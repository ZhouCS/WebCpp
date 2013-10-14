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
 * @file Libs/IO/File.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-11
 */

#include "Libs/IO/File.h"

#include "Types/ByteArray.h"
#include "Types/DateTime.h"

#include <ctime>

File::File(const Path& path)
{
	_path = path;

	stat(_path.absolutePath(), &_stat);
}

void File::open(int mode)
{
	std::ios_base::openmode stdMode = static_cast<std::ios_base::openmode>(0);

	if (mode & ReadOnly)
		stdMode |= std::fstream::in;
	if (mode & WriteOnly)
		stdMode |= std::fstream::out;
	if (mode & Append)
		stdMode |= std::fstream::app;
	if (mode & Truncate)
		stdMode |= std::fstream::trunc;
	if (!(mode & Text))
		stdMode |= std::fstream::binary;

	std::fstream::open(_path.toString().toCString(), stdMode);
}

void File::write(const ByteArray& datas)
{
	reinterpret_cast<std::ostream*>(this)->write(datas.data(), datas.size());
}

void File::close()
{
	std::fstream::close();
}

ByteArray File::getContent(const Path& path)
{
	File file(path);
	file.open(ReadOnly);

	ByteArray r;

	while (!file.std::ios::eof())
	{
		char* buffer = new char[1024];
		file.std::fstream::read(buffer, 1024);
		r.append(buffer, file.std::fstream::gcount());
		delete[] buffer;
	}

	return r;
}

//----------------------------------------------------------------------------//

mode_t File::mode() const
{ return _stat.st_mode; }

uid_t File::ownerUid() const
{ return _stat.st_uid; }

gid_t File::ownerGid() const
{ return _stat.st_gid; }

uint64_t File::size() const
{ return _stat.st_size; }

DateTime File::lastAccessTime() const
{
	tm* tm = gmtime(&_stat.st_atime);
	return DateTime(1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour,
	                tm->tm_min, tm->tm_sec);
}

DateTime File::lastEditTime() const
{
	tm* tm = gmtime(&_stat.st_mtime);
	return DateTime(1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour,
	                tm->tm_min, tm->tm_sec);
}
