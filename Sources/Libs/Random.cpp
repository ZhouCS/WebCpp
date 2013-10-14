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
 * @file Libs/Random.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-22
 */

#include "Libs/Random.h"
#include "Types/List.h"

#include <random>
#include <functional>
#include <boost/date_time/posix_time/posix_time_types.hpp>

String Random::generate(int length, int charsOpt)
{
	List<char> chars = charsList(charsOpt);
	auto gen = std::bind(std::uniform_int_distribution<int>(0, chars.count() - 1),
	                     std::mt19937(
	                       boost::posix_time::microsec_clock::universal_time()
	                       .time_of_day().total_microseconds()));
	char* output = new char[length + 1];

	for (int i = 0; i < length; i++)
		output[i] = chars[gen()];
	output[length] = '\0';

	String r(output);
	delete[] output;
	return r;
}

List<char> Random::charsList(int charsOpt)
{
	List<char> chars;
	if (charsOpt & Digits)
		chars.append({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
	if (charsOpt & LowerCase)
		chars.append({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		              'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		              'y', 'z'});
	if (charsOpt & UpperCase)
		chars.append({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
		              'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		              'Y', 'Z'});
	if (charsOpt & AsciiSymbols)
		chars.append({'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
		              '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\',
		              ']', '^', '_', '`', '{', '|', '}', '~'});
	return chars;
}
