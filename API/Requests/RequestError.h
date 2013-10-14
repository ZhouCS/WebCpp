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
 * @file Requests/RequestError.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-04-19
 */

#ifndef _REQUESTS_REQUESTERROR_H_
#define _REQUESTS_REQUESTERROR_H_

class Request;
class Template;

#include "Exceptions/Exception.h"
#include "Exceptions/Segfault.h"

/**
 * @class RequestError Requests/RequestError.h <RequestError>
 * @brief A request error handler
 */
class RequestError
{
public:
	static void exception(Request* request, Exception& e);
	static void stdException(Request* request, const std::exception& e);
	static void segfault(Request* request, Exceptions::Segfault& e);

private:
	static void loadStackTrace(Exception& e, Template* tpl);
	static void fallbackErrorPage(Request* request,
	                              const Exception& e,
	                              const String& e2Name);
	static void fallbackErrorPage(Request* request,
	                              const std::exception& e,
	                              const String& e2Name);
};

#endif // !_REQUESTS_REQUESTERROR_H_
