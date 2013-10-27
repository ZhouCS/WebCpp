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
 * @file Requests/Request.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-23
 */

#ifndef _WPP_REQUESTS_REQUEST_H_
#define _WPP_REQUESTS_REQUEST_H_

#include "Types/String.h"
#include "Types/Map.h"
#include "Types/MultiMap.h"
#include "Types/IpAddr.h"
#include "Requests/RequestStream.h"
#include "Requests/UserAgent.h"

struct FCGX_Request;

class RequestThread;
class RequestProfile;
class Session;
class DateTimeDuration;
class Locale;

/**
 * @class Request Requests/Request.h <Request>
 * @brief A request instance
 */
class Request
{
public:
	enum ExpiryPolicy{Delete, Never, OneMonth, SessionCookie};

	/**
	 * @brief Constructs a request
	 * @param fcgiRequest The FastCGI request object
	 */
	explicit Request(FCGX_Request* fcgiRequest);

	/**
	 * @brief Destrucsts a request
	 */
	~Request();


	/**
	 * @brief Ask the request to be processed
	 */
	void process();


	/**
	 * @brief Get the requested URI (e.g. /foo/bar?lorem=ipsum)
	 */
	String uri() const;

	/**
	 * @brief Get a environment variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the environment variable
	 *                     doesn't exist
	 * @return The variable value with the given name
	 */
	String env(const String& variable,
	           const String& defaultValue = String()) const;

	bool hasGet(const String& variable) const;

	/**
	 * @brief Get a GET variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the GET variable doesn't
	 *                     exist
	 * @return The variable value with the given name
	 */
	String get(const String& variable,
	           const String& defaultValue = String()) const;

	/**
	 * @brief Get a POST variable
	 * @param variable The variable name
	 * @param defaultValue A default value to return if the POST variable doesn't
	 *                     exist
	 * @return The variable value with the given name
	 */
	String post(const String& variable,
	            const String& defaultValue = String()) const;

	/**
	 * @brief Get a cookie
	 * @param name The cookie name
	 * @param defaultValue A default value to return if the cookie doesn't exist
	 * @return The cookie value with the given name
	 */
	String cookie(const String& name,
	              const String& defaultValue = String()) const;

	/**
	 * @brief Get a session variable
	 * @param name The session variable name
	 * @param defaultValue A default value to return if the session variable
	 *                     doesn't exist
	 * @return The session variable value with the given name
	 */
	String session(const String& name,
	               const String& defaultValue = String()) const;

	bool hasCookie(const String& name) const;

	/**
	 * @brief Determines if the request is a POST one
	 * @return true if the request is a POST one, otherwise false
	 */
	bool isPost() const;

	/**
	 * @brief Get the client's IP address
	 */
	IpAddr ip() const;

	/**
	 * @brief Get the client's user agent
	 */
	UserAgent userAgent();

	/**
	 * @brief Get the request profile
	 */
	RequestProfile* profile() const;

	/**
	 * @brief Get the client's locale
	 */
	Locale* locale() const;

	void setLocale(const String& locale);
	void setLocale(Locale* locale);


	/**
	 * @brief Set an HTTP header
	 * @param name The HTTP header name (e.g. “Content-Language”)
	 * @param value The header value
	 * @param insert If true, a new header will be insert even if a header with
	 *               that name already exists
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void setHeader(const String& name, const String& value, bool insert = false);

	/**
	 * @brief Set the HTTP response code
	 * @param httpCode The HTTP response code
	 */
	void setStatus(int httpCode);

	/**
	 * @brief Set the content type of the document
	 * @param mimeType The document MIME type
	 * @param charset The document's charset
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void setContentType(const String& mimeType, const String& charset = String());

	/**
	 * @brief Get the request MIME content type
	 */
	String mimeType() const;

	/**
	 * @brief Get the request HTTP output charset
	 */
	String charset() const;

	/**
	 * @brief Explicitly send HTTP headers
	 * @warning Headers mustn't already be sent. If they already been, an
	 *          exception will be thrown.
	 */
	void sendHeaders();

	/**
	 * @brief Redirect the client to an other location
	 * @param location The new location to redirect to
	 * @param httpCode The HTTP response code
	 */
	void redirect(const String& location, int httpCode = 303);

	/**
	 * @brief Determines whether headers were sent
	 * @return true if headers were sent, otherwise false
	 */
	bool headersSent() const;

	/**
	 * @brief Get an HTTP header by name
	 * @param name The header name
	 */
	String header(const String& name) const;

	void setCookie(const String& name,
	               const String& value,
	               ExpiryPolicy expiryPolicy = OneMonth,
	               const String& path = "/",
	               const String& domain = String(),
	               bool https = false);

	void setCookie(const String& name,
	               const String& value,
	               const DateTimeDuration& duration,
	               const String& path = "/",
	               const String& domain = String(),
	               bool https = false);

	/**
	 * @brief Set a session variable
	 * @param name The variable name
	 * @param value The variable value
	 */
	void setSession(const String& name, const String& value) const;

	//void setCookie(const String& name, const String& value, DateT);



	/**
	 * @brief Get the request stream
	 */
	RequestStream& stream();

	/**
	 * @brief Get the FastCGI request object
	 * @return The FastCGI request object
	 */
	FCGX_Request* fcgiRequest() const;

private:
	static Map<int, String> _statusList;

	/**
	 * @brief The FastCGI request object
	 */
	FCGX_Request* _fcgiRequest;

	/**
	 * @brief The output request stream
	 */
	RequestStream _stream;

	/**
	 * @brief The input request stream
	 */
	RequestInputStream _inputStream;

	/**
	 * @brief The user locale
	 */
	Locale* _locale;

	/**
	 * @brief The client's user agent
	 */
	UserAgent _userAgent;

	/**
	 * @brief Defines if the user agent was pared
	 */
	bool _userAgentParsed;

	/**
	 * @brief The request's profile
	 */
	RequestProfile* _profile;

	/**
	 * @brief Defines if the request is a POST one
	 */
	bool _isPost;

	/**
	 * @brief The client's remote IP address
	 */
	IpAddr _ip;

	/**
	 * @brief The client's session
	 */
	Session* _session;

	/**
	 * @brief The MIME content type
	 */
	String _mimeType;

	/**
	 * @brief The HTTP output charset
	 */
	String _charset;

	/**
	 * @brief The environment variables
	 */
	Map<String, String> _env;

	/**
	 * @brief The GET arguments
	 */
	Map<String, String> _get;

	/**
	 * @brief The POST variables
	 */
	Map<String, String> _post;

	/**
	 * @brief The cookies
	 */
	Map<String, String> _cookies;

	/**
	 * @brief HTTP headers
	 */
	MultiMap<String, String> _headers;

	/**
	 * @brief Defines whether the headers were sent
	 */
	bool _headersSent;

	/**
	 * @brief The requested path (without GET variables)
	 */
	String _path;
};

#endif // !_WPP_REQUESTS_REQUEST_H_
