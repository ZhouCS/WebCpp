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
 * @file Libs/Dir.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-22
 */

#include "Libs/Dir.h"

#include "Exceptions/Files.h"

#include <dirent.h>

Dir::Dir(const Path& path)
{
	String strPath = path.absolutePath();
	if (!strPath.endsWith("/"))
		strPath += "/";
	_path = Path(strPath);
}

StringList Dir::entries() const
{
	DIR* dh = opendir(_path.absolutePath().toCString());
	if (dh == nullptr)
		throw Exceptions::FileOpenFail(_path);

	StringList list;
	while (dirent* entry = readdir(dh))
	{
		String name = entry->d_name;
		if (name == "." || name == "..")
			continue;
		list.append(name);
	}
	closedir(dh);

	return list;
}

StringList Dir::recursiveEntries(EntryOptions options) const
{
	StringList list;
	scanDir("", &list, options);
	return list;
}

void Dir::scanDir(const String& prefix,
                  StringList* list,
                  EntryOptions options) const
{
	DIR* dh = opendir(_path.absolutePath() + prefix);
	if (dh == nullptr)
		throw Exceptions::FileOpenFail(_path);

	while (dirent* entry = readdir(dh))
	{
		String name = entry->d_name;
		if (name == "." || name == "..")
			continue;
		if (entry->d_type == DT_DIR)
		{
			if (options & Dirs)
				list->append(prefix + name + "/");
			scanDir(prefix + name + "/", list, options);
		}
		else if (options & Files)
			list->append(prefix + name);
	}
	closedir(dh);
}
