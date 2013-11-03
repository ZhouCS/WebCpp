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
 * @file MVC/Templates/AbstractCompiledTemplate.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-17
 */

#ifndef _WPP_MVC_TEMPLATES_ABSTRACTCOMPILEDTEMPLATE_H_
#define	_WPP_MVC_TEMPLATES_ABSTRACTCOMPILEDTEMPLATE_H_

#include "Types/Path.h"
#include "Types/DateTime.h"

class Template;
class String;
class AbstractTemplateEngine;

/**
 * @class AbstractCompiledTemplate MVC/Templates/AbstractCompiledTemplate.h
 *        <AbstractCompiledTemplate>
 * @brief A compiled template
 */
class AbstractCompiledTemplate
{
public:
	AbstractCompiledTemplate(const Path& filePath,
	                         AbstractTemplateEngine* engine);

	virtual ~AbstractCompiledTemplate(){}

	/**
	 * @brief Adds a template as a dependency
	 * @param tpl The template to add as a dependency
	 */
	void addDependency(AbstractCompiledTemplate* tpl);

	/**
	 * @brief Check this template of updates
	 * @return true if updated, otherwise false
	 */
	bool update();

	/**
	 * @brief Renders the compiled template
	 * @param tpl The template instance to render
	 * @return The output
	 */
	virtual String render(Template* tpl) = 0;

	Path     filePath() const;
	DateTime compileTime() const;
	bool     dependsOn(AbstractCompiledTemplate* tpl) const;

private:
	AbstractTemplateEngine* _engine;
	Path     _filePath;
	DateTime _compileTime;
	List<AbstractCompiledTemplate*> _dependencies;
};

#endif // !_WPP_MVC_TEMPLATES_ABSTRACTCOMPILEDTEMPLATE_H_
