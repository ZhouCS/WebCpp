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
 * @file MVC/Templates/TemplatesManager.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-01
 */

#include "MVC/Templates/TemplatesManager.h"
#include "MVC/Templates/Template.h"
#include "MVC/Templates/AbstractCompiledTemplate.h"
#include "MVC/Templates/AbstractTemplateEngine.h"

#include "Libs/Dir.h"
#include "Libs/IO/File.h"
#include "Plugins/Plugin.h"
#include "System.h"

TemplatesManager::TemplatesManager()
{
	reloadEngines();
	_defaultEngine = _engines[System::settings()->defaultTemplateEngine];
}

TemplatesManager::~TemplatesManager()
{
	for (Map<String, AbstractCompiledTemplate*>::Iterator i(_templates);
	     i.hasNext(); i++)
		delete i.value();
	for (Map<String, AbstractTemplateEngine*>::Iterator i(_engines);
	     i.hasNext(); i++)
		delete i.value();
}

TemplatesManager* TemplatesManager::get()
{
	static TemplatesManager* manager = new TemplatesManager;
	return manager;
}

void TemplatesManager::reloadEngines()
{
	_engines.clear();

	StringList entries = Dir("WebCpp/Plugins/TemplateEngines/").entries();
	for (const String& entry : entries)
	{
		Plugin* plugin = new Plugin("WebCpp/Plugins/TemplateEngines/"+entry);
		AbstractTemplateEngine* engine = plugin->instance<AbstractTemplateEngine>();
		_engines[engine->id()] = engine;
	}
}

//----------------------------------------------------------------------------//

AbstractTemplateEngine* TemplatesManager::defaultEngine() const
{ return _defaultEngine; }

AbstractCompiledTemplate*
TemplatesManager::compiledTemplate(const Path& filePath,
                                   AbstractTemplateEngine* tplEngine)
{
	AbstractCompiledTemplate* compiledTpl;

	if (TemplatesManager::get()->_templates.hasKey(filePath.absolutePath()))
	{
		compiledTpl = TemplatesManager::get()->_templates[filePath.absolutePath()];
#ifdef DEBUG
		if (File(filePath).lastEditTime() > compiledTpl->compileTime())
			delete compiledTpl;
		else
			return compiledTpl;
#endif
#ifndef DEBUG
		return compiledTpl;
#endif
	}

	if (tplEngine == nullptr)
		tplEngine = TemplatesManager::get()->_defaultEngine;

	compiledTpl = tplEngine->compile(filePath);
	TemplatesManager::get()->_templates.set(filePath.absolutePath(), compiledTpl);

	return compiledTpl;
}

AbstractTemplateEngine* TemplatesManager::engineByName(const String& name)
{
	return TemplatesManager::get()->_engines.get(name, nullptr);
}

void TemplatesManager::setTemplate(const String& filePath,
                                   AbstractCompiledTemplate* compiledTpl)
{
	TemplatesManager::get()->_templates[filePath] = compiledTpl;
}

void TemplatesManager::setDefaultEngine(AbstractTemplateEngine* defaultEngine)
{ _defaultEngine = defaultEngine; }
