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
 * @file Types/OrderedMap.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-15
 */

template<typename Key, typename Value, typename Comp>
OrderedMap<Key, Value, Comp>::OrderedMap()
  : std::map<Key, Value, Comp>()
{ }

template<typename Key, typename Value, typename Comp>
Value OrderedMap<Key, Value, Comp>::get(const Key& key) const
{ return find(key)->second; }

template<typename Key, typename Value, typename Comp>
void OrderedMap<Key, Value, Comp>::set(const Key& key, const Value& value)
{ std::map<Key, Value, Comp>::operator[](key) = value; }

template<typename Key, typename Value, typename Comp>
void OrderedMap<Key, Value, Comp>::clear()
{ std::map<Key, Value, Comp>::clear(); }

template<typename Key, typename Value, typename Comp>
typename OrderedMap<Key, Value, Comp>::Iterator OrderedMap<Key, Value,
                                                           Comp>::it() const
{ return OrderedMap<Key, Value, Comp>::Iterator(*this); }

template<typename Key, typename Value, typename Comp>
bool OrderedMap<Key, Value, Comp>::hasKey(const Key& key) const
{ return find(key) != std::map<Key, Value, Comp>::end(); }

template<typename Key, typename Value, typename Comp>
List<Key> OrderedMap<Key, Value, Comp>::keys() const
{
	List<Key> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.key());
	return list;
}

template<typename Key, typename Value, typename Comp>
List<Value> OrderedMap<Key, Value, Comp>::values() const
{
	List<Value> list;
	for (auto i = it(); i.hasNext(); i++)
		list.append(i.value());
	return list;
}

template<typename Key, typename Value, typename Comp>
Value& OrderedMap<Key, Value, Comp>::operator[](const Key& key)
{ return std::map<Key, Value, Comp>::operator[](key); }

template<typename Key, typename Value, typename Comp>
Value OrderedMap<Key, Value, Comp>::operator[](const Key& key) const
{ return find(key)->second; }

//----------------------------------------------------------------------------//

template<typename Key, typename Value, typename Comp>
OrderedMap<Key, Value, Comp>::Iterator::Iterator(const OrderedMap<Key, Value,
                                                 Comp>& map) : _map(&map)
{
	_iterator = ((std::map<Key, Value, Comp>*)_map)
	            ->std::map<Key, Value, Comp>::begin();
}

template<typename Key, typename Value, typename Comp>
void OrderedMap<Key, Value, Comp>::Iterator::next()
{
	// TODO: throw an exception if at the end
	_iterator++;
}

template<typename Key, typename Value, typename Comp>
bool OrderedMap<Key, Value, Comp>::Iterator::hasNext() const
{ return _iterator != _map->end(); }

template<typename Key, typename Value, typename Comp>
Key OrderedMap<Key, Value, Comp>::Iterator::key() const
{ return _iterator->first; }

template<typename Key, typename Value, typename Comp>
Value OrderedMap<Key, Value, Comp>::Iterator::value() const
{ return _iterator->second; }

template<typename Key, typename Value, typename Comp>
typename OrderedMap<Key, Value, Comp>::Iterator
  OrderedMap<Key, Value, Comp>::Iterator::operator++(int)
{
	next();
	return *this;
}
