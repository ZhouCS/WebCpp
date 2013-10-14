/*************************************************************************
 * Copyright © 2011-2012 Kévin Lesénéchal <kevin.lesenechal@bilbax.com>  *
 *                                                                       *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.            *
 *                                                                       *
 * * WebCpp is free software: you can redistribute it and/or modify it     **
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/

/**
 * \file MVC/Templates/WppEngine/WppTplFunc.h
 * \author Kévin Lesénéchal
 * \date 2012-03-07
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_WPPTPLFUNC_H
#define	_MVC_TEMPLATES_WPPENGINE_WPPTPLFUNC_H

#include "Types/String.h"

class Renderable;
template<typename T> class List;

/**
 * \class WppTplFunc MVC/Templates/WppEngine/WppTplFunc.h <WppTplFunc>
 * \brief A WebCpp template engine function
 */
class WppTplFunc
{
	friend class WppTplExpr;
public:
	WppTplFunc(const String& name, Renderable (*func)(const List<Renderable>& args));
	
	static void registerFunction(const String& name, Renderable (*func)(const List<Renderable>& args));
	
	static WppTplFunc* byName(const String& name);
	
	Renderable exec(const List<Renderable>& args) const;

private:
	static Map<String, WppTplFunc*> _funcs;
	
	String _name;
	
	Renderable (*_func)(const List<Renderable>& args);
};

#endif
