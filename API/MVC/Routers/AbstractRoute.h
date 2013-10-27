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
 * @file MVC/Routers/AbstractRoute.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#ifndef _WPP_MVC_ROUTERS_ABSTRACTROUTE_H_
#define _WPP_MVC_ROUTERS_ABSTRACTROUTE_H_

#include "Types/String.h"
#include "Types/Map.h"

class Request;

/**
 * @class AbstractRoute MVC/Routers/AbstractRoute.h <AbstractRoute>
 * @brief A basic router route
 */
class AbstractRoute
{
public:
	struct Match
	{
		AbstractRoute* route;
		bool           matched;
		String         pattern;
		String         lang;
	};

	/**
	 * @brief Constructs a basic router route
	 * @param pattern The route pattern
	 */
	AbstractRoute(const String& id, const String& pattern);

	/**
	 * @brief Constructs a basic router route
	 * @param patterns The route patterns list
	 */
	AbstractRoute(const String& id, const Map<String, String>& patterns);

	virtual ~AbstractRoute(){}

	/**
	 * @brief Tests if the given path matches the route
	 * @param path The path to check
	 * @return true if the path @p path matches the route
	 */
	virtual Match match(const String& path);

	/**
	 * @brief Triggers the route
	 * @param path The requested path
	 * @param request The associated request
	 */
	virtual void trigger(const String& path,
	                     const String& pattern,
	                     Request* request) const;

	/**
	 * @brief Implements how to process the route
	 * @param args The arguments list
	 * @param request The associated request
	 */
	virtual void process(const Map<String, String>& args,
	                     Request* request) const = 0;

	String generatePath(const Map<String, String>& args,
	                    const String& lang) const;

	String id() const;

protected:
	String _id;

	/**
	 * @brief The route patterns (e.g. "en" => "/view-topic/{$id}/{$slug}")
	 */
	Map<String, String> _patterns;
};

#endif // !_WPP_MVC_ROUTERS_ABSTRACTROUTE_H_
