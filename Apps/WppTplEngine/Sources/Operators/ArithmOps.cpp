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
 * @file Operators/ArithmOps.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#include "Operators/ArithmOps.h"

namespace Operators {

Sum::Sum()
  : Operator("sum", "+", Operator::Unary | Operator::Binary)
{
	_unaryPrecedence = 11;
	_binaryPrecedence = 9;
}

bool Sum::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Sum::exec(const List<Variant>& args) const
{
	if (args.count() == 1)
	{
		if (args[0].type() != Variant::Type::Integer
		    && args[0].type() != Variant::Type::Float)
			throw 42; // FIX ME
		return args[0];
	}
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toInt() + args[1].toInt());
	else if (args[0].type() == Variant::Type::Integer
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toInt() + args[1].toFloat());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toFloat() + args[1].toInt());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toFloat() + args[1].toFloat());
	else if (args[0].type() == Variant::Type::String
	         && (args[1].type() == Variant::Type::String
	             || args[1].type() == Variant::Type::Integer
	             || args[1].type() == Variant::Type::Float))
		return args[0].toString() + args[1].toString();
	else if (args[1].type() == Variant::Type::String
	         && (args[0].type() == Variant::Type::Integer
	             || args[0].type() == Variant::Type::Float))
		return args[0].toString() + args[1].toString();
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Difference::Difference()
  : Operator("difference", "-", Operator::Unary | Operator::Binary)
{
	_unaryPrecedence = 11;
	_binaryPrecedence = 9;
}

bool Difference::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Difference::exec(const List<Variant>& args) const
{
	if (args.count() == 1)
	{
		if (args[0].type() != Variant::Type::Integer
		    && args[0].type() != Variant::Type::Float)
			throw 42; // FIX ME
		return args[0].type() == Variant::Type::Integer
		    ? Variant(-(args[0].toInt())) : Variant(-(args[0].toFloat()));
	}
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toInt() - args[1].toInt());
	else if (args[0].type() == Variant::Type::Integer
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toInt() - args[1].toFloat());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toFloat() - args[1].toInt());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toFloat() - args[1].toFloat());
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Product::Product()
  : Operator("product", "*", Operator::Binary)
{
	_binaryPrecedence = 10;
}

bool Product::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Product::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toInt() * args[1].toInt());
	else if (args[0].type() == Variant::Type::Integer
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toInt() * args[1].toFloat());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toFloat() * args[1].toInt());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toFloat() * args[1].toFloat());
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Quotient::Quotient()
  : Operator("quotient", "/",  Operator::Binary)
{
	_binaryPrecedence = 10;
}

bool Quotient::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Quotient::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toInt() / args[1].toInt());
	else if (args[0].type() == Variant::Type::Integer
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toInt() / args[1].toFloat());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toFloat() / args[1].toInt());
	else if (args[0].type() == Variant::Type::Float
	         && args[1].type() == Variant::Type::Float)
		return Variant(args[0].toFloat() / args[1].toFloat());
	else
		throw 42; // FIX ME
}

//----------------------------------------------------------------------------//

Modulo::Modulo()
  : Operator("modulo", "%",  Operator::Binary)
{
	_binaryPrecedence = 10;
}

bool Modulo::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Modulo::exec(const List<Variant>& args) const
{
	if (args[0].type() == Variant::Type::Integer
	    && args[1].type() == Variant::Type::Integer)
		return Variant(args[0].toInt() % args[1].toInt());
	else
		throw 42; // FIX ME
}

} // ns Operators
