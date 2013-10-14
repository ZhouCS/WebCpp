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
 * @file DB/DatabaseSystem.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-06-26
 */

#ifndef _DB_DATABASESYSTEM_H_
#define	_DB_DATABASESYSTEM_H_

#include "Types/String.h"

class Plugin;

/**
 * @class DatabaseSystem DB/DatabaseSystem.h <DatabaseSystem>
 * @brief An interface to a DBMS
 */
class DatabaseSystem
{
public:
	/**
	 * @brief Constructs a DBMS instance
	 * @param id The DBMS ID
	 */
	DatabaseSystem(const String& id);

	/**
	 * @brief Destructs the DBMS instance
	 */
	virtual ~DatabaseSystem();

	/**
	 * @brief Reloads DBMS list from plugins
	 */
	static void reloadDbmsList();

	/**
	 * @brief Deletes all DBMS instances
	 */
	static void deleteDbmsList();

	/**
	 * @brief Implements how to get a new DBMS connection instance
	 * @return The new DBMS connection instance
	 */
	virtual AbstractDbConnection* newConnection() const = 0;

	/**
	 * @brief Get a DBMS instance by ID
	 * @param id The DBMS ID
	 * @return The DBMS with the specified ID
	 */
	static DatabaseSystem* dbms(const String& id);

	/**
	 * @brief Get the DBMS ID
	 * @return The DBMS ID
	 */
	String id() const;

private:
	/**
	 * @brief The DBMS list
	 */
	static Map<String, DatabaseSystem*> _dbmsList;

	/**
	 * @brief The DBMS ID
	 */
	String _id;

	/**
	 * @brief The associated plugin
	 */
	Plugin* _plugin;
};

#endif // !_DB_DATABASESYSTEM_H_
