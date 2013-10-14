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
 * @file CliOptions.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#include "CliOptions.h"

#include "Types/StringList.h"

CliOptions::FlagEntry CliOptions::_flagsList[] = {
	{"prompt",    'p',  CliOptions::ForcePrompt},
	{"no-prompt", '\0', CliOptions::NoPrompt},
	{"verbose",   'v',  CliOptions::Verbose},
	{"version",   '\0', CliOptions::Version},
	{"help",      'h',  CliOptions::Help},
  {"debug",     'g',  CliOptions::Debug}
};

CliOptions::CliOptions(const StringList& args)
{
	_flags = 0;

	for (int i = 1, c = args.count(); i < c; i++)
	{
		if (args[i].startsWith("--") && args[i].length() > 2)
			longOption(args[i].removeLeft(2), &i);
		else if (args[i].startsWith("-") && args[i].length() > 1)
			shortOptions(args[i].removeLeft(1), &i);
		else
			argument(args[i]);
	}
}

void CliOptions::longOption(const String& name, int*)
{
	int flagsCount = sizeof _flagsList / sizeof _flagsList[0];

	for (int i = 0; i < flagsCount; i++)
	{
		if (_flagsList[i].longName == name)
		{
			_flags |= _flagsList[i].value;
			return;
		}
	}
}

void CliOptions::shortOptions(const String& options, int*)
{
	int flagsCount = sizeof _flagsList / sizeof _flagsList[0];

	for (char ch : options)
	{
		for (int i = 0; i < flagsCount; i++)
		{
			if (_flagsList[i].shortName == ch)
			{
				_flags |= _flagsList[i].value;
				break;
			}
		}
	}
}

void CliOptions::argument(const String&)
{

}

//----------------------------------------------------------------------------//

bool CliOptions::flag(Flag flg) const
{ return _flags & flg; }
