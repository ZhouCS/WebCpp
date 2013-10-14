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
 * @file Libs/Locale/TransManager.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-20
 */

#ifndef _LIBS_LOCALE_TRANSMANAGER_H_
#define	_LIBS_LOCALE_TRANSMANAGER_H_

#include "Types/Map.h"

class TransContext;
class Path;
class Module;

/**
 * @class TransManager Libs/Locale/TransManager.h <TransManager>
 * @brief The translations manager
 */
class TransManager
{
public:
	~TransManager();

	static TransManager* get();

	void reloadFromFiles();

	String translate(Module* module,
	                 const String& context,
	                 const String& lang,
	                 const String& text) const;

private:
	void scanDir(const Path& path, const String& lang);

private:
	Map<Module*, Map<String, TransContext*>> _contexts;
};

#endif // !_LIBS_LOCALE_TRANSMANAGER_H_
