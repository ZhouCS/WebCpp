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
 * @file MVC/Templates/Template.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-15
 */

#ifndef _MVC_TEMPLATES_TEMPLATE_H_
#define _MVC_TEMPLATES_TEMPLATE_H_

#include "MVC/AbstractView.h"
#include "Types/Path.h"

class AbstractTemplateEngine;
class AbstractCompiledTemplate;
class Module;
class Request;

/**
 * @class Template MVC/Templates/Template.h <Template>
 * @brief A template view
 */
class Template : public AbstractView
{
public:
	/**
	 * @brief Contructs a template
	 * @param name The template name
	 * @param module The module which requests the template
	 * @param request The associated request
	 * @param engine The template engine to use for rendering
	 */
	Template(const String& name,
	         const Module* module = nullptr,
	         Request* request = nullptr,
	         AbstractTemplateEngine* engine = nullptr);

	/**
	 * @brief Executes the template and returns the output
	 */
	String exec();

	/**
	 * @brief Renders the template and send the result to the output
	 */
	void render();

	/**
	 * @brief Get the template file path
	 */
	Path filePath() const;

	/**
	 * @brief Get the compiled template instance
	 */
	AbstractCompiledTemplate* compiledTpl() const;

	/**
	 * @brief Set the request to render this template
	 */
	void setRequest(Request* request);

public:
	/**
	 * @brief Resolves a template name into its file path
	 * @param name The template name (e.g. "Sys::About.html")
	 * @param defaultModule The module reference to use for relative resolutions
	 * @return The template file path
	 * @warning This function will NOT check whether the template exists or not
	 *
	 * This static method resolves a template name @p name into its file path. A
	 * template name is in the form of "Namespace::File" where the namespace is
	 * either a module name (e.g. "Forum::File"), either the "Sys" namespace (e.g.
	 * "Sys::File") which refers to the WebCpp internal templates, either empty
	 * ("::File") for site-general templates, either missing ("File"). If the
	 * namespace is missing, it is a relative resolution.
	 *
	 * In cas of relative resolution, the name resolution is done relatively to
	 * the specified module @p defaultModule. If @p defaultModule is null,
	 * relative resolutions are made from the website.
	 *
	 * @code
	 * Module* module = Module::byId("MyModule");
	 *
	 * // Absolute name resolutions
	 * Template::resolveName("Forum::ViewTopic.html"); // ./Mods/Forum/Templates/ViewTopic.html
	 * Template::resolveName("::LegalNotices.html"); // ./Templates/LegalNotices.html
	 * Template::resolveName("Sys::Exception.html"); // ./WebCpp/Templates/Exception.html
	 *
	 * // Relative name resolutions
	 * Template::resolveName("Foo.html", module); // ./Mods/MyModule/Templates/Foo.html
	 * Template::resolveName("Bar.hmtl"); // ./Templates/Bar.html
	 * @endcode
	 *
	 * Be careful, this function will NOT check whether the template exists or
	 * not.
	 */
	static String resolveName(const String& name,
	                          const Module* defaultModule = nullptr);

private:
	/**
	 * @brief The template file path
	 */
	Path _filePath;

	/**
	 * @brief The template engine to render the template
	 */
	AbstractTemplateEngine* _engine;

	/**
	 * @brief The compiled template
	 */
	AbstractCompiledTemplate* _compiled;
};

#endif // !_MVC_TEMPLATES_TEMPLATE_H_
