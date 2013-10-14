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
 * @file Libs/Regex.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-05
 */

#include "Libs/Regex.h"

#include "Exceptions/Regex.h"

#include <iostream>

Regex::Regex()
{ }

Regex::Regex(const String& pattern, int options)
{
	_pattern = pattern;
	_options = options;

	compile();
}

Regex::~Regex()
{
	pcre_free(_regex);
}

void Regex::compile()
{
	const char* errMsg;
	int errOffset;

	_regex = pcre_compile(_pattern, _options, &errMsg, &errOffset, nullptr);

	if (_regex == nullptr)
		throw Exceptions::RegexCompilation(*this, errMsg, errOffset);
}

bool Regex::exec(const String& str)
{
	int count = capturesCount();
	int* matches = new int[(count + 1) * 3];
	int r = pcre_exec(_regex, nullptr, str, str.size(), 0, 0, matches,
	                  (count + 1) * 3);
	if (r == -1)
	{
		delete[] matches;
		return false;
	}

	_capturedTexts.clear();
	_capturedIndexes.clear();
	for (int i = 1; i <= count; i++)
	{
		_capturedIndexes.append(
		      Pair<int, int>(matches[i * 2], matches[i * 2 + 1] - matches[i * 2]));
		_capturedTexts.append(
		      str.substr(matches[i * 2], matches[i * 2 + 1] - matches[i * 2]));
	}
	delete[] matches;
	return true;
}

//----------------------------------------------------------------------------//

String Regex::pattern() const
{ return _pattern; }

int Regex::capturesCount() const
{
	int n;
	pcre_fullinfo(_regex, nullptr, PCRE_INFO_CAPTURECOUNT, &n);
	return n;
}

StringList Regex::capturedTexts() const
{ return _capturedTexts; }

List<Pair<int, int> > Regex::capturedIndexes() const
{ return _capturedIndexes; }
