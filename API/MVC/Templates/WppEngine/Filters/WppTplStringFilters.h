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
 * \file MVC/Templates/WppEngine/Filters/WppTplStringFilters.h
 * \author Kévin Lesénéchal
 * \date 2012-01-16
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_FILTERS_WPPTPLSTRINGFILTERS_H
#define	_MVC_TEMPLATES_WPPENGINE_FILTERS_WPPTPLSTRINGFILTERS_H

#include "MVC/Templates/WppEngine/WppTplVarFilter.h"

#include "Types/Renderable.h"

namespace WppTplFilters {

class Raw : public WppTplVarFilter
{
public:
	Raw() : WppTplVarFilter("raw")
	{ _rawOutput = true; }
	
	virtual Renderable apply(const Renderable& input) const
	{ return input; }
};


}

#endif
