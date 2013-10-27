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
 * @file MVC/Routers/Route.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-07
 */

#ifndef _WPP_MVC_ROUTERS_ROUTE_H_
#define _WPP_MVC_ROUTERS_ROUTE_H_

#include "MVC/Routers/AbstractRoute.h"

class Controller;
class Request;

/**
 * @class Route MVC/Routers/Route.h <Route>
 * @brief A route to a controller/action
 */
class Route : public AbstractRoute
{
public:
	/**
	 * @brief Constructs a route
	 * @param id The route ID
	 * @param pattern The route pattern
	 * @param controller The associated controller
	 * @param action The controller action to call
	 */
	Route(const String& id,
	      const String& pattern,
	      Controller* controller,
	      const String& action);

	Route(const String& id,
	      const Map<String, String>& patterns,
	      Controller* controller,
	      const String& action);

	/**
	 * @brief Implements how to process the route
	 * @param args The arguments list
	 * @param request The associated request
	 */
	virtual void process(const Map<String, String>& args, Request* request) const;

protected:
	/**
	 * @brief The controller to call
	 */
	Controller* _controller;

	/**
	 * @brief The controller action to call
	 */
	String _action;
};

#endif // !_WPP_MVC_ROUTERS_ROUTE_H_
