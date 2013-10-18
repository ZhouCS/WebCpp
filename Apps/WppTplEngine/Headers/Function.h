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
 * @file Function.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-29
 */

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <List>
#include <Map>

class Variant;
class Template;

class Function
{
public:
	typedef Variant (*Handler)(Template*, const List<Variant>&);
	enum Option
	{
		NoOptions = 0x0,
		Const     = 0x1,
		Raw       = 0x2,
		Filter    = 0x4
	};

	Function();
	Function(const String& name,
	         Handler func,
	         int argsCount = -1,
	         int options = NoOptions);

	static void registerFunction(const String& name,
	                             Handler func,
	                             int argsCount = -1,
	                             int options = NoOptions);
	static void registerFilter(const String& name, Handler func,
	                           int argsCount = -1,
	                           int options = NoOptions);
	static void registerBuiltins();
	static bool hasFunction(const String& name);
	static bool hasFilter(const String& name);
	static Function byName(const String& name);
	static Function filterByName(const String& name);

public:
	String  name;
	int     argsCount;
	bool    isConst;
	bool    isRaw;
	bool    isFilter;
	Handler func;

private:
	static Map<String, Function> _functions;
	static Map<String, Function> _filters;
};

#endif // !_FUNCTION_H_
