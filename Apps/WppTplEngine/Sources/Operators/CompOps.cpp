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
 * @file Operators/CompOps.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-31
 */

#include "Operators/CompOps.h"

namespace Operators {

Equal::Equal()
  : Operator("equal", "==", Operator::Binary)
{
	_binaryPrecedence = 3;
}

bool Equal::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Equal::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() == args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() == args[1].toFloat();
	else if (args[0].type() == Variant::Type::String
	         && args[1].type() == Variant::Type::String)
		return args[0].toString() == args[1].toString();
	else if (args[0].type() == Variant::Type::None
	         && args[1].type() == Variant::Type::None)
		return true;
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

NotEqual::NotEqual()
  : Operator("not equal", "!=", Operator::Binary)
{
	_binaryPrecedence = 3;
}

bool NotEqual::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant NotEqual::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() != args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() != args[1].toFloat();
	else if (args[0].type() == Variant::Type::String
	         && args[1].type() == Variant::Type::String)
		return args[0].toString() != args[1].toString();
	else if (args[0].type() == Variant::Type::None
	         && args[1].type() == Variant::Type::None)
		return false;
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Less::Less()
  : Operator("less", "<", Operator::Binary)
{
	_binaryPrecedence = 4;
}

bool Less::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Less::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() < args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() < args[1].toFloat();
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

LessEqual::LessEqual()
  : Operator("less or equal", "<=", Operator::Binary)
{
	_binaryPrecedence = 4;
}

bool LessEqual::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant LessEqual::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() <= args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() <= args[1].toFloat();
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Greater::Greater()
  : Operator("greater", ">", Operator::Binary)
{
	_binaryPrecedence = 4;
}

bool Greater::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Greater::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() > args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() > args[1].toFloat();
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

GreaterEqual::GreaterEqual()
  : Operator("greater or equal", ">=", Operator::Binary)
{
	_binaryPrecedence = 4;
}

bool GreaterEqual::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant GreaterEqual::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return args[0].toInt() >= args[1].toInt();
	else if ((args[0].type() == Variant::Type::Float
	          || args[0].type() == Variant::Type::Integer)
	         && (args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toFloat() >= args[1].toFloat();
	else
		throw 42; // FIX ME
}

} // ns Operators
