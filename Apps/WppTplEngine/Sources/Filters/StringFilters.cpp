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
 * @file Filters/StringFilters.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-31
 */

#include "Filters/StringFilters.h"

#include <CodeHighlighter>

namespace Filters {

Variant raw(Template*, const List<Variant>& args)
{
	return args[0];
}

Variant upper(Template*, const List<Variant>& args)
{
	return args[0].toString().toAsciiUpper(); // FIX ME
}

Variant left(Template*, const List<Variant>& args)
{
	return args[0].toString().left(args[1].toInt());
}

Variant hex(Template*, const List<Variant>& args)
{
	if (args[0].type() == Variant::Type::UInt64)
		return String::fromNumber(args[0].toUInt64(), 16);
	else if (args[0].type() == Variant::Type::Integer)
		return String::fromNumber(args[0].toInt(), 16);
	else
		throw 42; // FIX ME
}

Variant codeHighlight(Template*, const List<Variant> &args)
{
	return CodeHighlighter::byId(args[1].toString())
	    ->highlight(args[0].toString());
}

} // ns Filters
