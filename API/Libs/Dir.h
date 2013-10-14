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
 * @file Libs/Dir.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-22
 */

#ifndef _LIBS_DIR_H_
#define	_LIBS_DIR_H_

#include "Types/Path.h"

/**
 * @class Dir Libs/Dir.h <Dir>
 * @brief A directory
 */
class Dir
{
public:
	enum EntryOptions
	{
		Files        = 0x1,
		Dirs         = 0x2,
		DirsAndFiles = 0x3
	};

	/**
	 * @brief Constructs a directory
	 * @param path The directory's path
	 */
	Dir(const Path& path);

	/**
	 * @brief Get the list of the directory's entries
	 */
	StringList entries() const;

	/**
	 * @brief Get the list of the directory's entries recursively
	 */
	StringList recursiveEntries(EntryOptions options = Files) const;

private:
	void scanDir(const String& prefix,
	             StringList* list,
	             EntryOptions options) const;

private:
	/**
	 * @brief The directory's path
	 */
	Path _path;
};

#endif // !_LIBS_DIR_H_
