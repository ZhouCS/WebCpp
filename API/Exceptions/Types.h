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
 * @file Exceptions/Types.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-31
 */

#ifndef _WPP_EXCEPTIONS_TYPES_H_
#define	_WPP_EXCEPTIONS_TYPES_H_

#include "Exceptions/Exception.h"

namespace Exceptions {

class BadIpAddr : public Exception
{
public:
	BadIpAddr(const String& ip)
	  : Exception("BadIpAddr",
	              String("Bad IPv4 address “%1”").format(ip))
	{}
};

class CannotConvertToInt : public Exception
{
public:
	CannotConvertToInt(const String& src)
	  : Exception("CannotConvertToInt",
	              String("Cannot convert “%1” to integer").format(src))
	{}
};

class CannotConvertToFloat : public Exception
{
public:
	CannotConvertToFloat(const String& src)
	  : Exception("CannotConvertToFloat",
	              String("Cannot convert “%1” to float").format(src))
	{}
};

}

#endif // !_WPP_EXCEPTIONS_TYPES_H_
