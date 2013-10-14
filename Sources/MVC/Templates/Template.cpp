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
 * @file MVC/Templates/Template.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-15
 */

#include "System.h"
#include "MVC/Templates/Template.h"
#include "MVC/Templates/TemplatesManager.h"
#include "Requests/Request.h"
#include "MVC/Templates/AbstractCompiledTemplate.h"
#include "Sites/Site.h"
#include "Sites/Module.h"
#include "Libs/Chrono.h"
#include "Requests/RequestProfile.h"
#include "Libs/Locale/Locale.h"

Template::Template(const String& name,
                   const Module* module,
                   Request* request,
                   AbstractTemplateEngine* engine)
{
	_filePath = Template::resolveName(name, module);
	_engine = engine == nullptr
	          ? TemplatesManager::get()->defaultEngine()
	          : engine;

	Chrono chrono(true);
	_compiled = TemplatesManager::get()->compiledTemplate(_filePath, _engine);
	chrono.stop();

	if (request != nullptr)
	{
		request->profile()->addChronoTime(RequestProfile::Templates,
		                                  chrono.elapsed());
		setRequest(request);
	}
}

String Template::exec()
{
	Chrono chrono(true);
	String r = _compiled->render(this);
	request()->profile()->addChronoTime(RequestProfile::Templates,
	                                    chrono.elapsed());
	return r;
}

void Template::render()
{
	if (!request()->headersSent())
		request()->sendHeaders();
	request()->stream() << exec();
}

String Template::resolveName(const String& name, const Module* defaultModule)
{
	String dir, fileName;

	if (name.contains("::"))
	{
		String ns = name.tokenLeft("::");
		fileName = name.tokenRight("::");
		if (ns.isEmpty())
			dir = "Templates/";
		else if (ns == "Sys")
			dir = "WebCpp/Templates/";
		else
			dir = Module::byId(ns)->absolutePath() + "Templates/";
	}
	else if (defaultModule == nullptr)
	{
		dir = "Templates/";
		fileName = name;
	}
	else
	{
		dir = defaultModule->absolutePath() + "Templates/";
		fileName = name;
	}
	return dir + fileName;
}

//----------------------------------------------------------------------------//

Path Template::filePath() const
{ return _filePath; }

void Template::setRequest(Request* request)
{
	AbstractView::setRequest(request);

	set("_locale",    request->locale()->name());
	set("_lang",      request->locale()->lang());
	set("_mimeType",  request->mimeType());
	set("_charset",   request->charset());
	set("_profileId", request->profile()->id());

	Variant profiler = "<script>var _sys_profileId = "
	                   + String(request->profile()->id())
	                   + ";</script><script src=\"/sys/js/devbar.js\"></script>";
	profiler.setRaw();
	set("_profiler",  profiler);
}
