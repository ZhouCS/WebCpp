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
 * @file Exceptions/Requests.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-31
 */

#ifndef _WPP_EXCEPTIONS_REQUESTS_H_
#define	_WPP_EXCEPTIONS_REQUESTS_H_

#include "Exceptions/Exception.h"

#include "Requests/Session.h"

namespace Exceptions {

class NotFound : public Exception
{
public:
	NotFound(const String& url)
	  : Exception("NotFound",
	              String("The requested URL “%1” was not found").format(url))
	{}
};

class Forbidden : public Exception
{
public:
	Forbidden(const String& url)
	  : Exception("Forbidden",
	              String("The requested URL “%1” is forbidden").format(url))
	{}
};

class HeadersAlreadySent : public Exception
{
public:
	HeadersAlreadySent()
	  : Exception("HeadersAlreadySent",
	              "Cannot modify headers, they were already sent")
	{}
};

class NoSuchSession : public Exception
{
public:
	NoSuchSession(uint32_t id)
	  : Exception("NoSuchSession",
	              String("There is no session with ID %1").format(id))
	{}
};

class InvalidSessionToken : public Exception
{
public:
	InvalidSessionToken(Session* session, const String& wrongToken)
	  : Exception("InvalidSessionToken",
	              String("Wrong token for session %1 (“%2” given)")
	                .format({session->id(), wrongToken}))
	{}
};

class SessionIpCheckFail : public Exception
{
public:
	SessionIpCheckFail(Session* session, const IpAddr& wrongIp)
	  : Exception("SessionIpCheckFail",
	              String("%3 tried to thief session %1 of %2")
	                .format((int)session->id(), session->ip(), wrongIp))
	{}
};

}

#endif // !_WPP_EXCEPTIONS_REQUESTS_H_
