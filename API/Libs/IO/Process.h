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
 * @file Libs/IO/Process.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-04-25
 */

#ifndef _LIBS_IO_PROCESS_H_
#define	_LIBS_IO_PROCESS_H_

#include <unistd.h>

#include "Libs/IO/IODevice.h"
#include "Types/String.h"
#include "Types/StringList.h"

/**
 * @class Process Libs/IO/Process.h <Process>
 * @brief A processus handler
 */
class Process : public IODevice
{
public:
	explicit Process(const String& command,
	                 const StringList& args = StringList());

	void start();

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

	int waitForFinished();

	ByteArray readAll();

	pid_t pid() const;

public:
	static ByteArray exec(const String& command,
	                      const StringList& args = StringList());

private:
	String _command;

	StringList _args;

	pid_t _pid;

	int _stdinFd;
	int _stdoutFd;

	int _exitStatus;
};

#endif // !_LIBS_IO_PROCESS_H_
