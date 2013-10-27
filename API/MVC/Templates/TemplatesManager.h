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
 * @file MVC/Templates/TemplatesManager.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-01
 */

#ifndef _MVC_TEMPLATES_TEMPLATESMANAGER_H_
#define	_MVC_TEMPLATES_TEMPLATESMANAGER_H_

#include "Types/Map.h"

class Template;
class AbstractTemplateEngine;
class AbstractCompiledTemplate;
class String;
class Path;

/**
 * @class TemplatesManager MVC/Templates/TemplatesManager.h <TemplatesManager>
 * @brief The templates manager
 */
class TemplatesManager
{
public:
	~TemplatesManager();

	/**
	 * @brief Get the template manager instance
	 */
	static TemplatesManager* get();

	/**
	 * @brief Reload template engines from plugins
	 */
	void reloadEngines();

	/**
	 * @brief Get the default template engine
	 */
	AbstractTemplateEngine* defaultEngine() const;

	/**
	 * @brief Get a template by name
	 * @param name The template file path
	 * @return The template with the name @p name
	 */
	static AbstractCompiledTemplate*
	  compiledTemplate(const Path& filePath,
	                   AbstractTemplateEngine* tplEngine = nullptr);


	/**
	 * @brief Set the default template engine
	 * @param defaultEngine The new default template engine
	 */
	void setDefaultEngine(AbstractTemplateEngine* defaultEngine);

public:
	static AbstractTemplateEngine* engineByName(const String& name);

private:
	/**
	 * @brief Constructs the template manager instance
	 */
	TemplatesManager();

private:
	/**
	 * @brief The list of templates
	 */
	Map<String, AbstractCompiledTemplate*> _templates;

	/**
	 * @brief The template engines list
	 */
	Map<String, AbstractTemplateEngine*> _engines;

	/**
	 * @brief The default template engine
	 */
	AbstractTemplateEngine* _defaultEngine;
};

#endif // !_MVC_TEMPLATES_TEMPLATESMANAGER_H_
