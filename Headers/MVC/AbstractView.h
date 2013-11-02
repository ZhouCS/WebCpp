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
 * @file MVC/AbstractView.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-15
 */

#ifndef _WPP_MVC_ABSTRACTVIEW_H_
#define _WPP_MVC_ABSTRACTVIEW_H_

#include "Types/Map.h"
#include "Types/String.h"
#include "Types/Variant.h"

class Request;

/**
 * @class AbstractView MVC/AbstractView.h <View>
 * @brief A basic view
 */
class AbstractView
{
public:
	/**
	 * @brief Constructs a basic view
	 */
	AbstractView();

	virtual ~AbstractView();

	/**
	 * @brief Implements how to render the view
	 */
	virtual void render() = 0;

	/**
	 * @brief Clears the view variables
	 */
	virtual void clear();


	/**
	 * @brief Get the associated request
	 */
	Request* request() const;

	/**
	 * @brief Set the request associated to the view
	 * @param request The associated request
	 */
	void setRequest(Request* request);

	/**
	 * @brief Determines whether the view has the @p key variable
	 * @param key The variable name
	 * @return true if the view has a @p key variable, otherwise false
	 */
	bool hasVar(const String& key) const;

	/**
	 * @brief Get a view variable
	 * @param key The variable name
	 * @return The value of variable @p name
	 */
	Variant get(const String& key) const;

	/**
	 * @brief Set a view variable value
	 * @param key The variable name
	 * @param var The variable value
	 */
	void set(const String& key, const Variant& var);

private:
	/**
	 * @brief The view variables
	 */
	Map<String, Variant> _vars;

	/**
	 * @brief The request that renders the view
	 */
	Request* _request;
};

#include "MVC/Templates/Template.h"
#include "DB/AbstractDbResult.h"

class ViewVarSetter
{
public:
	ViewVarSetter(AbstractView* view, const String& key)
	  : _key(key),
	    _view(view)
	{ }

	void operator=(const Variant& value)
	{ _view->set(_key, value); }

	void operator=(const List<Variant>& list)
	{ _view->set(_key, list); }

	void operator=(AbstractDbResult* dbResult)
	{
		List<Variant> rows;
		AbstractDbRow* row;
		while ((row = dbResult->fetch()) != nullptr)
			rows.append(row->renderableValues());
		_view->set(_key, rows);
		delete dbResult;
	}

private:
	String        _key;
	AbstractView* _view;
};

class View
{
public:
	View(AbstractView* view)
	  : _view(view)
	{ }

	~View()
	{
		_view->clear();
		delete _view;
	}

	ViewVarSetter operator[](const String& var)
	{ return ViewVarSetter(_view, var); }


	AbstractView* operator->() const
	{ return _view; }

	AbstractView* operator*() const
	{ return _view; }

	operator AbstractView*() const
	{ return _view; }

private:
	AbstractView* _view;
};

#endif // !_WPP_MVC_ABSTRACTVIEW_H_
