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
 * @file Types/Path.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-11
 */

#include "Types/Path.h"

#include <stdlib.h>

Path::Path()
{

}

Path::Path(const char* path, const String& relativeTo)
  : Path(String(path), relativeTo)
{}

Path::Path(const String& path, const String& relativeTo)
{
	if (path.startsWith("/"))
		_absolutePath = path;
	else
		_absolutePath = relativeTo + "/" + path;
	solvePath();
}

void Path::solvePath()
{
	if (!_absolutePath.endsWith("/"))
		_absolutePath += "/";
	_absolutePath = _absolutePath.replace("/./", "/");
	int pos = 0;
	while ((pos = _absolutePath.indexOf("//")) > -1)
		_absolutePath = _absolutePath.replace(pos, pos + 1, "/");
	pos = 0;
	while ((pos = _absolutePath.indexOf("/../", pos)) > -1)
	{
		if (pos == 0)
			_absolutePath = _absolutePath.removeLeft(3);
		else
			_absolutePath = _absolutePath.replace(_absolutePath.reversedIndexOf("/",
			                                      pos - 1) + 1, pos + 3, "");
	}
	if (_absolutePath != "/") // /foo/bar/../hello/world/
		_absolutePath = _absolutePath.removeRight(1);
}

//----------------------------------------------------------------------------//

String Path::absolutePath() const
{ return _absolutePath; }

String Path::relativePath() const
{ return _absolutePath.removeLeft(System::get()->absolutePath().length() + 1); }

String Path::toString() const
{ return _absolutePath; }

Path::operator String() const
{ return toString(); }

Path::operator const char*() const
{ return toString().toCString(); }
