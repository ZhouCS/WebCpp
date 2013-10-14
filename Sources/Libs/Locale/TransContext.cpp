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
 * @file Libs/Locale/TransContext.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-20
 */

#include "Libs/Locale/TransContext.h"
#include "Libs/Locale/Translation.h"

TransContext::TransContext(Module* module)
{
	_module = module;
}

TransContext::~TransContext()
{
	for (Map<String, Map<String, Translation*>>::Iterator i(_translations);
	     i.hasNext(); i++)
	{
		for (Map<String, Translation*>::Iterator j(i.value()); j.hasNext(); j++)
			delete j.value();
	}
}

String TransContext::translate(const String& lang, const String& text) const
{
	if (!_translations.hasKey(lang) || !_translations[lang].hasKey(text))
		return text;
	return _translations[lang][text]->translate();
}
