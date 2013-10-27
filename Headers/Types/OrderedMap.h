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
 * @file Types/OrderedMap.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-15
 */

#ifndef _WPP_TYPES_ORDEREDMAP_H_
#define	_WPP_TYPES_ORDEREDMAP_H_

#include <map>

#include "Types/List.h"

template<typename Key,
         typename Value,
         typename Comp = std::less<Key>> class OrderedMap
                                   : private std::map<Key, Value, Comp>
{
public:
	using std::map<Key, Value, Comp>::begin;
	using std::map<Key, Value, Comp>::end;
	using std::map<Key, Value, Comp>::find;

	/**
	 * @brief Constructs an empty map
	 */
	OrderedMap();

	/**
	 * @brief Get a value from a key
	 * @param key The specified key
	 * @return The value associated to key @p key.
	 */
	Value get(const Key& key) const;

	/**
	 * @brief Set a value in the map
	 * @param key The key index
	 * @param value The value to set
	 */
	void set(const Key& key, const Value& value);

	/**
	 * @brief Removes all the map's content
	 */
	void clear();

	/**
	 * @brief Get the map iterator
	 */
	typename OrderedMap<Key, Value, Comp>::Iterator it() const;

	/**
	 * @brief Determines if the map contains the given key
	 * @param key The given key
	 * @return true if the map has a @p key key, otherwise false
	 */
	bool hasKey(const Key& key) const;

	/**
	 * @brief Get the keys list
	 */
	List<Key> keys() const;

	/**
	 * @brief Get the values list
	 */
	List<Value> values() const;

	Value& operator[](const Key& key);

	Value operator[](const Key& key) const;

	/**
	 * @brief A map iterator
	 */
	class Iterator
	{
	public:
		Iterator(const OrderedMap<Key, Value, Comp>& map);

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
		const OrderedMap<Key, Value, Comp>* _map;

		/**
		 * @brief The STL iterator
		 */
		typename std::map<Key, Value, Comp>::iterator _iterator;
	};
};

#include "Sources/Types/OrderedMap.cpp"

#endif // !_WPP_TYPES_ORDEREDMAP_H_
