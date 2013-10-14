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
 * @file Object.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-23
 */

#ifndef _OBJECT_H_
#define	_OBJECT_H_

#include "Types/Pair.h"
#include "Types/String.h"
#include "Types/MultiMap.h"

/**
 * @brief Root entity class
 */
class Object
{
public:
	void connect(const String& event, Object* target, void (Object::*action)());

protected:
	void emit(const String& event) const;

private:
	MultiMap<String, Pair<Object*, void (Object::*)()>> _connections;
};

#endif // !_OBJECT_H_
