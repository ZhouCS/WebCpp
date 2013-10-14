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
 * @file Exceptions/Routers.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-10
 */

#ifndef _EXCEPTIONS_ROUTERS_H_
#define	_EXCEPTIONS_ROUTERS_H_

#include "Exceptions/Exception.h"

namespace Exceptions {

/**
 * @class NoRouteToPath Exceptions/Routers.h <Exceptions/Routers>
 * @brief Exception thrown when no route match the path
 */
class NoRouteToPath : public Exception
{
public:
	NoRouteToPath(const String& path) throw()
	  : Exception("NoRouteToPath",
	              String("No route match path “%1”").format(path))
	{}
};

class NoRoutePattern : public Exception
{
public:
	NoRoutePattern(const String& routeName)
	  : Exception("NoRoutePattern",
	              String("There is no pattern for the route “%1”")
	                .format(routeName))
	{}
};

}

#endif // !_EXCEPTIONS_ROUTERS_H_
