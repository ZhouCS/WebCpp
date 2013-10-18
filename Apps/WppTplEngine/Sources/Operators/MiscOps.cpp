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
 * @file Operators/MiscOps.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-06
 */

#include "Operators/MiscOps.h"

namespace Operators {

Typeof::Typeof()
  : Operator("type of", "typeof", Operator::Unary)
{
	_unaryPrecedence = 11;
}

bool Typeof::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Typeof::exec(const List<Variant>& args) const
{
	return args[0].typeString();
}

//----------------------------------------------------------------------------//

Count::Count()
  : Operator("count", "#", Operator::Unary)
{
	_unaryPrecedence = 11;
}

bool Count::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Count::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::List)
		return args[0].toList().count();
	else if (args[0].type() == Variant::Type::String)
		return args[0].toString().size();
	else if (args[0].type() == Variant::Type::Map)
		return args[0].toMap().count();
	else
		throw 42; // FIX ME
}

} // ns Operators
