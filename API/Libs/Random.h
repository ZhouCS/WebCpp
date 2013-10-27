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
 * @file Libs/Random.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-22
 */

#ifndef _WPP_LIBS_RANDOM_H_
#define	_WPP_LIBS_RANDOM_H_

class String;
template<typename T> class List;

/**
 * @class Random Libs/Random.h <Random>
 * @brief Generator of random values
 */
class Random
{
public:
	/**
	 * @brief Types of characters to generate the string
	 */
	enum Characters
	{
		Digits       = 0x1,
		LowerCase    = 0x2,
		UpperCase    = 0x4,
		AsciiSymbols = 0x8,
		All          = 0xf
	};

	/**
	 * @brief Generates a simple string from pseudo-random generator
	 * @param length The length of the string
	 * @param charsOpt The characters to use
	 * @return A pseudo-random string of @p length chars in @p charsOpt
	 */
	static String generate(int length, int charsOpt = (Digits
	                                                   | LowerCase
	                                                   | UpperCase));

protected:
	/**
	 * @brief Get the chars list from options
	 * @param charsOpt The characters options
	 * @return The chars list
	 */
	static List<char> charsList(int charsOpt);
};

#endif // !_WPP_LIBS_RANDOM_H_
