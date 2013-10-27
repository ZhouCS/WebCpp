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
 * @file Sites/Module.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-10
 */

#ifndef _WPP_SITES_MODULE_H_
#define _WPP_SITES_MODULE_H_

#include "Types/String.h"
#include "Types/List.h"

class Plugin;
class Controller;
class Model;
class Repository;
class View;
class AbstractRouter;
class Template;
class AbstractTemplateEngine;

/**
 * @class Module Sites/Module.h <Module>
 * @brief A module
 */
class Module
{
public:
	Module(const String& id);

	/**
	 * @brief Destructs the module
	 */
	virtual ~Module();

	/**
	 * @brief Register a controller
	 * @param controller The controller to register
	 */
	void registerController(Controller* controller);

	/**
	 * @brief Register a model
	 * @param model The model to register
	 */
	void registerModel(Model* model);

	/**
	 * @brief Register a repository
	 * @param repository The repository to register
	 */
	void registerRepository(Repository* repository);

	/**
	 * @brief Register a view
	 * @param view The view to register
	 */
	void registerView(View* view);

	/**
	 * @brief Unloads the module
	 */
	void unload();


	/**
	 * @brief Get the module identifier
	 */
	String id() const;

	/**
	 * @brief Get the module's main router
	 */
	AbstractRouter* router() const;

	/**
	 * @brief Get a controller by its identifier
	 * @param id The controller identifier to get
	 * @return The controller with the specified identifier
	 */
	Controller* controller(const String& id) const;

	/**
	 * @brief Get a template by name
	 * @param name The template name
	 * @param tplEngine The template engine
	 * @return The template @p name
	 */
	Template* tpl(const String& name,
	              AbstractTemplateEngine* tplEngine = nullptr) const;

	String absolutePath() const;


	/**
	 * @brief Set the module's main router
	 * @param router The main router
	 */
	void setRouter(AbstractRouter* router);

	/**
	 * @brief Get a module by ID
	 * @param id The module
	 * @return The module with ID @p id
	 * @note Raises a NoSuchModule exception if there is no such module
	 */
	static Module* byId(const String& id);

public:
	/**
	 * @brief Loads the module with the specified identifier
	 * @param id The module identifier
	 * @return The module instance
	 */
	static Module* load(const String& id);

protected:
	/**
	 * @brief Constructs the module instance
	 */
	Module();

private:
	/**
	 * @brief The module identifier
	 */
	String _id;

	/**
	 * @brief The associated plugin
	 */
	Plugin* _plugin;

	/**
	 * @brief The main router
	 */
	AbstractRouter* _router;

	/**
	 * @brief The module's controllers
	 */
	List<Controller*> _controllers;

	/**
	 * @brief The module's models
	 */
	List<Model*> _models;

	/**
	 * @brief The module's repositories
	 */
	List<Repository*> _repositories;

	/**
	 * @brief The module's views
	 */
	List<View*> _views;
};

#endif // !_WPP_SITES_MODULE_H_
