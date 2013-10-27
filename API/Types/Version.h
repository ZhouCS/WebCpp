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
 * @file Types/Version.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-16
 */

#ifndef _WPP_TYPES_VERSION_H_
#define	_WPP_TYPES_VERSION_H_

#include "Types/String.h"

/**
 * @class Version Types/Version.h <Version>
 * @brief A version representation
 */
class Version
{
public:
	Version();

	/**
	 * @brief Constructs a version from a string
	 */
	Version(const String& str);

	operator String() const;

private:
	/**
	 * @brief The version as string
	 */
	String _str;
};

#endif // !_WPP_TYPES_VERSION_H_
