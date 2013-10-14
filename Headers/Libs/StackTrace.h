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
 * @file Libs/StackTrace.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-19
 */

#ifndef _LIBS_STACKTRACE_H_
#define _LIBS_STACKTRACE_H_

#include "Types/List.h"
#include "Types/Path.h"

#include <stdint.h>

class StackTrace
{
public:
	struct Frame
	{
		uint64_t address;
		Path     object;
		String   function;
		uint64_t functionOffset;
		String   fileName;
		int      line;
	};

	StackTrace(int removeLastFrames = 0);

	List<Frame> stackFrames();
	List<Frame> stackFrames() const;

private:
	void     loadFrames();
	uint64_t objAddr(Frame frame);

private:
	int         _framesCount;
	int         _removeLastFrames;
	void*       _rawFrames[64];
	List<Frame> _stackFrames;

private:
	static Map<String, uint64_t> _soMapCache;
};

#endif // !_LIBS_STACKTRACE_H_
