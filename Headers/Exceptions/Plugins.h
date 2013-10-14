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
 * @file Exceptions/Plugins.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-11
 */

#ifndef _EXCEPTIONS_PLUGINS_H_
#define	_EXCEPTIONS_PLUGINS_H_

#include "Exceptions/Exception.h"

class Plugin;

namespace Exceptions {

/**
 * @class PluginLoad Exceptions/Plugins.h <Exceptions/Plugins>
 * @brief A plugin load exception
 */
class PluginLoad : public Exception
{
public:
	PluginLoad(const Plugin* plugin, const String& errorMessage);
	const Plugin* plugin;
	String errorMessage;
};

/**
 * @class NoPluginInstance Exceptions/Plugins.h <Exceptions/Plugins>
 * @brief Exception thrown when no plugin instance was found
 */
class NoPluginInstance : public Exception
{
public:
	/**
	 * @brief Constructs an exception thrown when no plugin instance was found
	 * @param plugin The plugin which we failed to get instance from
	 * @param errorMessage The error message
	 */
	NoPluginInstance(const Plugin* plugin, const String& errorMessage);

	virtual ~NoPluginInstance() throw() {}

	/**
	 * @brief The plugin which we failed to get instance from
	 */
	const Plugin* plugin;

	/**
	 * @brief The error message
	 */
	String errorMessage;
};

}

#endif // !_EXCEPTIONS_PLUGINS_H_
