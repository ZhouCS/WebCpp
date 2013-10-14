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
 * @file DB/DatabaseSystem.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-06-26
 */

#include "DB/DatabaseSystem.h"
#include "Libs/Dir.h"
#include "Plugins/Plugin.h"
#include "Types/Map.h"
#include "System.h"

#include "Exceptions/Db.h"

Map<String, DatabaseSystem*> DatabaseSystem::_dbmsList;

DatabaseSystem::DatabaseSystem(const String& id)
{
	_id = id;
	_plugin = nullptr;
}

DatabaseSystem::~DatabaseSystem()
{

}

void DatabaseSystem::reloadDbmsList()
{
	deleteDbmsList();
	StringList dbmsList = Dir("WebCpp/Plugins/DBMS/").entries();
	for (const String& dbmsName : dbmsList)
	{
		Plugin* plugin = new Plugin("WebCpp/Plugins/DBMS/"+dbmsName);
		DatabaseSystem* dbms = plugin->instance<DatabaseSystem>();
		dbms->_plugin = plugin;
		_dbmsList[dbms->id()] = dbms;
	}
}

void DatabaseSystem::deleteDbmsList()
{
	for (Map<String, DatabaseSystem*>::Iterator i(_dbmsList); i.hasNext(); i++)
		delete i.value();
	_dbmsList.clear();
}

//----------------------------------------------------------------------------//

DatabaseSystem* DatabaseSystem::dbms(const String& id)
{
	DatabaseSystem* dbms = _dbmsList.get(id, nullptr);
	if (dbms == nullptr)
		throw Exceptions::NoSuchDbms(id);
	return dbms;
}

String DatabaseSystem::id() const
{ return _id; }
