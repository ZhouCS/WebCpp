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
 * @file Exceptions/Exception.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-08
 */

#include "Exceptions/Exception.h"

#include "System.h"
#include "Types/String.h"

#include "Libs/IO/File.h"
#include "Libs/StackTrace.h"

#include <fstream>

#ifndef WINDOWS
#include <execinfo.h>
#include <cxxabi.h>
#endif

//Map<String, uint64_t> Exception::_soMapsCache;

Exception::Exception(const String& type, const String& message) throw()
  : _type(type),
    _message(message),
    _stackTrace(new StackTrace(2))
{
	std::ofstream file(String(ABS + "Logs/Exceptions.log").toCString(),
	                   std::ios::app);
	file << String("%1: %2.").format({type, message}) << std::endl;
	file.close();
}

Exception::~Exception() throw()
{
	delete _stackTrace;
}

String Exception::type() const
{ return _type; }

String Exception::message() const
{ return _message; }

String Exception::htmlMessage() const
{
	return _htmlMessage.isNull()
	    ? "<p>" + _message.htmlEscape() + ".</p>"
	    : _htmlMessage;
}

StackTrace* Exception::stackTrace() const
{
	/*
#ifndef WINDOWS
	if (_stackTraceSize == 0)
		return List<Exception::StackFrame>();
	else if(_stackTrace.count() > 0)
		return _stackTrace;

	for (int i = 2; i < ((int)_stackTraceSize) - 2; i++)
	{
		char* lineCh = _stackTraceLines[i];
		if (lineCh == nullptr)
			break;

		String line = lineCh;
		int parPos = line.indexOf("(");

		StackFrame frame;
		frame.address = reinterpret_cast<uint64_t>(_stackTraceBuffer[i]);

		String objectName = line.mid(0, parPos);
		if (objectName.endsWith("/WebCpp"))
			frame.object = ABS + "WebCpp/WebCpp";
		else
			frame.object = objectName;

		int status;
		String funcName = line.mid(parPos + 1, line.indexOf(")", parPos + 1))
		                  .tokenLeft("+");
		char* func = abi::__cxa_demangle(funcName, 0, 0, &status);
		if (status == 0)
			frame.functionName = func;
		else
			frame.functionName = funcName;

		uint64_t objAddr = 0;
		if (frame.object.absolutePath().endsWith(".so"))
		{
			uint64_t soMapAddr = _soMapsCache.get(frame.object.absolutePath(), 0);
			if (soMapAddr == 0)
			{
				StringList mapsLines = String(File::getContent("/proc/self/maps"))
				                       .split("\n");
				for (const String& mapsLine : mapsLines)
				{
					if (mapsLine.section(" ", 1, 1) != "r-xp")
						continue;
					if (mapsLine.tokenRight("   ").trim() != frame.object.absolutePath())
						continue;
					soMapAddr = mapsLine.tokenLeft("-").toUInt64(16);
					_soMapsCache[frame.object.absolutePath()] = soMapAddr;
					break;
				}
			}
			objAddr = frame.address - soMapAddr;
		}
		else
			objAddr = frame.address;

		FILE* cmd = popen(String("addr2line -e \"%1\" 0x%2")
		                  .format(frame.object.absolutePath(),
		                          String::fromNumber(objAddr, 16))
		                  .toCString(),
		                  "r");
		String r;
		char buffer[128];
		while (!feof(cmd))
		{
			if (fgets(buffer, 128, cmd) != nullptr)
				r += buffer;
		}
		pclose(cmd);

		frame.fileName = r.tokenLeft(":");
		if (frame.fileName == "??")
		{
			frame.fileName = String();
			frame.line = 0;
		}
		else
			frame.line = r.tokenRight(":").toInt();

		_stackTrace.append(frame);
	}

	return _stackTrace;
#endif
#ifdef WINDOWS
	return List<Exception::StackFrame>();
#endif
	*/
	return _stackTrace;
}

const char* Exception::what() const throw()
{ return _message.toCString(); }
