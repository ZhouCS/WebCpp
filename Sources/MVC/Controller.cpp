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
 * @file MVC/Controller.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-14
 */

#include "MVC/Controller.h"
#include "Types/String.h"
#include "Requests/Request.h"
#include "Sites/Site.h"
#include "System.h"

#include "DB/AbstractDbConnection.h"

#include "MVC/Templates/Template.h"
#include "MVC/Templates/TemplatesManager.h"
#include "Sites/Module.h"
#include "Libs/Locale/TransManager.h"

#include "Exceptions/Controllers.h"
#include "MVC/Routers/AbstractRouter.h"
#include "Exceptions/Requests.h"

Controller::Controller()
{
	_module = nullptr;
	_request = nullptr;
}

Controller::Controller(const String& id)
{
	_module = nullptr;
	_request = nullptr;
	_id = id;
}

Controller::~Controller()
{

}

void Controller::registerActionMethod(const String& _id,
                                      void (Controller::*ptr)())
{
	String id = _id;

	if (id.contains("::"))
	{
		id = id.section("::", 1, -1);
		if (id.endsWith("Action"))
			id = id.removeRight(6);
	}

	_actions.set(id, ptr);
}

void Controller::exec(Request* request,
                      const String& action,
                      const Map<String, String>& args)
{
	if (!_actions.hasKey(action))
		throw Exceptions::NoSuchControllerAction(this, action);

	Controller* ctrl = newInstance();
	ctrl->_module = _module;
	ctrl->_request = request;
	ctrl->_args = args;

	try
	{
		(ctrl->*(ctrl->_actions[action]))();
	}
	catch (const Controller::NotFound& e)
	{ throw Exceptions::NotFound(request->uri()); }
	catch (const Controller::Forbidden& e)
	{ throw Exceptions::Forbidden(request->uri()); }
	catch (const Controller::Exit&)
	{ }

	delete ctrl;
}


Request* Controller::request() const
{ return _request; }

RequestStream& Controller::stream() const
{
	return _request->stream();
}

AbstractDbConnection* Controller::db() const
{
	return System::get()->site()->dbConnection();
}

AbstractDbResult* Controller::query(const String& sql) const
{
	return db()->query(sql, _request);
}

Template* Controller::tpl(const String& name,
                          AbstractTemplateEngine* tplEngine) const
{
	return new Template(name, _module, _request, tplEngine);
}

String Controller::tr(const String& text) const
{
	return TransManager::get()->translate(_module, "Controllers/" + _id,
	                                      _request->locale()->lang(), text);
}

String Controller::path(const String& id,
                        const StringList& args,
                        const String& lang) const
{
	Map<String, String> map;
	for (const String& arg : args)
		map[arg.tokenLeft("=")] = arg.tokenRight("=");
	return path(id, map, lang);
}

String Controller::path(const String& id,
                        const Map<String, String>& args,
                        const String& lang) const
{
	String moduleId, routeId;

	if (!id.contains("::"))
	{
		moduleId = _module->id();
		routeId = id;
	}
	else
	{
		moduleId = id.tokenLeft("::");
		routeId = id.tokenRight("::");
	}
	return System::get()->site()->module(moduleId)
	                            ->router()->generatePath(routeId, args, lang);
}

bool Controller::isPost() const
{ return _request->isPost(); }

UserAgent Controller::userAgent() const
{ return _request->userAgent(); }

Locale* Controller::locale() const
{ return _request->locale(); }

String Controller::env(const String& variable, const String& defaultValue) const
{ return _request->env(variable, defaultValue); }

bool Controller::hasGet(const String& variable) const
{ return _request->hasGet(variable); }

String Controller::get(const String& variable, const String& defaultValue) const
{ return _request->get(variable, defaultValue); }

String Controller::post(const String& variable,
                        const String& defaultValue) const
{ return _request->post(variable, defaultValue); }

String Controller::cookie(const String& variable,
                          const String& defaultValue) const
{ return _request->cookie(variable, defaultValue); }

String Controller::session(const String& variable,
                           const String& defaultValue) const
{ return _request->session(variable, defaultValue); }

void Controller::setSession(const String& name, const String& value) const
{ _request->setSession(name, value); }

String Controller::arg(const String& name, const String& defaultValue) const
{ return _args.get(name, defaultValue); }


void Controller::setHeader(const String& name, const String& value)
{ _request->setHeader(name, value); }

void Controller::setStatus(int httpCode)
{ _request->setStatus(httpCode); }

void Controller::setContentType(const String& mimeType, const String& charset)
{ _request->setContentType(mimeType, charset); }

void Controller::sendHeaders()
{ _request->sendHeaders(); }

void Controller::redirect(const String& location, int httpCode)
{ _request->redirect(location, httpCode); }

bool Controller::headersSent() const
{ return _request->headersSent(); }

String Controller::header(const String& name) const
{ return _request->header(name); }

void Controller::exit() const
{
	throw Controller::Exit();
}

Controller* Controller::byId(const String& id, Module* module)
{
	if (module == nullptr && !id.contains("::"))
		throw Exceptions::NoSuchController(id);
	else if (module != nullptr && !id.contains("::"))
		return module->controller(id);
	return System::get()->site()
	                    ->module(id.tokenLeft("::"))
	                    ->controller(id.tokenRight("::"));
}

//----------------------------------------------------------------------------//

bool Controller::isMaster() const
{ return !_id.isNull(); }

String Controller::id() const
{ return _id; }

String Controller::fullId() const
{ return (_module == nullptr ? "" : _module->id()) + "::" + _id; }
