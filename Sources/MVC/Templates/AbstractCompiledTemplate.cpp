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
 * @file MVC/Templates/AbstractCompiledTemplate.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-12
 */

#include "MVC/Templates/AbstractCompiledTemplate.h"
#include "MVC/Templates/AbstractTemplateEngine.h"

#include "Libs/IO/File.h"

AbstractCompiledTemplate::AbstractCompiledTemplate(const Path& filePath,
                                                   AbstractTemplateEngine* eng)
  : _engine(eng),
    _filePath(filePath),
    _compileTime(DateTime::now())
{}

void AbstractCompiledTemplate::addDependency(AbstractCompiledTemplate* tpl)
{
	_dependencies.append(tpl);
}

bool AbstractCompiledTemplate::update()
{
	bool toUpdate = false;
	for (AbstractCompiledTemplate* dep : _dependencies)
	{
		if (dep->update())
			toUpdate = true;
	}
	if (!toUpdate)
		toUpdate = File(_filePath).lastEditTime() > _compileTime;
	if (toUpdate)
	{
		_engine->compile(_filePath);
		delete this;
	}
	return toUpdate;
}

//----------------------------------------------------------------------------//

Path AbstractCompiledTemplate::filePath() const
{ return _filePath; }

DateTime AbstractCompiledTemplate::compileTime() const
{ return _compileTime; }

bool AbstractCompiledTemplate::dependsOn(AbstractCompiledTemplate* tpl) const
{ return _dependencies.contains(tpl); }
