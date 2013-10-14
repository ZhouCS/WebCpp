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
 * @file Requests/RequestStream.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#ifndef _REQUESTS_REQUESTSTREAM_H_
#define _REQUESTS_REQUESTSTREAM_H_

#include <fcgio.h>

class Request;

#include <cstdlib>

/**
 * @class RequestStream Requests/RequestStream.h <RequestStream>
 * @brief An output request stream
 */
class RequestStream : public std::ostream
{
public:
	/**
	 * @brief Constructs an output request stream
	 * @param request The associated request
	 */
	RequestStream(Request* request);
	~RequestStream();

	std::ostream& flush()
	{
		return std::ostream::flush();
	}
};

/**
 * @brief An input request stream
 */
class RequestInputStream : public std::istream
{
public:
	/**
	 * @brief Constructs an input request stream
	 * @param request The associated request
	 */
	RequestInputStream(Request* request);
	~RequestInputStream();
};

#endif // !_REQUESTS_REQUESTSTREAM_H_
