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
 * @file MVC/Routers/FuncRoute.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-16
 */

#include "MVC/Routers/FuncRoute.h"

FuncRoute::FuncRoute(const String& id,
                     const String& pattern,
										 void (*funcPtr)(Request*, const Map<String, String>&))
  : AbstractRoute(id, pattern)
{
	_funcPtr = funcPtr;
}

FuncRoute::FuncRoute(const String& id,
                     const Map<String,String>& patterns,
										 void (*funcPtr)(Request*, const Map<String, String>&))
  : AbstractRoute(id, patterns)
{
	_funcPtr = funcPtr;
}

void FuncRoute::process(const Map<String,String>& args, Request* request) const
{
	_funcPtr(request, args);
}
