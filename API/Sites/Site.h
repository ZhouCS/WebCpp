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
 * @file Sites/Site.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-11
 */

#ifndef _SITES_SITE_H_
#define	_SITES_SITE_H_

#include "Types/List.h"

class Module;
class Plugin;
class Router;
class AbstractDbConnection;

/**
 * @class Site Sites/Site.h <Site>
 * @brief A basic website
 */
class Site
{
public:
	/**
	 * @brief Destructs the site
	 */
	virtual ~Site();

	/**
	 * @brief Registers a module by its identifier
	 * @param id The module identifier to register
	 */
	void registerModule(const String& id);

	/**
	 * @brief Loads the module from the plugin Site.so
	 */
	static Site* load();


	/**
	 * @brief Get the site main router
	 */
	Router* router() const;

	/**
	 * @brief Get a module by identifier
	 * @param id The module identifier
	 * @return The module with the specified identifier, otherwise a null pointer
	 */
	Module* module(const String& id) const;

	/**
	 * @brief Get the modules list
	 */
	List<Module*> modules() const;

	/**
	 * @brief Get the default database connection
	 */
	AbstractDbConnection* dbConnection() const;


	/**
	 * @brief Set the module's main router
	 * @param router The main router instance
	 */
	void setRouter(Router* router);

	/**
	 * @brief Set the default database connection
	 * @brief db The database connection
	 */
	void setDbConnection(AbstractDbConnection* db);

protected:
	Site();

private:
	/**
	 * @brief The list of modules
	 */
	List<Module*> _modules;

	/**
	 * @brief The site plugin
	 */
	Plugin* _plugin;

	/**
	 * @brief The main router
	 */
	Router* _router;

	/**
	 * @brief The default SQL connection
	 */
	AbstractDbConnection* _db;
};

#endif // !_SITES_SITE_H_
