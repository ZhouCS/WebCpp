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
 * @file Exceptions/Regex.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-08
 */

#ifndef _WPP_EXCEPTIONS_REGEX_H_
#define	_WPP_EXCEPTIONS_REGEX_H_

#include "Exceptions/Exception.h"

#include "Libs/Regex.h"

namespace Exceptions {

/**
 * @class RegexCompilation Exceptions/Regex.h <Exceptions/Regex>
 */
class RegexCompilation : public Exception
{
public:
	RegexCompilation(const Regex& regex,
	                 const String& compileError,
	                 int column) throw()
	  : Exception("RegexCompilation",
	              String("Failed to compile regex “%1”: %2 (col %3)")
	                .format({regex.pattern(), compileError, column})),
	    _regex(&regex),
	    _compileError(compileError),
	    _column(column)
	{}

private:
	const Regex* _regex;
	String       _compileError;
	int          _column;
};

}

#endif // !_WPP_EXCEPTIONS_REGEX_H_
