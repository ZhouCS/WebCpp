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
 * @file Types/Map.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

template<typename Key, typename Value>
Map<Key, Value>::Map()
  : std::unordered_map<Key, Value>()
{ }

template<typename Key, typename Value>
Value Map<Key, Value>::get(const Key& key) const
{ return find(key)->second; }

template<typename Key, typename Value>
Value Map<Key, Value>::get(const Key& key, const Value& defaultValue) const
{ return hasKey(key) ? find(key)->second : defaultValue; }

template<typename Key, typename Value>
void Map<Key, Value>::set(const Key& key, const Value& value)
{ std::unordered_map<Key, Value>::operator[](key) = value; }

template<typename Key, typename Value>
void Map<Key, Value>::clear()
{ std::unordered_map<Key, Value>::clear(); }

template<typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::it() const
{ return Map<Key, Value>::Iterator(*this); }

template<typename Key, typename Value>
bool Map<Key, Value>::hasKey(const Key& key) const
{ return find(key) != std::unordered_map<Key, Value>::end(); }

template<typename Key, typename Value>
List<Key> Map<Key, Value>::keys() const
{
	List<Key> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.key());
	return list;
}

template<typename Key, typename Value>
List<Value> Map<Key, Value>::values() const
{
	List<Value> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.value());
	return list;
}

template<typename Key, typename Value>
int Map<Key, Value>::count() const
{ return std::unordered_map<Key, Value>::size(); }

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{ return std::unordered_map<Key, Value>::operator[](key); }

template<typename Key, typename Value>
Value Map<Key, Value>::operator[](const Key& key) const
{ return find(key)->second; }

//----------------------------------------------------------------------------//

template<typename Key, typename Value>
Map<Key, Value>::Iterator::Iterator(const Map<Key, Value>& map)
  : _map(&map)
{
	_iterator = ((std::unordered_map<Key, Value>*)_map)
	            ->std::unordered_map<Key, Value>::begin();
}

template<typename Key, typename Value>
void Map<Key, Value>::Iterator::next()
{
	// TODO: throw an exception if at the end
	_iterator++;
}

template<typename Key, typename Value>
bool Map<Key, Value>::Iterator::hasNext() const
{ return _iterator != _map->end(); }

template<typename Key, typename Value>
Key Map<Key, Value>::Iterator::key() const
{ return _iterator->first; }

template<typename Key, typename Value>
Value Map<Key, Value>::Iterator::value() const
{ return _iterator->second; }

template<typename Key, typename Value>
Value& Map<Key, Value>::Iterator::value()
{ return _iterator->second; }

template<typename Key, typename Value>
typename Map<Key, Value>::Iterator Map<Key, Value>::Iterator::operator++(int)
{
	next();
	return *this;
}
