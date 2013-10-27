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
 * @file Libs/IO/File.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-11
 */

#ifndef _WPP_LIBS_IO_FILE_H_
#define	_WPP_LIBS_IO_FILE_H_

#include <fstream>
#include <sys/stat.h>

#include "Libs/IO/IODevice.h"
#include "Types/Path.h"

class DateTime;

/**
 * @class File Libs/IO/File.h <File>
 * @brief A file
 */
class File : public IODevice, private std::fstream
{
public:
	File(const Path& path);

	/**
	 * @brief Implements how to open the device
	 * @brief mode The open mode
	 */
	virtual void open(int mode);

	/**
	 * @brief Implements how to write datas to the device
	 */
	virtual void write(const ByteArray& datas);

	/**
	 * @brief Implements how to close the device
	 */
	virtual void close();

	/**
	 * @brief Get all the content of a file
	 * @param path The file path
	 * @return All the content of the file to @p path
	 */
	static ByteArray getContent(const Path& path);


	mode_t mode() const;

	uid_t ownerUid() const;

	gid_t ownerGid() const;

	uint64_t size() const;

	DateTime lastAccessTime() const;

	DateTime lastEditTime() const;

private:
	/**
	 * @brief The file path
	 */
	Path _path;

	/**
	 * @brief File informations
	 */
	struct stat _stat;
};

#endif // !_WPP_LIBS_IO_FILE_H_
