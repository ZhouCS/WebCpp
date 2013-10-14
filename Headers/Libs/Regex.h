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
 * @file Libs/Regex.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-05
 */

#ifndef _LIBS_REGEX_H_
#define	_LIBS_REGEX_H_

#include <pcre.h>

#include "Types/String.h"
#include "Types/StringList.h"
#include "Types/Pair.h"

/**
 * @class Regex Libs/Regex.h <Regex>
 * @brief A PCRE regular expression
 */
class Regex
{
public:
	/**
	 * @brief Regex options
	 */
	enum Options
	{
		None          = 0x0,
		Caseless      = 0x1,
		Multiline     = 0x2,
		DotAll        = 0x4,
		Extended      = 0x8,

		Anchored      = 0x10,
		DollarEndOnly = 0x20,
		Extra         = 0x40,
		NotBOL        = 0x80,

		NotEOL        = 0x100,
		Ungreedy      = 0x200
	};

	/**
	 * @brief Constructs an empty regular expression
	 */
	Regex();

	/**
	 * @brief Constructs a regular expression from a string
	 * @param pattern The regex pattern
	 */
	Regex(const String& pattern, int options = None);

	/**
	 * @brief Destructs the regex
	 */
	~Regex();

	/**
	 * @brief Compiles the regex
	 */
	void compile();

	/**
	 * @brief Executes the regex
	 * @param str The string to test
	 * @return true if the regex matches the string, otherwise false
	 */
	bool exec(const String& str);


	/**
	 * @brief Get the regex pattern
	 * @return The regex pattern
	 */
	String pattern() const;

	/**
	 * @brief Get the number of captures in the regex
	 * @return The number of captures in the regex
	 */
	int capturesCount() const;

	/**
	 * @brief Get the captured texts
	 * @return The captured texts
	 */
	StringList capturedTexts() const;

	List<Pair<int, int>> capturedIndexes() const;

private:
	/**
	 * @brief The regex pattern
	 */
	String _pattern;

	/**
	 * @brief The regex options
	 */
	int _options;

	/**
	 * @brief The PCRE regex
	 */
	pcre* _regex;

	/**
	 * @brief Captured textes
	 */
	StringList _capturedTexts;

	/**
	 * @brief Captured indexes
	 */
	List<Pair<int, int>> _capturedIndexes;
};

#endif // !_LIBS_REGEX_H_
