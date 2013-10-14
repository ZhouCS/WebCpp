/*************************************************************************
 * Copyright © 2011-2013 Kévin Lesénéchal <kevin@lesenechal.org>         *
 *                                                                       *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.            *
 *                                                                       *
 * WebCpp is free software: you can redistribute it and/or modify it     *
 * under the terms of the GNU General Public License as published by the *
 * Free Software Foundation, either version 3 of the License, or (at     *
 * your option) any later version.                                       *
 *                                                                       *
 * WebCpp is distributed in the hope that it will be useful, but WITHOUT *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License  *
 * for more details.                                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with WebCpp. If not, see <http://www.gnu.org/licenses/>.        *
 *************************************************************************/

/**
 * @file Libs/StackTrace.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-19
 */

#include "Libs/StackTrace.h"
#include "Libs/IO/Process.h"
#include "Libs/IO/File.h"

#include <execinfo.h>
#include <cxxabi.h>

Map<String, uint64_t> StackTrace::_soMapCache;

StackTrace::StackTrace(int removeLastFrames)
{
	_framesCount = backtrace(_rawFrames,
	                         (sizeof _rawFrames / sizeof _rawFrames[0]) - 1);
	if (removeLastFrames < 0)
		removeLastFrames = 0;
	removeLastFrames++;
	if (removeLastFrames >= _framesCount)
	{
		_rawFrames[0] = nullptr;
		return;
	}
	_removeLastFrames = removeLastFrames;
	_rawFrames[_framesCount] = nullptr;
}

void StackTrace::loadFrames()
{
	char** symbols = backtrace_symbols(_rawFrames, _framesCount);
	if (symbols == nullptr)
		return;

	for (int i = _removeLastFrames; i < _framesCount - 2; i++)
	{
		String symbol = symbols[i];
		Frame frame;

		frame.address = reinterpret_cast<uint64_t>(_rawFrames[i]);
		int leftParPos = symbol.indexOf("(");
		if (leftParPos == -1)
			continue;
		int rightParPos = symbol.indexOf(")", leftParPos + 1);
		if (rightParPos == -1)
			continue;
		frame.object = Path(symbol.substr(0, leftParPos), System::get()->runDir());
		String func = symbol.mid(leftParPos + 1, rightParPos);
		int status;
		char* funcName = abi::__cxa_demangle(func.tokenLeft("+"), nullptr,
		                                     nullptr, &status);
		frame.function = funcName == nullptr
		                   ? func.tokenLeft("+")
		                   : String(funcName);
		frame.functionOffset = func.tokenRight("+").toInt(16);

		frame.fileName = String();
		frame.line = 0;
		String fileLine = Process::exec("/usr/bin/addr2line",
		                                {"-e", frame.object.absolutePath(),
		                                 "0x" + String::fromNumber(objAddr(frame),
		                                                           16)});
		fileLine = fileLine.removeRight(1);
		if (!fileLine.startsWith("??"))
			frame.fileName = Path(fileLine.section(":", 0, -2)).absolutePath();
		String line = fileLine.section(":", -1, -1);
		if (line.contains(" "))
			line = line.tokenLeft(" ");
		frame.line = line.toInt();

		_stackFrames.append(frame);
	}
	free(symbols);
}

uint64_t StackTrace::objAddr(Frame frame)
{
	if (frame.object.relativePath() == "WebCpp/WebCpp")
		return frame.address;
	if (_soMapCache.hasKey(frame.object.absolutePath()))
		return frame.address - _soMapCache[frame.object.absolutePath()];
	StringList lines = String(File::getContent("/proc/self/maps")).split("\n");
	for (const String& line : lines)
	{
		if (line.endsWith(frame.object.absolutePath()) && line.contains(" r-xp "))
		{
			uint64_t base = line.tokenLeft("-").toUInt64(16);
			_soMapCache[frame.object.absolutePath()] = base;
			return frame.address - base;
		}
	}
	return frame.address;
}

//----------------------------------------------------------------------------//

List<StackTrace::Frame> StackTrace::stackFrames()
{
	if (_stackFrames.count() == 0)
		loadFrames();
	return _stackFrames;
}

List<StackTrace::Frame> StackTrace::stackFrames() const
{ return _stackFrames; }
