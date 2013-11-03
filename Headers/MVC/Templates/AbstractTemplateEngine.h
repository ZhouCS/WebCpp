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
 * @file MVC/Templates/AbstractTemplateEngine.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-16
 */

#ifndef _WPP_MVC_TEMPLATES_ABSTRACTTEMPLATEENGINE_H_
#define	_WPP_MVC_TEMPLATES_ABSTRACTTEMPLATEENGINE_H_

class AbstractCompiledTemplate;
class Path;

#include "Types/String.h"

/**
 * @class AbstractTemplateEngine MVC/Templates/AbstractTemplateEngine.h
 *        <AbstractTemplateEngine>
 * @brief A template engine interface
 */
class AbstractTemplateEngine
{
public:
	/**
	 * @brief Constructs a template engine
	 * @param id The template engine's ID
	 */
	AbstractTemplateEngine(const String& id);

	virtual ~AbstractTemplateEngine(){}

	/**
	 * @brief Compiles a template by file path
	 * @param filePath The template's file path to compile
	 * @return The compiled template
	 */
	AbstractCompiledTemplate* compile(const Path& filePath);

	/**
	 * @brief Implements how to compile a template
	 * @param name The template file path
	 * @return The compiled template
	 */
	virtual AbstractCompiledTemplate* compileImpl(const Path& filePath) = 0;


	String id() const;

private:
	/**
	 * @brief The engine's ID
	 */
	String _id;
};

#endif // !_WPP_MVC_TEMPLATES_ABSTRACTTEMPLATEENGINE_H_
