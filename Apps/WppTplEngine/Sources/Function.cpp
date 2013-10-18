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
 * @file Function.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-29
 */

#include "Function.h"

#include "Functions/MiscFuncs.h"
#include "Functions/MathFuncs.h"

#include "Filters/StringFilters.h"
#include "Filters/LocaleFilters.h"

Map<String, Function> Function::_functions;
Map<String, Function> Function::_filters;

Function::Function()
  : argsCount(-1),
    isConst(false)
{}

Function::Function(const String& name,
                   Handler func,
                   int argsCount,
                   int options)
  : name(name),
    argsCount(argsCount),
    isConst(options & Const),
    isRaw(options & Raw),
    isFilter(options & Filter),
    func(func)
{}

void Function::registerFunction(const String& name,
                                Handler func,
                                int argsCount,
                                int options)
{
	Function f(name, func, argsCount, options);
	if (options & Filter)
		_filters[name] = f;
	else
		_functions[name] = f;
}

void Function::registerFilter(const String& name,
                              Handler func,
                              int argsCount,
                              int options)
{
	registerFunction(name, func, argsCount, options | Filter);
}

void Function::registerBuiltins()
{
	registerFunction("dump", &Functions::dump, 1, Const | Raw);
	registerFunction("pow",  &Functions::pow,  2, Const);

	registerFilter("raw",           &Filters::raw,           0, Const | Raw);
	registerFilter("upper",         &Filters::upper,         0, Const);
	registerFilter("left",          &Filters::left,          1, Const);
	registerFilter("hex",           &Filters::hex,           0, Const);
	registerFilter("codeHighlight", &Filters::codeHighlight, 1, Const | Raw);

	registerFilter("bytesSize",     &Filters::bytesSize,     0, Const | Raw);
	registerFilter("money",         &Filters::money,        -1, Const | Raw);
}

bool Function::hasFunction(const String& name)
{ return _functions.hasKey(name); }

bool Function::hasFilter(const String &name)
{ return _filters.hasKey(name); }

Function Function::byName(const String& name)
{ return _functions[name]; }

Function Function::filterByName(const String& name)
{ return _filters[name]; }
