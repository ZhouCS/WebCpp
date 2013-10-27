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
 * @file MVC/Controller.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-14
 */

#ifndef _WPP_MVC_CONTROLLER_H_
#define _WPP_MVC_CONTROLLER_H_

#include "Types/String.h"
#include "Types/Map.h"

#include "Requests/Request.h"
#include "Requests/RequestStream.h"
#include "Requests/UserAgent.h"

#include "Sites/Module.h"

#include "Libs/Locale/Locale.h"

class Module;
class Request;
class AbstractDbConnection;
class AbstractDbResult;
class Template;
class AbstractTemplateEngine;

/**
 * @brief Easily register an action
 * @param memberName The action member name (e.g. MyController::myAction)
 */
#define registerAction(memberName) \
	registerActionMethod(#memberName, (void (Controller::*)())(&memberName))

#define CONTROLLER(name) virtual Controller* newInstance() const \
  { return new name; }

/**
 * @class Controller MVC/Controller.h <Controller>
 * @brief A controller
 */
class Controller
{
	friend void Module::registerController(Controller*);
public:
	class Forbidden{};
	class NotFound{};

	/**
	 * @brief Constructs a slave controller
	 */
	Controller();

	/**
	 * @brief Constructs the master controller
	 * @param id The controller identifier
	 */
	Controller(const String& id);

	/**
	 * @brief Destucts the controller
	 */
	virtual ~Controller();

	/**
	 * @brief Implements how to get a new instance of the controller
	 * @return The new controller instance
	 */
	virtual Controller* newInstance() const = 0;

	/**
	 * @brief Executes an action of the controller
	 * @param request The associated request
	 * @param action The action name
	 * @param args The arguments list
	 */
	void exec(Request* request,
	          const String& action,
	          const Map<String, String>& args);

	/**
	 * @brief Registers an action method
	 * @param id The action identifier (without "Action" suffix)
	 * @param func The member function to execute
	 */
	void registerActionMethod(const String& id, void (Controller::*func)());


	/**
	 * @brief Get the current request
	 */
	Request* request() const;

	/**
	 * @brief Get the request stream
	 */
	RequestStream& stream() const;

	/**
	 * @brief Get the default database connection
	 */
	AbstractDbConnection* db() const;

	/**
	 * @brief Executes an SQL query
	 * @param sql The SQL query
	 * @return The SQL result
	 */
	AbstractDbResult* query(const String& sql) const;

	/**
	 * @brief Get a template by name
	 * @param name The template name
	 * @param tplEngine The template engine
	 * @return The template @p name
	 */
	Template* tpl(const String& name,
	              AbstractTemplateEngine* tplEngine = nullptr) const;

	/**
	 * @brief Translate a text
	 * @param text The text to translate
	 * @return The translated text
	 */
	String tr(const String& text) const;

	/**
	 * @brief Generates an URL
	 * @param id The path ID
	 * @param args The arguments lists (e.g. {"id=23", "title=Moo"})
	 * @param lang The path lang
	 * @return The URL
	 */
	String path(const String& id,
	            const StringList& args,
	            const String& lang = String()) const;

	/**
	 * @brief Generates an URL
	 * @param id The path ID
	 * @param args The arguments map
	 * @param lang The path lang
	 * @return The URL
	 */
	String path(const String& id,
	            const Map<String, String>& args = Map<String, String>(),
	            const String& lang = String()) const;

	/**
	 * @brief Determines if the request is a POST one
	 * @return true if the request is a POST one, otherwise false
	 */
	bool isPost() const;

	/**
	 * @brief Get the client's user agent
	 */
	UserAgent userAgent() const;

	/**
	 * @brief Get the client's locale
	 */
	Locale* locale() const;

	/**
	 * @brief Get a environment variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the environment variable
	 *                     doesn't exist
	 * @return The variable value with the given name
	 */
	String env(const String& variable,
	           const String& defaultValue = String()) const;

	bool hasGet(const String& variable) const;

	/**
	 * @brief Get a GET variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the GET variable doesn't
	 *                     exist
	 * @return The variable value with the given name
	 */
	String get(const String& variable,
	           const String& defaultValue = String()) const;

	/**
	 * @brief Get a POST variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the POST variable doesn't
	 *                     exist
	 * @return The variable value with the given name
	 */
	String post(const String& variable,
	            const String& defaultValue = String()) const;

	/**
	 * @brief Get a cookie
	 * @param name The cookie name
	 * @param defaultValue A default value to return if the cookie doesn't exist
	 * @return The cookie value with the given name
	 */
	String cookie(const String& name,
	              const String& defaultValue = String()) const;

	/**
	 * @brief Get a session variable
	 * @param name The session variable name
	 * @param defaultValue A default value to return if the session variable
	 *                     doesn't exist
	 * @return The session variable value with the given name
	 */
	String session(const String& name,
	               const String& defaultValue = String()) const;

	/**
	 * @brief Set a session variable
	 * @param name The variable name
	 * @param value The variable value
	 */
	void setSession(const String& name, const String& value) const;

	/**
	 * @brief Get an argument variable
	 * @param variable The argument name
	 * @return The argument value with the given name
	 */
	String arg(const String& name, const String& defaultValue = String()) const;


	/**
	 * @brief Set an HTTP header
	 * @param name The HTTP header name (e.g. “Content-Language”)
	 * @param value The header value
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void setHeader(const String& name, const String& value);

	/**
	 * @brief Set the HTTP response code
	 * @param httpCode The HTTP response code
	 */
	void setStatus(int httpCode);

	/**
	 * @brief Set the content type of the document
	 * @param mimeType The document MIME type
	 * @param charset The document's charset
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void setContentType(const String& mimeType, const String& charset = String());

	/**
	 * @brief Explicitly send HTTP headers
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void sendHeaders();

	/**
	 * @brief Redirect the client to an other location
	 * @param location The new location to redirect to
	 * @param httpCode The HTTP response code
	 */
	void redirect(const String& location, int httpCode = 303);

	/**
	 * @brief Determines whether headers were sent
	 * @return true if headers were sent, otherwise false
	 */
	bool headersSent() const;

	/**
	 * @brief Get an HTTP header by name
	 * @param name The header name
	 */
	String header(const String& name) const;


	/**
	 * @brief Immediately stops the action execution and the request
	 */
	void exit() const;


	/**
	 * @brief Determines if this instance is the master controller
	 */
	bool isMaster() const;

	/**
	 * @brief Get the controller identifier
	 */
	String id() const;

	String fullId() const;

	//void setModule();

public:
	static Controller* byId(const String& id, Module* module = nullptr);

private:
	class Exit{};

private:
	/**
	 * @brief The controller identifier
	 */
	String _id;

	/**
	 * @brief The associated module
	 */
	Module* _module;

	/**
	 * @brief The list of actions
	 */
	Map<String, void (Controller::*)()> _actions;

	/**
	 * @brief The current request
	 */
	Request* _request;

	/**
	 * @brief The current arguments list
	 */
	Map<String, String> _args;
};

#endif  // !_WPP_MVC_CONTROLLER_H_
