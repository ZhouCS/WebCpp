/********************************************************************************
 * Copyright © 2011 Kévin Lesénéchal <kevin.lesenechal@bilbax.com>              *
 *                                                                              *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.                   *
 *                                                                              *
 * * WebCpp is free software: you can redistribute it and/or modify it     **
 * it under the terms of the GNU Affero General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU Affero General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the GNU Affero General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 ********************************************************************************/

/**
 * \file MVC/View.h
 * \author Kévin Lesénéchal
 * \date 2011-12-15
 */

#ifndef _MVC_VIEW_H
#define _MVC_VIEW_H

#include "Types/Map.h"
#include "Types/String.h"

class Renderable;

/**
 * \class View MVC/View.h <View>
 * \brief A basic view
 */
class View
{
public:
	View();
	
	virtual void render() = 0;
	
	const Renderable& get(const String& key) const;
	
	void set(const String& key, const Renderable& var);

private:
	/**
	 * \brief The view variables
	 */
	Map<String, const Renderable*> _vars;
};

#endif
