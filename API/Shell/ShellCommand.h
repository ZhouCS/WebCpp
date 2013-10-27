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
 * @file Shell/ShellCommand.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#ifndef _WPP_SHELL_SHELLCOMMAND_H_
#define _WPP_SHELL_SHELLCOMMAND_H_

#include "Types/String.h"

class StringList;

typedef void (*ShellCommandFunc)(const StringList&);

class ShellCommand
{
public:
	ShellCommand(const String& name, const String& description,
	             ShellCommandFunc func);

	void exec(const StringList& args);

	String name() const;
	String description() const;

private:
	String           _name;
	String           _description;
	ShellCommandFunc _func;
};

namespace ShellCmd {

void version(const StringList& args);
void help(const StringList& args);

}

#endif // !_WPP_SHELL_SHELLCOMMAND_H_
