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
 * @file Types/Stack.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-13
 */

#ifndef _WPP_TYPES_STACK_H_
#define	_WPP_TYPES_STACK_H_

#include <stack>

/**
 * @class Stack Types/Stack.h <Stack>
 * @brief A stack
 */
template<typename T> class Stack : private std::stack<T>
{
public:
	/**
	 * @brief Constructs an empty stack
	 */
	Stack();

	T&   top();
	T    top() const;
	void push(const T& value);
	T    pop();
	int  count() const;
	bool isEmpty() const;
};

#include "Sources/Types/Stack.cpp"

#endif // !_WPP_TYPES_STACK_H_
