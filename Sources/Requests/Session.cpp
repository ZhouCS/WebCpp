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
 * @file Requests/Session.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-31
 */

#include "Requests/Session.h"
#include "System.h"
#include "Exceptions/Requests.h"
#include "Libs/Random.h"
#include "Requests/Request.h"

Map<uint16_t, Session*> Session::_sessions;
uint16_t Session::_counter = 0;

Session::Session(Request* request)
{
	_request = request;
	_id = _counter++;
	_token = Random::generate(32, Random::Digits
	                          | Random::LowerCase
	                          | Random::UpperCase);
	_ip = _request->ip();
	_request->setCookie(System::setting("Sessions.IdCookieName"), String(_id),
	                    Request::SessionCookie);
	_request->setCookie(System::setting("Sessions.TokenCookieName"), _token,
	                    Request::SessionCookie);
	if (_sessions.hasKey(_id))
		delete _sessions[_id];
	_sessions[_id] = this;
}

bool Session::hasSession(uint16_t id)
{ return _sessions.hasKey(id); }

Session* Session::get(uint16_t id, const String& token, const IpAddr& ip)
{
	Session* sess = _sessions.get(id, nullptr);
	if (sess == nullptr)
		throw Exceptions::NoSuchSession(id);
	if (sess->_token != token)
		throw Exceptions::InvalidSessionToken(sess, token);
	if (System::setting("Sessions.IpCheck") && sess->_ip != ip)
		throw Exceptions::SessionIpCheckFail(sess, ip);
	return sess;
}

String Session::value(const String& name, const String& defaultValue) const
{ return _values.get(name, defaultValue); }

void Session::setValue(const String& name, const String& value)
{ _values.set(name, value); }

void Session::destroy()
{
	//_sessions.remove(_id);
	//delete this;
}

void Session::deleteSessions()
{
	for (Map<uint16_t, Session*>::Iterator i(_sessions); i.hasNext(); i++)
		delete i.value();
}

//----------------------------------------------------------------------------//

uint16_t Session::id() const
{ return _id; }

IpAddr Session::ip() const
{ return _ip; }
