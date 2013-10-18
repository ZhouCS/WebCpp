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
#include <Template>
#include <Request>
#include <Libs/Locale/Locale.h>

namespace Filters {

Variant bytesSize(Template* tpl, const List<Variant>& args)
{
	return tpl->request()->locale()->parseSize(args[0].toUInt64());
}

Variant money(Template* tpl, const List<Variant>& args)
{
	String currency;

	if (args.count() > 1)
		currency = args[1].toString();
	return tpl->request()->locale()->parseMoney(args[0].toFloat(), currency);
}

} // ns Filters
