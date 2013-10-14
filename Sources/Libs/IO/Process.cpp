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
 * @file Libs/IO/Process.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-04-25
 */

#include "Libs/IO/Process.h"
#include "Types/String.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

Process::Process(const String& command, const StringList& args)
{
	_command = command;
	_args = args;
	_exitStatus = -1;
}

void Process::open(int)
{ }

void Process::start()
{
	int fd0[2], fd1[2];
	pipe(fd0);
	pipe(fd1);

	pid_t pid = fork();
	if (pid == 0)
	{
		char** args = new char*[_args.count() + 2];
		args[0] = const_cast<char*>(_command.toCString());
		for (int i = 0, c = _args.count(); i < c; i++)
			args[i + 1] = const_cast<char*>(_args[i].toCString());
		args[_args.count() + 1] = nullptr;

		::close(fd0[1]);
		::close(fd1[0]);
		dup2(fd0[0], 0);
		dup2(fd1[1], 1);
		execv(_command.toCString(), args);
		exit(1);
	}

	::close(fd0[0]);
	::close(fd1[1]);
	_stdinFd = fd0[1];
	_stdoutFd = fd1[0];
	_pid = pid;
}

void Process::close()
{ }

void Process::write(const ByteArray&)
{

}

int Process::waitForFinished()
{
	int status;
	waitpid(_pid, &status, 0);
	_exitStatus = status;
	return status;
}

ByteArray Process::readAll()
{
	ssize_t sizeRead;
	char   buffer[1024];
	ByteArray ret;

	while ((sizeRead = ::read(_stdoutFd, buffer, sizeof buffer)) > 0)
		ret.append(buffer, sizeRead);
	return ret;
}

ByteArray Process::exec(const String& command, const StringList& args)
{
	Process proc(command, args);
	proc.start();
	proc.waitForFinished();
	return proc.readAll();
}

//----------------------------------------------------------------------------//

pid_t Process::pid() const
{ return _pid; }
