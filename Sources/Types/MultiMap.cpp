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
 * @file Tools/MultiMap.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-23
 */

template<typename Key, typename Value>
MultiMap<Key, Value>::MultiMap()
  : std::multimap<Key, Value>()
{ }

template<typename Key, typename Value>
Value MultiMap<Key, Value>::getFirst(const Key& key) const
{ return find(key)->second; }

template<typename Key, typename Value>
List<Value> MultiMap<Key, Value>::get(const Key& key) const
{
	const std::pair<typename std::multimap<Key, Value>::const_iterator,
	                typename std::multimap<Key, Value>::const_iterator>
	    it = std::multimap<Key, Value>::equal_range(key);
	List<Value> list;
	for (typename std::multimap<Key, Value>::const_iterator i = it.first;
	     i != it.second; i++)
		list.append((*i).second);
	return list;
}

template<typename Key, typename Value>
void MultiMap<Key, Value>::setFirst(const Key& key, const Value& value)
{
	typename std::multimap<Key, Value>::iterator it = find(key);
	if (it == end())
		insert(key, value);
	else
		it->second = value;
}

template<typename Key, typename Value>
void MultiMap<Key, Value>::insert(const Key& key, const Value& value)
{ std::multimap<Key, Value>::insert(std::pair<Key, Value>(key, value)); }

template<typename Key, typename Value>
void MultiMap<Key, Value>::clear()
{ std::multimap<Key, Value>::clear(); }

template<typename Key, typename Value>
typename MultiMap<Key, Value>::Iterator MultiMap<Key, Value>::it() const
{ return MultiMap<Key, Value>::Iterator(*this); }

template<typename Key, typename Value>
List<Key> MultiMap<Key, Value>::keys() const
{
	List<Key> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.key());
	return list;
}

template<typename Key, typename Value>
List<Value> MultiMap<Key, Value>::values() const
{
	List<Value> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.value());
	return list;
}

template<typename Key, typename Value>
int MultiMap<Key, Value>::count() const
{
	return std::multimap<Key, Value>::size();
}

//----------------------------------------------------------------------------//

template<typename Key, typename Value>
MultiMap<Key, Value>::Iterator::Iterator(const MultiMap<Key, Value>& map)
  : _map(&map)
{
	_iterator = ((std::multimap<Key, Value>*)_map)
	            ->std::multimap<Key, Value>::begin();
}

template<typename Key, typename Value>
void MultiMap<Key, Value>::Iterator::next()
{
	// TODO: throw an exception if at the end
	_iterator++;
}

template<typename Key, typename Value>
bool MultiMap<Key, Value>::Iterator::hasNext() const
{ return _iterator != _map->end(); }

template<typename Key, typename Value>
Key MultiMap<Key, Value>::Iterator::key() const
{ return _iterator->first; }

template<typename Key, typename Value>
Value MultiMap<Key, Value>::Iterator::value() const
{ return _iterator->second; }

template<typename Key, typename Value>
typename MultiMap<Key, Value>::Iterator
  MultiMap<Key, Value>::Iterator::operator++(int)
{
	next();
	return *this;
}
