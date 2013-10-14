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
 * @file MVC/Routers/FuncRoute.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-16
 */

#ifndef _MVC_ROUTERS_FUNCROUTE_H_
#define _MVC_ROUTERS_FUNCROUTE_H_

#include "MVC/Routers/AbstractRoute.h"

class String;
class Request;

/**
 * @class FuncRoute MVC/Routers/FuncRoute.h <FuncRoute>
 * @brief A route to a function handler
 */
class FuncRoute : public AbstractRoute
{
public:
	/**
	 * @brief Constructs a route to a function handler
	 * @param id The route ID
	 * @param pattern The route pattern
	 * @param The function handler pointer
	 */
	FuncRoute(const String& id,
	          const String& pattern,
	          void (*funcPtr)(Request*, const Map<String, String>&));

	FuncRoute(const String& id,
	          const Map<String, String>& patterns,
	          void (*funcPtr)(Request*, const Map<String, String>&));

	/**
	 * @brief Implements how to process the route
	 * @param args The arguments list
	 * @param request The associated request
	 */
	virtual void process(const Map<String, String>& args, Request* request) const;

private:
	void (*_funcPtr)(Request*, const Map<String, String>&);
};

#endif // !_MVC_ROUTERS_FUNCROUTE_H_
