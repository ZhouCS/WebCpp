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
 * @file Types/List.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-26
 */

#include "Types/String.h"

#include <iostream>
#include <typeinfo>

template<typename T>
List<T>::List()
  : std::vector<T>()
{

}

template<typename T>
List<T>::List(std::initializer_list<T> initList)
  : std::vector<T>(initList)
{ }

template<typename T>
void List<T>::append(const T& value)
{
	std::vector<T>::push_back(value);
}

template<typename T>
void List<T>::prepend(const T& value)
{
	std::vector<T>::insert(std::vector<T>::begin(), value);
}

template<typename T>
void List<T>::append(const List<T>& values)
{
	for (int i = 0; i < values.count(); i++)
		std::vector<T>::push_back(values[i]);
}


template<typename T>
void List<T>::remove(int index)
{
	std::vector<T>::erase(begin() + index);
}

template<typename T>
void List<T>::removeOne(const T& value)
{
	for (int i = 0, c = count(); i < c; i++)
	{
		if (at(i) == value)
		{
			remove(i);
			return;
		}
	}
}

template<typename T>
void List<T>::removeAll(const T& value)
{
	for (int i = 0; i < count();)
	{
		if (at(i) == value)
			remove(i);
		else
			i++;
	}
}


template<typename T>
int List<T>::count() const
{ return std::vector<T>::size(); }

template<typename T>
bool List<T>::contains(const T& value) const
{
	for (int i = 0, c = count(); i < c; i++)
	{
		if (at(i) == value)
			return true;
	}
	return false;
}

template<typename T>
const T& List<T>::last() const
{ return std::vector<T>::operator[](count() - 1); }

template<typename T>
T& List<T>::last()
{ return std::vector<T>::operator[](count() - 1); }

template<typename T>
List<T> List<T>::revert() const
{
	List<T> r;
	for (int i = count() - 1; i >= 0; i--)
		r.append(at(i));
	return r;
}


/*template<typename T>
String List<T>::dump() const
{
	return String("List of %1 (%2 items)").format({typeid(T).name(), count()});
}*/

template<typename T>
T List<T>::at(int index) const
{ return operator[](index); }

template<typename T>
T List<T>::operator[](int index) const
{ return std::vector<T>::operator[](index); }

template<typename T>
T& List<T>::operator[](int index)
{ return std::vector<T>::operator[](index); }
