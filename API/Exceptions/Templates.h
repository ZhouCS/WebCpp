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
 * @file Exceptions/Templates.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-01
 */

#ifndef _WPP_EXCEPTIONS_TEMPLATES_H_
#define	_WPP_EXCEPTIONS_TEMPLATES_H_

#include "Exceptions/Exception.h"
#include "MVC/Templates/AbstractCompiledTemplate.h"
#include "MVC/Templates/Template.h"
#include "Libs/IO/File.h"
#include "Libs/CodeHighlighter.h"

namespace Exceptions {

/**
 * @class TemplateCompilation Exceptions/Templates.h <Exceptions/Templates>
 * @brief Exception thrown when a template fails to compile
 */
class TemplateCompilation : public Exception
{
public:
	TemplateCompilation(AbstractCompiledTemplate* tpl,
	                    const String& message) throw()
	  : Exception("TemplateCompilation",
	              String("Template “%1” failed to compile: %2")
	                .format({tpl->filePath().relativePath(), message}))
	{
		_htmlMessage = "<p>The template file “<code>"
		               + tpl->filePath().relativePath().htmlEscape() + "</code>” "
		               "failed to compile.</p><h3>Template</h3>"
		               + CodeHighlighter::codeBlock("plain",
		                                          File::getContent(tpl->filePath()))
		               + "<h3>Error message</h3><p>" + message.htmlEscape()
		               + ".</p>";
	}
};

class TemplateExecution : public Exception
{
public:
	TemplateExecution(Template* tpl, const String& message) throw()
	  : Exception("TemplateExecution",
	              String("Failed to execute template “%1”: %2")
	                .format({tpl->filePath().relativePath(), message}))
	{
		_htmlMessage = "<p>The template file “<code>"
		               + tpl->filePath().relativePath().htmlEscape() + "</code>” "
		               "failed to execute.</p><h3>Template</h3>"
		               + CodeHighlighter::codeBlock("plain",
		                                          File::getContent(tpl->filePath()))
		               + "<h3>Error message</h3>0<p>" + message.htmlEscape()
		               + ".</p>";
	}
};

}

#endif // !_WPP_EXCEPTIONS_TEMPLATES_H_
