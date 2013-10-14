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
 * @file Shell/CmdCore.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#include "Shell/ShellCommand.h"
#include "Shell/Shell.h"

#include "System.h"

#include <iomanip>

namespace ShellCmd {

void version(const StringList&)
{
	std::cout << System::get()->version() << std::endl;
}

void help(const StringList&)
{
	List<ShellCommand*> commands = Shell::commands();
	int maxLen = 0;

	for (ShellCommand* cmd : commands)
	{
		if (cmd->name().length() > maxLen)
			maxLen = cmd->name().length();
	}
	for (ShellCommand* cmd : commands)
	{
		std::cout << std::setw(maxLen) << cmd->name()
		          << " - " << cmd->description() << std::endl;
	}
}

}
