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
 * @file AbstractRouter.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#ifndef _MVC_ROUTERS_ABSTRACTROUTER_H_
#define _MVC_ROUTERS_ABSTRACTROUTER_H_

class String;
class Request;
template<typename Key, typename Value> class Map;

/**
 * @class AbstractRouter MVC/Routers/AbstractRouter.h <AbstractRouter>
 * @brief A basic router
 */
class AbstractRouter
{
public:
	virtual ~AbstractRouter(){}

	/**
	 * @brief Implements how to process an URL path
	 * @param path The URL path to process
	 * @param request The request to process
	 */
	virtual void process(const String& path, Request* request) = 0;

	virtual String generatePath(const String& id,
	                            const Map<String, String>& args,
	                            const String& lang) = 0;
};

#endif // !_MVC_ROUTERS_ABSTRACTROUTER_H_
