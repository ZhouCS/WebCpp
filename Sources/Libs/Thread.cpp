 /*******************************************************************************
 * Copyright © 2011 Kévin Lesénéchal <kevin@lesenechal.org>                     *
 *                                                                              *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.                   *
 *                                                                              *
 * WebCpp is free software: you can redistribute it and/or modify it     *
 * it under the terms of the GNU Affero General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU Affero General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the GNU Affero General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 ********************************************************************************/

/**
 * @file Libs/Thread.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-19
 */

#include "Libs/Thread.h"

Thread::Thread(void* (*funcPtr)(void*))
  : _funcPtr(funcPtr)
{

}

void Thread::start()
{
	pthread_create(&_thread, nullptr,
	               _funcPtr == nullptr ? pthreadRun : _funcPtr,
	               _funcPtr == nullptr ? static_cast<void*>(this) : nullptr);
}

void Thread::wait()
{
	pthread_join(_thread, nullptr);
}

void Thread::stop()
{
	pthread_cancel(_thread);
}

void* Thread::pthreadRun(void* thread)
{
	((Thread*)thread)->run();
	return nullptr;
}

void Thread::run()
{ }

//----------------------------------------------------------------------------//

Thread::Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, nullptr);
}

void Thread::Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void Thread::Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

void Thread::Mutex::setLocked(bool locked)
{
	if (locked)
		lock();
	else
		unlock();
}
