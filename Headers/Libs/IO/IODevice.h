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
 * @file Libs/IO/IODevice.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-11
 */

#ifndef _LIBS_IO_IODEVICE_H_
#define	_LIBS_IO_IODEVICE_H_

#include <iostream>

#include "Types/ByteArray.h"

/**
 * @class IODevice Libs/IO/IODevice.h <IODevice>
 * @brief A basic input / output device
 */
class IODevice : protected std::iostream
{
public:
	/**
	 * @brief The opening modes
	 */
	enum OpenMode
	{
		NotOpen   = 0x0,
		ReadOnly  = 0x1,
		WriteOnly = 0x2,
		ReadWrite = 0x3,
		Append    = 0x4,
		Truncate  = 0x8,
		Text      = 0x10
	};

	/**
	 * @brief Constructs an I/O device
	 */
	IODevice();

	/**
	 * @brief Implements how to open the device
	 * @brief mode The open mode
	 */
	virtual void open(int mode) = 0;

	/**
	 * @brief Implements how to write datas to the device
	 */
	virtual void write(const ByteArray& datas) = 0;

	/**
	 * @brief Implements how to close the device
	 */
	virtual void close() = 0;

protected:
	/**
	 * @brief The open mode
	 */
	OpenMode _openMode;
};

#endif // !_LIBS_IO_IODEVICE_H_
