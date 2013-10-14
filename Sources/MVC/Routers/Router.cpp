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
 * @file MVC/Routers/Router.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#include "MVC/Routers/Router.h"
#include "MVC/Routers/AbstractRoute.h"
#include "MVC/Routers/Route.h"
#include "MVC/Routers/ViewRoute.h"
#include "MVC/Routers/FuncRoute.h"

#include "MVC/Templates/Template.h"

#include "Sites/Module.h"

#include "Types/Map.h"
#include "Libs/Settings.h"

#include "Exceptions/Routers.h"
#include "MVC/Controller.h"

Map<String, AbstractRoute::Match> Router::_cache;

Router::Router()
{

}

Router::~Router()
{
	for (Map<String, AbstractRouter*>::Iterator i(_prefixes); i.hasNext(); i++)
		delete i.value();
	for (Map<String, AbstractRoute*>::Iterator i(_routes); i.hasNext(); i++)
		delete i.value();
}

void Router::process(const String& path, Request* request)
{
	for (Map<String, AbstractRouter*>::Iterator i(_prefixes); i.hasNext(); i++)
	{
		if (path.startsWith(i.key()))
		{
			String subPath = path.substr(i.key().size());
			if (i.key().right(1) == "/")
				subPath = String("/") + subPath;

			i.value()->process(subPath, request);
			return;
		}
	}

	if (!_cache.hasKey(path))
	{
		for (Map<String, AbstractRoute*>::Iterator i(_routes); i.hasNext(); i++)
		{
			AbstractRoute::Match match = i.value()->match(path);
			if (match.matched)
			{
				_cache[path] = match;
				break;
			}
		}
	}

	if (_cache.hasKey(path))
	{
		AbstractRoute::Match match = _cache[path];
		match.route->trigger(path, match.pattern, request);
		return;
	}

	throw Exceptions::NoRouteToPath(path);
}

String Router::generatePath(const String& id,
                            const Map<String,String>& args,
                            const String& lang)
{ return _routes[id]->generatePath(args, lang); }

void Router::addPrefix(const String& prefix, AbstractRouter* router)
{ _prefixes.set(prefix, router); }

void Router::addPrefix(const String& prefix, const Module* module)
{ addPrefix(prefix, module->router()); }

void Router::addRoute(AbstractRoute* route)
{ _routes[route->id()] = route; }

void Router::addRoute(const String& id,
                      const String& pattern,
                      Controller* controller,
                      const String& action)
{ addRoute(new Route(id, pattern, controller, action)); }

void Router::addRoute(const String& id,
                      const String& pattern,
                      AbstractView* view)
{ addRoute(new ViewRoute(id, pattern, view)); }

void Router::addRoute(const String& id,
                      const String& pattern,
                      void (*funcPtr)(Request*, const Map<String, String>&))
{ addRoute(new FuncRoute(id, pattern, funcPtr)); }

Router* Router::loadFromFile(const Path& filePath, Module* module)
{
	Router* router = new Router;

	Map<String, Map<String, String>> settings
	                                 = Settings::fromIniFile(filePath).values();
	for (Map<String, Map<String, String>>::Iterator i(settings); i.hasNext(); i++)
	{
		AbstractRoute* route = nullptr;

		Map<String, String> patterns;

		for (Map<String, String>::Iterator j(i.value()); j.hasNext(); j++)
		{
			if (j.key() == "Pattern")
				patterns[""] = j.value();
			else if (j.key().startsWith("Pattern_"))
				patterns[j.key().tokenRight("_")] = j.value();
		}

		if (patterns.count() == 0)
			throw Exceptions::NoRoutePattern(i.key());

		if (i.value().hasKey("Action"))
			route = new Route(i.key(),
												patterns,
												Controller::byId(i.value().get("Action")
			                                   .section("::", 0, 0), module),
												i.value().get("Action").section("::", 1, 1));
		else if (i.value().hasKey("Template"))
			route = new ViewRoute(i.key(), patterns,
			                      new Template(i.value().get("Template"), module));

		router->addRoute(route);
	}

	return router;
}
