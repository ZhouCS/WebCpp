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
 * @file Types/Map.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#ifndef _WPP_TYPES_MAP_H_
#define _WPP_TYPES_MAP_H_

#include <unordered_map>

#include "Types/String.h"
#include "Types/List.h"
#include "Types/Pair.h"

#define REGISTER_HASH(className) namespace std {     \
template<> struct hash<className>                    \
{                                                    \
	std::size_t operator()(const className& val) const \
	{ return val.hash(); }                             \
};                                                   \
}

/**
 * @class Map Types/Map.h <Map>
 * @brief A map (std::unordered_map backend)
 */
template<typename Key, typename Value> class Map
  : private std::unordered_map<Key, Value>
{
public:
	//using std::unordered_map<Key, Value>::operator[];
	using std::unordered_map<Key, Value>::begin;
	using std::unordered_map<Key, Value>::end;
	using std::unordered_map<Key, Value>::find;

	/**
	 * @brief Constructs an empty map
	 */
	Map();

	/**
	 * @brief Get a value from a key
	 * @param key The specified key
	 * @return The value associated to key @p key.
	 */
	Value get(const Key& key) const;

	/**
	 * @brief Get a value from a key with a default value
	 * @param key The specified key
	 * @param defaultValue The default value
	 * @return The value associated to key @p key. If @p key doesn't exist,
	 *         returns @p defaultValue
	 */
	Value get(const Key& key, const Value& defaultValue) const;

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
	typename Map<Key, Value>::Iterator it() const;

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

	/**
	 * @brief Get the number of items in the map
	 */
	int count() const;

	Value& operator[](const Key& key);

	Value operator[](const Key& key) const;

	/**
	 * @brief A map iterator
	 */
	class Iterator
	{
	public:
		Iterator(const Map<Key, Value>& map);

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

		Value& value();

		/**
		 * @brief Operator to call next()
		 */
		Iterator operator++(int);

	private:
		/**
		 * @brief The reference to the map
		 */
		const Map<Key, Value>* _map;

		/**
		 * @brief The STL iterator
		 */
		typename std::unordered_map<Key, Value>::iterator _iterator;
	};
};

REGISTER_HASH(String)

#include "Sources/Types/Map.cpp"

#endif // !_WPP_TYPES_MAP_H_
