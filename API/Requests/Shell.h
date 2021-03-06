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
 * @file Requests/Shell.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-18
 */

#ifndef _WPP_REQUESTS_SHELL_H_
#define _WPP_REQUESTS_SHELL_H_

class StringList;
class String;

class Shell
{
public:
	static void run();

private:
	static StringList parseInput(const String& input);
	static void parseQuotedString(String& arg, const char* str, int* i);
	static void skipWhitespaces(const char* input, int* i);

private:
	static bool _run;
};

#endif // !_WPP_REQUESTS_SHELL_H_
