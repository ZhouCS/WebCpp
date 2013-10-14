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
 * @file Plugins/Plugin.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-11
 */

#include "Plugins/Plugin.h"
#include "System.h"

Plugin::Plugin(const Path& soFilePath)
{
	_soFilePath = soFilePath;

	_handle = dlopen(_soFilePath.absolutePath(), RTLD_NOW | RTLD_GLOBAL);
	if (_handle == nullptr)
		throw Exceptions::PluginLoad(this, dlerror());
	System::get()->addLoadedPlugin(this);
}

Plugin::~Plugin()
{
	if (_handle != nullptr)
		dlclose(_handle);
}

//----------------------------------------------------------------------------//

Path Plugin::soFilePath() const
{ return _soFilePath; }
