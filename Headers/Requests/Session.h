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
 * @file Requests/Session.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-31
 */

#ifndef _REQUESTS_SESSION_H_
#define	_REQUESTS_SESSION_H_

#include "Types/String.h"
#include "Types/Map.h"
#include "Types/IpAddr.h"

class Request;

/**
 * @class Session Requests/Session.h <Session>
 * @brief A client session
 */
class Session
{
public:
	/**
	 * @brief Constructs a new session
	 * @param request The associated request
	 */
	Session(Request* request);

	String value(const String& name, const String& defaultValue = String()) const;
	void   setValue(const String& name, const String& value);
	void   destroy();

	uint16_t id() const;
	IpAddr   ip() const;

public:
	static bool hasSession(uint16_t id);
	static Session* get(uint16_t id, const String& token, const IpAddr& ip);
	static void deleteSessions();

private:
	/**
	 * @brief The list of sessions
	 */
	static Map<uint16_t, Session*> _sessions;

	/**
	 * @brief Current IDs counter
	 */
	static uint16_t _counter;

	/**
	 * @brief The associated request
	 */
	Request* _request;

	/**
	 * @brief The session ID
	 */
	uint16_t _id;

	/**
	 * @brief The session token
	 */
	String _token;

	/**
	 * @brief The client's IP (for IP check security)
	 */
	IpAddr _ip;

	/**
	 * @brief The session values
	 */
	Map<String, String> _values;
};

#endif // !_REQUESTS_SESSION_H_
