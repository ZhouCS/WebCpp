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
 * @file MVC/Routers/Router.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#ifndef _MVC_ROUTERS_ROUTER_H_
#define _MVC_ROUTERS_ROUTER_H_

#include "MVC/Routers/AbstractRouter.h"
#include "MVC/Routers/AbstractRoute.h"

#include "Types/List.h"
#include "Types/Map.h"

class String;
class Request;
class Module;
class Controller;
class AbstractView;
class Path;

/**
 * @class Router MVC/Routers/Router.h <Router>
 * @brief A simple and useful router
 */
class Router : public AbstractRouter
{
public:
	/**
	 * @brief Constructs an empty router
	 */
	Router();

	virtual ~Router();

	/**
	 * @brief Implements how to process an URL path
	 * @param path The requested path
	 * @param request The request to process
	 */
	virtual void process(const String& path, Request* request);

	virtual String generatePath(const String& id,
	                            const Map<String, String>& args,
	                            const String& lang);

	/**
	 * @brief Add a prefix to the router
	 * @param prefix The route prefix (e.g. /forum/)
	 * @param router The delegate router
	 */
	void addPrefix(const String& prefix, AbstractRouter* router);

	/**
	 * @brief Add a module's main router as a new prefix in this router
	 * @param route The route prefix (e.g. /forum/)
	 * @param module The module that contains the router to add
	 */
	void addPrefix(const String& prefix, const Module* module);

	/**
	 * @brief Adds a route to the router
	 * @param route The route to add
	 */
	void addRoute(AbstractRoute* route);

	/**
	 * @brief Adds a controller route to the router
	 * @param id The route ID
	 * @param pattern The route path
	 * @param controllerId The controller to call
	 * @param action The action associated to the controller
	 */
	void addRoute(const String& id,
	              const String& pattern,
	              Controller* controller,
	              const String& action);

	/**
	 * @brief Adds a view route to the router
	 * @param id The route ID
	 * @param pattern The route path
	 * @param view The view to render
	 */
	void addRoute(const String& id, const String& pattern, AbstractView* view);

	/**
	 * @brief Adds a function route to the router
	 * @param id The route ID
	 * @param pattern The route path
	 * @param funcPtr The function pointer
	 */
	void addRoute(const String& id,
	              const String& pattern,
	              void (*funcPtr)(Request*, const Map<String, String>&));

public:
	static Router* loadFromFile(const Path& filePath, Module* module = nullptr);

protected:
	/**
	 * @brief The list of prefixes
	 */
	Map<String, AbstractRouter*> _prefixes;

	/**
	 * @brief The list of routes
	 */
	Map<String, AbstractRoute*> _routes;

private:
	static Map<String, AbstractRoute::Match> _cache;
};

#endif // !_MVC_ROUTERS_ROUTER_H_
