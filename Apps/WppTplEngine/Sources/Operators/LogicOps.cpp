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
 * @file Operators/LogicOps.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-31
 */

#include "Operators/LogicOps.h"

namespace Operators {

And::And()
  : Operator("and", "&&", Operator::Binary)
{
	_binaryPrecedence = 2;
}

bool And::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant And::exec(const List<Variant>& args) const
{
	return args[0].toBool() && args[1].toBool();
}

//----------------------------------------------------------------------------//

Or::Or()
  : Operator("or", "||", Operator::Binary)
{
	_binaryPrecedence = 1;
}

bool Or::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Or::exec(const List<Variant>& args) const
{
	return args[0].toBool() || args[1].toBool();
}

//----------------------------------------------------------------------------//

Not::Not()
  : Operator("not", "!", Operator::Unary)
{
	_unaryPrecedence = 11;
}

bool Not::checkArgTypes(const List<Variant::Type>&) const
{
	return true;
}

Variant Not::exec(const List<Variant>& args) const
{
	return !(args[0].toBool());
}

} // ns Operators
