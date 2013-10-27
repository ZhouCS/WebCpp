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
 * @file StringList.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-26
 */

#ifndef _WPP_TYPES_STRINGLIST_H_
#define _WPP_TYPES_STRINGLIST_H_

#include "Types/List.h"
#include "Types/String.h"

/**
 * @class StringList Types/StringList.h <StringList>
 * @brief A list of strings
 */
class StringList : public List<String>
{
public:
	/**
	 * @brief Constructs an empty string list
	 */
	StringList();

	StringList(const List<String>& list);

	/**
	 * @brief Constructs a string list with an initializer list
	 * @param initList The initializer list
	 */
	StringList(std::initializer_list<String> initList);

	/**
	 * @brief Joins the string list with the specified delimiter
	 * @param delem The delimiter
	 * @return The joined string
	 */
	String join(const String& delem) const;

	/**
	 * @brief Implements how to dump the data for debugging
	 * @return The dumped data string
	 */
	String dump() const;
};

#endif // !_WPP_TYPES_STRINGLIST_H_
