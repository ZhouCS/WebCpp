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

#include "Exceptions/Controllers.h"


/**
 * @file Sites/Module.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-10
 */

#include "Sites/Module.h"
#include "Plugins/Plugin.h"
#include "MVC/Controller.h"
#include "MVC/Templates/Template.h"
#include "MVC/Routers/AbstractRouter.h"
#include "System.h"
#include "Sites/Site.h"

Module::Module(const String& id)
{
	_id = id;
	_plugin = nullptr;
	_router = nullptr;
}

Module::~Module()
{
	for (Controller* controller : _controllers)
		delete controller;
}

Module* Module::load(const String& id)
{
	Plugin* plugin = new Plugin("Mods/" + id + "/" + id + ".so");
	Module* module = plugin->instance<Module>();
	module->_plugin = plugin;
	if (id != module->_id)
		throw Exceptions::ExceptionNotImplemented();

	return module;
}

void Module::unload()
{

	//TODO: delete controllers / models / repositories / views
}

void Module::registerController(Controller* controller)
{
	controller->_module = this;
	_controllers.append(controller);
}

void Module::registerModel(Model* model)
{ _models.append(model); }

void Module::registerRepository(Repository* repository)
{ _repositories.append(repository); }

void Module::registerView(View* view)
{ _views.append(view); }

//----------------------------------------------------------------------------//

String Module::id() const
{ return _id; }

AbstractRouter* Module::router() const
{ return _router; }

Controller* Module::controller(const String& id) const
{
	for (Controller* controller : _controllers)
	{
		if (controller->id() == id)
			return controller;
	}

	throw Exceptions::NoSuchController(_id + "::" + id);
	return nullptr; // Supresses compiler's warnings
}

Template* Module::tpl(const String&,
                      AbstractTemplateEngine*) const
{
	// TODO: implement me
	throw Exceptions::ExceptionNotImplemented();
	return nullptr;
	//return new Template(name, this, 0, tplEngine);
}

String Module::absolutePath() const
{ return ABS + "Mods/" + _id + "/"; }

void Module::setRouter(AbstractRouter* router)
{ _router = router; }

Module* Module::byId(const String& id)
{ return System::get()->site()->module(id); }
