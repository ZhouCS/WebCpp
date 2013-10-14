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
 * @file Requests/RequestThread.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-21
 */

#include "Requests/RequestThread.h"
#include "Requests/Request.h"
#include "Libs/Thread.h"
#include "System.h"

#include <fcgiapp.h>

void* fcgiProcessingLoop(void*)
{
	static Thread::Mutex acceptMutex;
	FCGX_Request fcgiRequest;

	while (System::isRunning())
	{
		FCGX_InitRequest(&fcgiRequest,
		                 System::get()->socket(),
		                 FCGI_FAIL_ACCEPT_ON_INTR);

		acceptMutex.lock();
		FCGX_Accept_r(&fcgiRequest);
		acceptMutex.unlock();

		Request* request = new Request(&fcgiRequest);
		request->process();
		delete request;

		FCGX_Finish_r(&fcgiRequest);
	}
	return nullptr;
}
