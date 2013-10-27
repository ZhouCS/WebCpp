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
 * @file MVC/Routers/ViewRoute.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-15
 */

#ifndef _WPP_MVC_ROUTERS_VIEWROUTE_H_
#define _WPP_MVC_ROUTERS_VIEWROUTE_H_

#include "MVC/Routers/AbstractRoute.h"

class AbstractView;
class Request;

/**
 * @class ViewRoute MVC/Routers/ViewRoute.h <ViewRoute>
 * @brief A route to a view
 */
class ViewRoute : public AbstractRoute
{
public:
	/**
	 * @brief Constructs view route
	 * @param id The view route ID
	 * @param pattern The route pattern
	 * @param view The view to render
	 */
	ViewRoute(const String& id, const String& pattern, AbstractView* view);

	/**
	 * @brief Constructs view route
	 * @param id The view route ID
	 * @param patterns The route patterns list
	 * @param view The view to render
	 */
	ViewRoute(const String& id,
	          const Map<String, String>& patterns,
	          AbstractView* view);

	/**
	 * @brief Implements how to process the route
	 * @param args The arguments list
	 * @param request The associated request
	 */
	virtual void process(const Map<String, String>& args, Request* request) const;

private:
	/**
	 * @brief The view to render
	 */
	AbstractView* _view;
};

#endif // !_WPP_MVC_ROUTERS_VIEWROUTE_H_
