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
 * @file Libs/Settings.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-29
 */

#ifndef _WPP_LIBS_SETTINGS_H_
#define	_WPP_LIBS_SETTINGS_H_

#include "Types/Map.h"
#include "Types/String.h"

class Path;

/**
 * @class Settings Libs/Settings.h <Settings>
 * @brief A settings list
 */
class Settings
{
public:
	/**
	 * @brief Constructs an empty settings list
	 */
	Settings();

	/**
	 * @brief Create a settings list from an INI file
	 * @param filePath The INI file path
	 * @return The created settings list
	 */
	static Settings fromIniFile(const Path& filePath);

	/**
	 * @brief Get a map copy of the values
	 */
	Map<String, Map<String, String>> values() const;

	/**
	 * @brief Get a value by key
	 * @param key The value key
	 * @return The value to key @p key
	 */
	String operator[](const String& key) const;

private:
	/**
	 * @brief The values list
	 */
	Map<String, String> _values;
};

#endif // !_WPP_LIBS_SETTINGS_H_
