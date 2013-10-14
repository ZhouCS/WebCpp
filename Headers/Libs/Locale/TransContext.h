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
 * @file Libs/Locale/TransContext.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-20
 */

#ifndef _LIBS_LOCALE_TRANSCONTEXT_H_
#define	_LIBS_LOCALE_TRANSCONTEXT_H_

#include "Types/String.h"
#include "Types/Map.h"
#include "Libs/Locale/TransManager.h"

class Module;
class Translation;

/**
 * @class TransContext Libs/Locale/TransContext.h <TransContext>
 * @brief A translation context
 */
class TransContext
{
	friend void TransManager::reloadFromFiles();
public:
	/**
	 * @brief Constructs a translation context
	 * @param module The parent module
	 */
	TransContext(Module* module);

	~TransContext();

	/**
	 * @brief Translates a string using this context
	 * @param lang The target language
	 * @param text The string to translate
	 * @return The translated string
	 */
	String translate(const String& lang, const String& text) const;

private:
	/**
	 * @brief The parent module
	 */
	Module* _module;

	/**
	 * @brief The context name
	 */
	String _contextName;

	/**
	 * @brief The context's translations
	 */
	Map<String, Map<String, Translation*>> _translations;
};

#endif // !_LIBS_LOCALE_TRANSCONTEXT_H_
