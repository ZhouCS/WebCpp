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
 * @file Requests/Request.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-23
 */

#include "Requests/Request.h"
#include "Requests/RequestThread.h"
#include "Requests/RequestStream.h"
#include "Requests/RequestError.h"
#include "Requests/RequestProfile.h"

#include "System.h"
#include "MVC/Routers/Router.h"
#include "Sites/Site.h"

#include "Libs/Locale/Locale.h"
#include "Libs/Chrono.h"

#include "Types/DateTime.h"
#include "Requests/Session.h"
#include "MVC/Controller.h"

#include "Exceptions/Routers.h"
#include "Exceptions/Requests.h"
#include "Exceptions/Segfault.h"
#include "Exceptions/Types.h"

#include <fcgiapp.h>

Map<int, String> Request::_statusList;

Request::Request(FCGX_Request* fcgiRequest)
  : _fcgiRequest(fcgiRequest),
    _stream(this),
    _inputStream(this)
{
	_locale = nullptr;
	_profile = new RequestProfile;
	_headersSent = false;
	_session = nullptr;
	_userAgentParsed = false;

	static bool statusInitialized = false;
	if (!statusInitialized)
	{
		_statusList[200] = "OK";
		_statusList[201] = "Created";
		_statusList[202] = "Accepted";
		_statusList[203] = "Non-Authoritative Information";
		_statusList[204] = "No Content";
		_statusList[205] = "Reset Content";
		_statusList[206] = "Partial Content";

		_statusList[300] = "Multiple Choices";
		_statusList[301] = "Moved Permanently";
		_statusList[302] = "Found";
		_statusList[303] = "See Other";
		_statusList[304] = "Not Modified";
		_statusList[305] = "Use Proxy";
		_statusList[307] = "Temporary Redirect";
		_statusList[310] = "Too Many Redirect";

		_statusList[400] = "Bad Request";
		_statusList[401] = "Unauthorized";
		_statusList[402] = "Payment Required";
		_statusList[403] = "Forbidden";
		_statusList[404] = "Not Found";
		_statusList[405] = "Method Not Allowed";
		_statusList[406] = "Not Acceptable";
		_statusList[407] = "Proxy Authentication Required";
		_statusList[408] = "Request Time-out";
		_statusList[409] = "Conflict";
		_statusList[410] = "Gone";
		_statusList[411] = "Length Required";
		_statusList[412] = "Precondition Failed";
		_statusList[413] = "Request Entity Too Large";
		_statusList[414] = "Request-URI Too Long";
		_statusList[415] = "Unsupported Media Type";
		_statusList[416] = "Requested Range Unsatisfiable";
		_statusList[417] = "Expectation Failed";
		_statusList[426] = "Upgrade Required";

		_statusList[500] = "Internal Server Error";
		_statusList[501] = "Not Implemented";
		_statusList[502] = "Bad Gateway";
		_statusList[503] = "Service Unavailable";
		_statusList[504] = "Gateway Time-out";
		_statusList[505] = "HTTP Version Not Supported";

		statusInitialized = true;
	}
}

Request::~Request()
{

}

void Request::process()
{
	Chrono totalChrono(true);
	Chrono sysChrono(true);

	_isPost = false;

	for (int i = 0; _fcgiRequest->envp[i] != 0; i++)
	{
		String str = _fcgiRequest->envp[i];
		if (!str.contains("="))
			continue;
		_env[str.tokenLeft("=")] = str.tokenRight("=");
	}

	/*
	for (Map<String, String>::Iterator i(_env); i.hasNext(); i++)
		std::cout << i.key() << "=" << i.value() << std::endl;
	//*/

	_get = _env["QUERY_STRING"].secure().urlUnescape()
	       .secure().parseQueryString(); // Don't forget to double secure()
	_path = _env["DOCUMENT_URI"].secure();
	if (_env.get("REQUEST_METHOD", "GET") == "POST"
	    && _env.hasKey("CONTENT_LENGTH"))
	{
		_isPost = true;
		int length = _env["CONTENT_LENGTH"].toInt() + 1;

		char* str = new char[length];
		str[length - 1] = '\0';

		_inputStream.read(str, length);
		_post = String(str).secure().urlUnescape().secure().parseQueryString();
		delete[] str;
	}
	_ip = _env["REMOTE_ADDR"];

	if (_env.hasKey("HTTP_COOKIE"))
	{
		StringList cookies = _env["HTTP_COOKIE"].secure().split("; ");
		for (String& cookie : cookies)
		{
			String key, value;
			if (cookie.contains("="))
			{
				key = cookie.tokenLeft("=");
				value = cookie.tokenRight("=");
			}
			else
				key = cookie;

			_cookies[key] = value;
		}
	}
	if (System::settings()->behindProxy && _env.hasKey("HTTP_X_FORWARDED_FOR"))
	{
		try
		{ _ip = _env["HTTP_X_FORWARDED_FOR"]; }
		catch (const Exceptions::BadIpAddr&)
		{ }
	}

	if (System::setting("Sessions.Enabled"))
	{
		if (hasCookie(System::settings()->sessionIdCookieName)
		    && hasCookie(System::settings()->sessionTokenCookieName))
		{
			try
			{
				_session = Session::get(
				             cookie(System::settings()->sessionIdCookieName).toInt(),
				             cookie(System::settings()->sessionTokenCookieName),
				             _ip);
			}
			catch (const Exceptions::NoSuchSession &e)
			{
				System::log("Security", "<" + _ip.toString() + "> " + e.message());
				_session = new Session(this);
			}
			catch (const Exceptions::InvalidSessionToken &e)
			{
				System::log("Security", "<" + _ip.toString() + "> " + e.message(),
				            System::Warning);
				_session = new Session(this);
			}
			catch (const Exceptions::SessionIpCheckFail &e)
			{
				System::log("Security", "<" + _ip.toString() + "> " + e.message(),
				            System::Critical);
				_session = new Session(this);
			}
		}
		else
			_session = new Session(this);
	}

	setContentType(System::settings()->defaultContentType,
	               System::settings()->defaultCharset);

	if (_session != nullptr)
		setLocale(_session->value("_LOCALE", Locale::defaultLocale()->name()));
	else
		_locale = Locale::defaultLocale();

	_profile->addChronoTime(RequestProfile::System, sysChrono.elapsed());

	if (System::hasExceptionHandling())
	{
		try
		{
			try
			{ System::get()->site()->router()->process(_path, this); }
			catch (const Exceptions::NoRouteToPath& e)
			{ throw Exceptions::NotFound(uri()); }
		}
		catch (Exceptions::Segfault& e)
		{ RequestError::segfault(this, e); }
		catch (Exception& e)
		{ RequestError::exception(this, e); }
		catch(const std::exception& e)
		{ RequestError::stdException(this, e); }
	}
	else
		System::get()->site()->router()->process(_path, this);

	if (!_headersSent)
		sendHeaders();

	_profile->addChronoTime(RequestProfile::Total, totalChrono.elapsed());
}


