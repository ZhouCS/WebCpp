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
 * @file MVC/Routers/AbstractRoute.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-04
 */

#include "MVC/Routers/AbstractRoute.h"
#include "Libs/Regex.h"
#include "Types/Map.h"
#include "MVC/Routers/Router.h"

AbstractRoute::AbstractRoute(const String& id, const String& pattern)
{
	_id = id;
	_patterns[""] = pattern;
}

AbstractRoute::AbstractRoute(const String& id,
                             const Map<String,String>& patterns)
{
	_id = id;
	_patterns = patterns;
}

AbstractRoute::Match AbstractRoute::match(const String& path)
{
	for (Map<String, String>::Iterator i(_patterns); i.hasNext(); i++)
	{
		String pattern = i.value().replace(".", "\\.");

		int pos = -1;
		while ((pos = pattern.indexOf("{$", pos + 1)) > -1)
		{
			int pos2 = pattern.indexOf("}", pos);
			pattern = pattern.replace(pos, pos2 + 1, ".+");
		}

		if (path.match(String("^") + pattern + "$"))
			return {this, true, i.value(), i.key()};
	}

	return {this, false, "", ""};
}

void AbstractRoute::trigger(const String& path,
                            const String& _pattern,
                            Request* request) const
{
	StringList keys;

	int pos = -1;
	while ((pos = _pattern.indexOf("{$", pos + 1)) >= 0)
		keys.append(_pattern.mid(pos + 2, _pattern.indexOf("}", pos)));

	String pattern = _pattern.replace(".", "\\.");
	pos = -1;
	while ((pos = pattern.indexOf("{$", pos + 1)) > -1)
	{
		int pos2 = pattern.indexOf("}", pos);
		pattern = pattern.replace(pos, pos2 + 1, "(.+)");
	}

	Regex valuesRegex(pattern);
	valuesRegex.exec(path);
	StringList values = valuesRegex.capturedTexts();

	Map<String, String> args;
	for (int i = 0; i < keys.count(); i++)
		args[keys[i]] = values[i];

	process(args, request);
}

String AbstractRoute::generatePath(const Map<String, String>& args,
                                   const String& lang) const
{
	String pattern = _patterns[lang];
	String r = pattern;

	int pos = -1;
	while ((pos = pattern.indexOf("{$", pos + 1)) >= 0)
	{
		String varName = pattern.mid(pos + 2, pattern.indexOf("}", pos));
		r = r.replace("{$" + varName + "}", args.get(varName, ""));
	}

	return r;
}

//----------------------------------------------------------------------------//

String AbstractRoute::id() const
{ return _id; }
