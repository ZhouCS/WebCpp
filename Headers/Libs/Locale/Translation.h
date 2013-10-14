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
 * @file Libs/Locale/Translation.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-20
 */

#ifndef _LIBS_LOCALE_TRANSLATION_H_
#define	_LIBS_LOCALE_TRANSLATION_H_

#include "Libs/Locale/TransManager.h"

class TransContext;

/**
 * @class Translation Libs/Locale/Translation.h <Translation>
 * @brief A translation text
 */
class Translation
{
	friend void TransManager::reloadFromFiles();
public:
	/**
	 * @brief Constructs a translation
	 * @param context The parent context
	 */
	Translation(TransContext* context);

	String translate() const;

private:
	/**
	 * @brief The parent context
	 */
	TransContext* _context;

	String _source;

	String _destination;
};

#endif // !_LIBS_LOCALE_TRANSLATION_H_
