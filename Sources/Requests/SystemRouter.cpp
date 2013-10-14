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
 * @file Requests/SystemRouter.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-15
 */

#include "Requests/SystemRouter.h"
#include "Requests/Request.h"
#include "Requests/RequestProfile.h"

#include "System.h"
#include "MVC/AbstractView.h"
#include "MVC/Templates/Template.h"

#include "Exceptions/Requests.h"

SystemRouter::SystemRouter()
{
	if (System::isDebug())
	{
		addRoute("About",   "/",        &about);
		addRoute("Profile", "/profile", &profile);
	}
}

void SystemRouter::about(Request* request, const Map<String, String>&)
{
	View tpl = new Template("Sys::About.html", nullptr, request);
	tpl["webcppVersion"] = System::get()->version();
	tpl["httpServer"] = request->env("SERVER_NAME", "(unknown)");
	tpl["absolutePath"] = ABS;
	tpl["runDir"] = System::get()->runDir();
	tpl->render();
}

void SystemRouter::profile(Request* request, const Map<String, String>&)
{
	int id = request->get("id");
	if (id < 0 || id > 255)
		throw Exceptions::Forbidden(request->uri());

	RequestProfile* profile = RequestProfile::profile(static_cast<uint8_t>(id));
	if (profile == nullptr)
		throw Exceptions::NotFound(request->uri());

	request->setContentType("application/json");

	View tpl = new Template("Sys::Profile.json", nullptr, request);
	tpl["webcppVersion"] = System::get()->version();
	tpl["totalExecTime"] =
	    static_cast<float>(profile->chronoTime(RequestProfile::Total));
	tpl["systemExecTime"] =
	    static_cast<float>(profile->chronoTime(RequestProfile::System));
	tpl["sqlExecTime"] =
	    static_cast<float>(profile->chronoTime(RequestProfile::Database));
	tpl["templatesExecTime"] =
	    static_cast<float>(profile->chronoTime(RequestProfile::Templates));
	tpl["sqlQueryCount"] = profile->counter(RequestProfile::SqlQueries);
	tpl->render();
}
