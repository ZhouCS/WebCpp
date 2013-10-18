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
 * @file Filters/LocaleFilters.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-08-31
 */

#ifndef _FILTERS_LOCALEFILTERS_H_
#define _FILTERS_LOCALEFILTERS_H_

#include <List>

class Template;
class Variant;

namespace Filters {

Variant bytesSize(Template* tpl, const List<Variant>& args);
Variant money(Template* tpl, const List<Variant>& args);

} // ns Filters

#endif // !_FILTERS_LOCALEFILTERS_H_
