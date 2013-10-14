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
 * @file Types/Pair.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-07
 */

#ifndef _TYPES_PAIR_H_
#define	_TYPES_PAIR_H_

#include <utility>

/**
 * @class Pair Types/Pair.h <Pair>
 * @brief A pair of values
 */
template<typename F, typename S> class Pair : private std::pair<F, S>
{
public:
	/**
	 * @brief Constructs a pair of values
	 */
	Pair();

	Pair(const std::pair<F, S>& pair);

	/**
	 * @brief Constructs a pair of values
	 * @param first The first value
	 * @param second The second value
	 */
	Pair(const F& first, const S& second);

	/**
	 * @brief Get the first value
	 * @return The first value
	 */
	F first() const;

	/**
	 * @brief Get the second value
	 * @return The second value
	 */
	S second() const;
};

#include "Sources/Types/Pair.cpp"

#endif // !_TYPES_PAIR_H_
