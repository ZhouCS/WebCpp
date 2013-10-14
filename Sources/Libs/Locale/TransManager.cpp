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
 * @file Libs/Locale/TransManager.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-20
 */

#include "Libs/Locale/TransManager.h"

#include "System.h"
#include "Sites/Site.h"
#include "Sites/Module.h"

#include "Libs/Xml/XmlDoc.h"
#include "Libs/Dir.h"
#include "Libs/Locale/TransContext.h"
#include "Libs/Locale/Translation.h"

TransManager::~TransManager()
{
	for (Map<Module*, Map<String, TransContext*>>::Iterator i(_contexts);
	     i.hasNext(); i++)
	{
		for (Map<String, TransContext*>::Iterator j(i.value()); j.hasNext(); j++)
			delete j.value();
	}
}

TransManager* TransManager::get()
{
	static TransManager* manager = new TransManager;
	return manager;
}

void TransManager::reloadFromFiles()
{
	StringList dirs = {"WebCpp/Translations/", "Translations/"};
	List<Module*> modules = System::get()->site()->modules();

	Map<String, Module*> dirToModule;

	for (Module* module : modules)
	{
		dirs.append("Mods/" + module->id() + "/Translations/");
		dirToModule["Mods/" + module->id() + "/Translations/"] = module;
	}

	Map<Module*, Map<String, TransContext*>> contexts;

	/*for (String dir : dirs)
	{
		StringList langs = Dir(dir).entries();
		Module* module = dirToModule.get(dir, nullptr);

		for (String lang : langs)
		{
			StringList files = Dir(dir + lang).recursiveEntries();
			for (String file : files)
			{
				XmlDoc doc(dir + lang + "/" + file);

				String contextName = doc.attribute("context");

				TransContext* context = contexts[module].get(contextName, nullptr);
				if (context == nullptr)
				{
					context = new TransContext(module);
					contexts[module][contextName] = context;
					_contexts[module][contextName] = context;
				}

				for (XmlNode node : doc)
				{
					Translation* tr = new Translation(context);
					tr->_source = node.child("source").text();
					tr->_destination = node.child("destination").text();
					context->_translations[lang][tr->_source] = tr;
				}
			}
		}
	}*/
}

String TransManager::translate(Module* module, const String& context,
                               const String& lang, const String& text) const
{
	if (!_contexts.hasKey(module) || !_contexts[module].hasKey(context))
		return text;
	return _contexts[module][context]->translate(lang, text);
}