void Request::setHeader(const String& name, const String& value, bool insert)
{
	if (_headersSent)
		throw Exceptions::HeadersAlreadySent();
	if (insert)
		_headers.insert(name, value);
	else
		_headers.setFirst(name, value);
}

void Request::setStatus(int httpCode)
{ setHeader("Status", String(httpCode) + " " + _statusList[httpCode]); }

void Request::setContentType(const String& mimeType, const String& charset)
{
	_mimeType = mimeType;
	_charset = charset;
	setHeader("Content-Type",
	          mimeType + "; charset=" + (charset.isNull() ? "utf-8" : charset));
}

void Request::sendHeaders()
{
	if (_headersSent)
		throw Exceptions::HeadersAlreadySent();

	for (MultiMap<String, String>::Iterator i(_headers); i.hasNext(); i++)
		_stream << i.key() << ": " << i.value() << "\r\n";
	_stream << "\r\n" << std::flush;

	_headersSent = true;
}

void Request::redirect(const String& location, int httpCode)
{
	setStatus(httpCode);
	setHeader("Location", location);
}

bool Request::headersSent() const
{ return _headersSent; }

String Request::header(const String& name) const
{ return _headers.getFirst(name); }

void Request::setCookie(const String& name,
                        const String& value,
                        ExpiryPolicy expiryPolicy,
                        const String& path,
                        const String& domain,
                        bool https)
{
	DateTimeDuration duration;
	if (expiryPolicy == Never)
		duration += DateTimeDuration("0005-00-00");
	else if (expiryPolicy == OneMonth)
		duration += DateTimeDuration("0000-01-00");
	setCookie(name, value, duration, path, domain, https);
}

void Request::setCookie(const String& name,
                        const String& value,
                        const DateTimeDuration& duration,
                        const String& path,
                        const String& domain, bool https)
{
	String str = name.urlEscape() + "=" + value.urlEscape();
	if (!domain.isNull())
		str += "; Domain=" + domain.replace(";", "");
	str += "; Path=" + path.replace(";", "");
	if (!duration.isNull())
		str += "; Expires=" + (DateTime::now() + duration).toRfc822();
	if (https)
		str += "; Secure";
	setHeader("Set-Cookie", str, true);
}

void Request::setSession(const String& name, const String& value) const
{ _session->setValue(name, value); }

//----------------------------------------------------------------------------//

String Request::uri() const
{ return _env["REQUEST_URI"]; }

String Request::mimeType() const
{ return _mimeType; }

String Request::charset() const
{ return _charset; }

String Request::env(const String& variable, const String& defaultValue) const
{ return _env.get(variable, defaultValue).secure(); }

bool Request::hasGet(const String& variable) const
{ return _get.hasKey(variable); }

String Request::get(const String& variable, const String& defaultValue) const
{ return _get.get(variable, defaultValue); }

String Request::post(const String& variable, const String& defaultValue) const
{ return _post.get(variable, defaultValue); }

String Request::cookie(const String& name, const String& defaultValue) const
{ return _cookies.get(name, defaultValue); }

String Request::session(const String& name, const String& defaultValue) const
{ return _session->value(name, defaultValue); }

bool Request::hasCookie(const String& name) const
{ return _cookies.hasKey(name); }

bool Request::isPost() const
{ return _isPost; }

IpAddr Request::ip() const
{ return _ip; }

UserAgent Request::userAgent()
{
	if (!_userAgentParsed)
	{
		_userAgent = UserAgent::fromString(_env["HTTP_USER_AGENT"].secure());
		_userAgentParsed = true;
	}
	return _userAgent;
}

RequestProfile* Request::profile() const
{ return _profile; }

Locale* Request::locale() const
{ return _locale; }

void Request::setLocale(const String& locale)
{
	//if(System::setting("Locale/Locales").split(",").contains(locale))
	_locale = Locale::get(locale);
}

void Request::setLocale(Locale* locale)
{
	//if(System::setting("Locale/Locales").split(",").contains(locale->name()))
	_locale = locale;
}

RequestStream& Request::stream()
{
	if (!_headersSent)
		sendHeaders();
	return _stream;
}

FCGX_Request* Request::fcgiRequest() const
{ return _fcgiRequest; }
