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
 * @file Types/List.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-26
 */

#ifndef _WPP_TYPES_LIST_H_
#define _WPP_TYPES_LIST_H_

#include <vector>

/**
 * @class List Types/List.h <List>
 * @brief A list (std::vector backend)
 * @param T The type of objects contained in the list
 */
template<typename T> class List : private std::vector<T>
{
public:
	/**
	 * @brief Remove all the elements
	 */
	using std::vector<T>::clear;
	using std::vector<T>::begin;
	using std::vector<T>::end;

	/**
	 * @brief Constructs an empty list
	 */
	List();

	/**
	 * @brief Constructs a list with an initializer list
	 * @param initList The initializer list
	 */
	List(std::initializer_list<T> initList);

	/**
	 * @brief Append a value to the end of the list
	 * @param value The value to append
	 */
	void append(const T& value);

	void prepend(const T& value);

	/**
	 * @brief Append a list of values to the end of the list
	 * @param value The list of values to append
	 */
	void append(const List<T>& values);


	/**
	 * @brief Removes the value at index @p index
	 * @param index The value's index to remove
	 */
	void remove(int index);

	/**
	 * @brief Removes the first value equal to @p value
	 * @param value The value to remove
	 */
	void removeOne(const T& value);

	/**
	 * @brief Removes all values equal to @p value
	 * @param value The value to remove
	 */
	void removeAll(const T& value);


	/**
	 * @brief Tests if the list contains @p value
	 * @param value The value to test
	 * @return true if the list contains @p value, otherwise false
	 */
	bool contains(const T& value) const;

	/**
	 * @brief Get the number of elements in the list
	 * @return The number of elements in the list
	 */
	int count() const;

	const T& last() const;
	T& last();


	/**
	 * @brief Reverts the list
	 * @return The reverted list
	 */
	List<T> revert() const;


	/**
	 * @brief Implements how to dump the data for debugging
	 * @return The dumped data string
	 */
	//virtual String dump() const;


	/**
	 * @brief Access an element by index
	 * @param index The element index
	 * @return The element to the given index
	 */
	T at(int index) const;

	/**
	 * @brief Access an element by index
	 * @param index The element index
	 * @return The element to the given index
	 */
	T operator[](int index) const;

	T& operator[](int index);
};

#include "Sources/Types/List.cpp"

#endif // !_WPP_TYPES_LIST_H_
