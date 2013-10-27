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
 * @file Types/MultiMap.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-23
 */

#ifndef _WPP_TYPES_MULTIMAP_H_
#define	_WPP_TYPES_MULTIMAP_H_

#include <map>

template<typename Value> class List;

template<typename Key, typename Value> class MultiMap
  : private std::multimap<Key, Value>
{
public:
	using std::multimap<Key, Value>::begin;
	using std::multimap<Key, Value>::end;
	using std::multimap<Key, Value>::find;

	/**
	 * @brief Constructs an empty multi map
	 */
	MultiMap();

	/**
	 * @brief Get the first value with the given key
	 * @param key The specified key
	 * @return The first value associated to key @p key.
	 */
	Value getFirst(const Key& key) const;

	/**
	 * @brief Get all the values from a key
	 * @param key The specified key
	 * @return All the values associated to key @p key
	 */
	List<Value> get(const Key& key) const;

	/**
	 * @brief Set the first key @p key to value @p value
	 * @param key The first key to search
	 * @param value The value to set
	 */
	void setFirst(const Key& key, const Value& value);

	/**
	 * @brief Inserts a value in the multi map
	 * @param key The key index
	 * @param value The value to insert
	 */
	void insert(const Key& key, const Value& value);

	/**
	 * @brief Removes all element in the map
	 */
	void clear();

	/**
	 * @brief Get the map iterator
	 */
	typename MultiMap<Key, Value>::Iterator it() const;

	/**
	 * @brief Get the keys list
	 */
	List<Key> keys() const;

	/**
	 * @brief Get the values list
	 */
	List<Value> values() const;

	/**
	 * @brief Get the number of items
	 */
	int count() const;

	/**
	 * @brief A map iterator
	 */
	class Iterator
	{
	public:
		Iterator(const MultiMap<Key, Value>& map);

		/**
		 * @brief Go to the next entry
		 */
		void next();

		/**
		 * @brief Determines if the iterator is at the end
		 * @return true if the iterator is at the end, otherwise false
		 */
		bool hasNext() const;

		/**
		 * @brief Get the current key
		 * @return The current key
		 */
		Key key() const;

		/**
		 * @brief Get the current value
		 * @return The current value
		 */
		Value value() const;

		/**
		 * @brief Operator to call next()
		 */
		Iterator operator++(int);

	private:
		/**
		 * @brief The reference to the map
		 */
		const MultiMap<Key, Value>* _map;

		/**
		 * @brief The STL iterator
		 */
		typename std::multimap<Key, Value>::iterator _iterator;
	};
};

#include "Sources/Types/MultiMap.cpp"

#endif // !_WPP_TYPES_MULTIMAP_H_
