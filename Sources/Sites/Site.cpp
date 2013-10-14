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
 * @file Sites/Site.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-11
 */

#include "Sites/Site.h"
#include "Sites/Module.h"
#include "MVC/Routers/AbstractRouter.h"
#include "Plugins/Plugin.h"
#include "System.h"

#include "DB/AbstractDbConnection.h"
#include "DB/DatabaseSystem.h"
#include "MVC/Routers/Router.h"
#include "Requests/SystemRouter.h"

Site::Site()
{
	_plugin = nullptr;
	_router = nullptr;
	_db = nullptr;
}

Site::~Site()
{
	if (_router != nullptr)
		delete _router;
	if (_db != nullptr)
		delete _db;
	for (Module* module : _modules)
		delete module;
}

void Site::registerModule(const String& id)
{
	_modules.append(Module::load(id));
}

Site* Site::load()
{
	Plugin* plugin = new Plugin("Site.so");
	Site* site = plugin->instance<Site>();
	site->_plugin = plugin;

	if (site->_db == nullptr)
	{
		site->_db = DatabaseSystem::dbms(System::setting("SQL.DBMS"))
		            ->newConnection();
		site->_db->connect(System::setting("SQL.Host"),
		                   System::setting("SQL.Login"),
		                   System::setting("SQL.Password"),
		                   System::setting("SQL.Database"),
		                   System::setting("SQL.Port") == "auto"
		                     ? 0
		                     : System::setting("SQL.Port").toInt());
	}

	return site;
}

//----------------------------------------------------------------------------//

Router* Site::router() const
{ return _router; }

Module* Site::module(const String& id) const
{
	for (int i = 0; i < _modules.count(); i++)
	{
		if (_modules[i]->id() == id)
			return _modules[i];
	}
	return nullptr;
}

List<Module*> Site::modules() const
{ return _modules; }

AbstractDbConnection* Site::dbConnection() const
{ return _db; }


void Site::setRouter(Router* router)
{
	_router = router;
	// FIXME: may not be at the right place
	_router->addPrefix("/sys/", System::get()->systemRouter());
}

void Site::setDbConnection(AbstractDbConnection* db)
{ _db = db; }
