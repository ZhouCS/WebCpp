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
 * \file MVC/Templates/WppEngine/WppCompiledTemplate.h
 * \author Kévin Lesénéchal
 * \date 2012-01-01
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_WPPCOMPILEDTEMPLATE_H
#define	_MVC_TEMPLATES_WPPENGINE_WPPCOMPILEDTEMPLATE_H

#include "MVC/Templates/AbstractCompiledTemplate.h"

class WppTplBlock;

/**
 * \class WppCompiledTemplate MVC/Templates/WppEngine/WppCompiledTemplate.h <WppCompiledTemplate>
 * \brief WebBase template engine compiled template
 */
class WppCompiledTemplate : public AbstractCompiledTemplate
{
	friend class WppTemplateEngine;
public:
	WppCompiledTemplate(const String& name);
	
	/**
	 * \brief Renders the compiled template
	 * \param tpl The template instance to render
	 * \return The output
	 */
	virtual String render(const Template* tpl);

private:
	WppTplBlock* _mainBlock;
};

#endif

