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
 * \file MVC/Templates/WppEngine/WppTplFuncInstance.h
 * \author Kévin Lesénéchal
 * \date 2012-03-18
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_WPPTPLFUNCINSTANCE_H
#define	_MVC_TEMPLATES_WPPENGINE_WPPTPLFUNCINSTANCE_H

#include "Types/List.h"
#include "MVC/Templates/WppEngine/WppTplExpr.h"

class WppTplFunc;
class Renderable;
class Template;

/**
 * \class WppTplFuncInstance MVC/Templates/WppEngine/WppTplFuncInstance.h <WppTplFuncInstance>
 * \brief A WppEngine function instance
 */
class WppTplFuncInstance
{
	//friend WppTplExpr* WppTplExpr::parse(const String& src);
	friend class WppTplExpr;
public:
	WppTplFuncInstance(WppTplFunc* func);
	
	Renderable exec(const Template* tpl) const;

private:
	/**
	 * \brief The associated function
	 */
	WppTplFunc* _func;
	
	/**
	 * \brief The function arguments
	 */
	List<WppTplExpr*> _args;
};

#endif
