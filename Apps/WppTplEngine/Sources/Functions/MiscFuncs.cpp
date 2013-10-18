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
 * @file Functions/MiscFuncs.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-29
 */

#include "Functions/MiscFuncs.h"

#include <cmath>

namespace Functions {

Variant dump(Template*, const List<Variant>& args)
{
	String r;
	Variant val = args[0];

	if (val.type() == Variant::Type::None)
		r = "<span style=\"color:#0000b1\">null</span>";
	else if (val.type() == Variant::Type::Integer)
		r = "Integer = <span style=\"color:#007f7f\">" + val.toString() + "</span>";
	else if (val.type() == Variant::Type::Float)
		r = "Float = <span style=\"color:#007f7f\">" + val.toString() + "</span>";
	else if (val.type() == Variant::Type::String)
		r = "String = <span style=\"color:#7f007f\">'" + val.toString()
		    + "'</span>";

	return "<pre>" + r + "</pre>";
}

}
