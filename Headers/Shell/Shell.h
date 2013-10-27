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
 * @file Shell/Shell.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#ifndef _WPP_SHELL_SHELL_H_
#define _WPP_SHELL_SHELL_H_

#include "Shell/ShellCommand.h"
#include "Types/Map.h"

class StringList;
class String;

class Shell
{
public:
	static void registerCommand(ShellCommand* command);
	static void registerCommand(const String& name,
	                            const String& description,
	                            ShellCommandFunc func);
	static void deleteCommands();

	static void run();

	static List<ShellCommand*> commands();

private:
	static void registerBuiltins();
	static StringList parseInput(const String& input);
	static void parseQuotedString(String& arg, const char* str, int* i);
	static void skipWhitespaces(const char* input, int* i);

private:
	static Map<String, ShellCommand*> _commands;
	static bool _run;
};

#endif // !_WPP_SHELL_SHELL_H_
