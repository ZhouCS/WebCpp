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
 * @file Shell/Shell.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#include "Shell/Shell.h"

#include "Types/String.h"

#include <iostream>

Map<String, ShellCommand*> Shell::_commands;
bool Shell::_run;

void Shell::registerCommand(ShellCommand* command)
{
	_commands[command->name()] = command;
}

void Shell::registerCommand(const String& name, const String& description,
                            ShellCommandFunc func)
{
	registerCommand(new ShellCommand(name, description, func));
}

void Shell::registerBuiltins()
{
	registerCommand("exit",    "Exits WebCpp",          nullptr);
	registerCommand("version", "Prints WebCpp version", ShellCmd::version);
	registerCommand("help",    "Prints commands list",  ShellCmd::help);
}

void Shell::deleteCommands()
{
	for (Map<String, ShellCommand*>::Iterator i(_commands); i.hasNext(); i++)
		delete i.value();
}

void Shell::run()
{
	registerBuiltins();
	_run = true;
	while (_run)
	{
		std::cout << "> ";

		String input;
		getline(std::cin, input.toStdString());

		StringList args = parseInput(input);
		if (args.count() > 0)
		{
			ShellCommand* cmd = _commands.get(args[0], nullptr);
			if (cmd == nullptr)
				std::cerr << args[0] << ": command not found" << std::endl;
			else if (cmd->name() == "exit")
				_run = false;
			else
			{
				args.remove(0);
				cmd->exec(args);
			}
		}
		if (std::cin.eof())
			_run = false;
	}
}

StringList Shell::parseInput(const String& input)
{
	StringList  args;
	const char* str = input.toCString();
	int         i = 0;

	while (str[i] != '\0')
	{
		String arg;

		skipWhitespaces(str, &i);
		for (; str[i] != '\0' && str[i] != ' ' && str[i] != '\t'; i++)
		{
			if (str[i] == '"')
				parseQuotedString(arg, str, &i);
			else
				arg += str[i];
		}
		args.append(arg);
		if (str[i] != '\0')
			skipWhitespaces(str, &i);
	}
	if (args.count() == 1 && args[0].length() == 0)
		return StringList();
	return args;
}

void Shell::parseQuotedString(String& arg, const char* str, int* i)
{
	(*i)++;
	for (; str[*i] != '\0'; (*i)++)
	{
		if (str[*i] == '\\')
		{
			(*i)++;
			if (str[*i] == 'n')
				arg += '\n';
			else if (str[*i] == 't')
				arg += '\t';
			else if (str[*i] == '"')
				arg += '"';
		}
		else if (str[*i] == '"')
			break;
		else
			arg += str[*i];
	}
}

void Shell::skipWhitespaces(const char* input, int* i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
}

//----------------------------------------------------------------------------//

List<ShellCommand*> Shell::commands()
{ return _commands.values(); }
