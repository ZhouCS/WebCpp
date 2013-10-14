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
 * @file Object.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-23
 */

#include "Object.h"
#include "Types/Pair.h"
#include "Types/List.h"

void Object::connect(const String& event, Object* target, void (Object::*action)())
{
	_connections.insert(event, Pair<Object*, void (Object::*)()>(target, action));
}

void Object::emit(const String& event) const
{
	List<Pair<Object*, void (Object::*)()> > targets = _connections.get(event);
	for(int i = 0; i < targets.count(); i++)
		(targets[i].first()->*(targets[i].second()))();
}
