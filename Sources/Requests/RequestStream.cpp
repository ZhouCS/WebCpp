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
 * @file RequestStream.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#include "Requests/RequestStream.h"
#include "Requests/Request.h"

#include <iostream>
#include <fcgio.h>

RequestStream::RequestStream(Request* request)
  : std::ostream(new fcgi_streambuf(request->fcgiRequest()->out))
{ }

RequestStream::~RequestStream()
{
	delete rdbuf();
}

//----------------------------------------------------------------------------//

RequestInputStream::RequestInputStream(Request* request)
  : std::istream(new fcgi_streambuf(request->fcgiRequest()->in))
{ }

RequestInputStream::~RequestInputStream()
{
	delete rdbuf();
}
