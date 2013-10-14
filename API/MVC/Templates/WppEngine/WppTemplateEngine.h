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
 * \file MVC/Templates/WppEngine/WppTemplateEngine.h
 * \author Kévin Lesénéchal
 * \date 2011-12-16
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_WPPTEMPLATEENGINE_H
#define	_MVC_TEMPLATES_WPPENGINE_WPPTEMPLATEENGINE_H

#include "MVC/Templates/AbstractTemplateEngine.h"

#include "Types/Map.h"

class WppTplVarFilter;

/**
 * \class WppTemplateEngine MVC/Templates/WppEngine/WppTemplateEngine.h <WppTemplateEngine>
 * \brief Default WebCpp template engine
 */
class WppTemplateEngine : public AbstractTemplateEngine
{
public:
	static WppTemplateEngine* get();
	
	/**
	 * \brief Implements how to compile a template
	 * \param name The template name
	 * \return The compiled template
	 */
	virtual AbstractCompiledTemplate* compile(const String& filePath);
	
	/**
	 * \brief Get a filter by name
	 * \param name The filter name
	 */
	WppTplVarFilter* filter(const String& name) const;
	
	/**
	 * \brief Register a variable filter
	 * \param filter The variable filter to register
	 */
	void registerFilter(WppTplVarFilter* filter);

private:
	WppTemplateEngine();

private:
	/**
	 * \brief The list of filters
	 */
	Map<String, WppTplVarFilter*> _filters;
};

#endif
