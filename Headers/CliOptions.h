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
 * @file CliOptions.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#ifndef _CLIOPTIONS_H_
#define _CLIOPTIONS_H_

#include "Types/String.h"

class CliOptions
{
public:
	struct FlagEntry
	{
		String longName;
		char   shortName;
		int    value;
	};

	enum Flag
	{
		ForcePrompt = 0x01,
		NoPrompt    = 0x02,
		Verbose     = 0x04,
		Version     = 0x08,
		Help        = 0x10,
		Debug       = 0x20
	};

	CliOptions(const StringList& args);

	bool flag(Flag flg) const;

private:
	void longOption(const String& name, int* i);
	void shortOptions(const String& options, int* i);
	void argument(const String& value);

private:
	static FlagEntry _flagsList[];
	int       _flags;
};

#endif // !_CLIOPTIONS_H_
