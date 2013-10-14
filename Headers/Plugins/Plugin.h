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
 * @file Plugins/Plugin.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-10
 */

#ifndef _PLUGINS_PLUGIN_H_
#define	_PLUGINS_PLUGIN_H_

#include "Types/Path.h"
#include "Exceptions/Plugins.h"

#include <dlfcn.h>

/**
 * \def PLUGIN_INSTANCE
 * @brief Insert function to get the plugin instance
 * @param className The name of the class to instantiate
 *
 * This macro defines, in the plugin, a function “pluginInstance()” which
 * returns a void*. The macro takes as parameter the name of a class which will
 * be instantiated in the function, and the instance returned to the host plugin
 * system.
 */
#define PLUGIN_INSTANCE(className) void* pluginInstance() \
{                                                         \
	static className* instance = new className;             \
	return reinterpret_cast<void*>(instance);               \
}

/**
 * @class Plugin Plugins/Plugin.h <Plugin>
 * @brief A plugin
 */
class Plugin
{
public:
	/**
	 * @brief Constructs a plugin on a shared object file
	 * @param soFilePath The associated shared object file path
	 */
	explicit Plugin(const Path& soFilePath);

	/**
	 * @brief Destructs the plugin
	 */
	virtual ~Plugin();

	/**
	 * @brief Get the class instance of the plugin
	 * @return The class instance
	 */
	template<typename T> T* instance() const
	{
		union {void* (*func)(); void* ptr;} getInstance;
		getInstance.ptr = dlsym(_handle, "_Z14pluginInstancev");
		char* err;
		if ((err = dlerror()) != nullptr)
			throw Exceptions::NoPluginInstance(this, err);
		return reinterpret_cast<T*>(getInstance.func());
	}

	/**
	 * @brief Get the associated shared object file path
	 * @return The associated shared object file path
	 */
	Path soFilePath() const;

private:
	/**
	 * @brief The associated shared object file path
	 */
	Path _soFilePath;

	/**
	 * @brief The dlopen()'s handle
	 */
	void* _handle;
};

#endif // !_PLUGINS_PLUGIN_H_
