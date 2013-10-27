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
 * @file Functions/MiscFuncs.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-29
 */

#ifndef _WPP_FUNCTIONS_MISCFUNCS_H_
#define _WPP_FUNCTIONS_MISCFUNCS_H_

#include <List>

class Template;
class Variant;

namespace Functions {

Variant dump(Template* tpl, const List<Variant>& args);

}

#endif // !_WPP_FUNCTIONS_MISCFUNCS_H_
