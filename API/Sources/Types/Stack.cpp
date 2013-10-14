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
 * @file Types/Stack.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-13
 */

template<typename T>
Stack<T>::Stack()
{ }

template<typename T>
T& Stack<T>::top()
{ return std::stack<T>::top(); }

template<typename T>
T Stack<T>::top() const
{ return std::stack<T>::top(); }

template<typename T>
void Stack<T>::push(const T& value)
{ std::stack<T>::push(value); }

template<typename T>
T Stack<T>::pop()
{
	T& val = top();
	std::stack<T>::pop();
	return val;
}

template<typename T>
int Stack<T>::count() const
{ return std::stack<T>::size(); }

template<typename T>
bool Stack<T>::isEmpty() const
{ return std::stack<T>::empty(); }
