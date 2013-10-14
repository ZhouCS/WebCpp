/********************************************************************************
 * Copyright © 2011 Kévin Lesénéchal <kevin.lesenechal@bilbax.com>              *
 *                                                                              *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.                   *
 *                                                                              *
 * * WebCpp is free software: you can redistribute it and/or modify it     **
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
 * \file Thread.h
 * \author Kévin Lesénéchal
 * \date 2011-11-19
 */

#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

/**
 * \class Thread Tools/Thread.h <Thread>
 * \brief A thread instance
 */
class Thread
{
public:
	/**
	 * \brief Constructs a thread instance
	 */
	Thread();
	
	/**
	 * \brief Starts the thread
	 */
	void start();
	
	/**
	 * \brief Waits until the thread is finished
	 */
	void wait();
	
	
	
	/**
	 * \brief A thread mutex
	 */
	class Mutex
	{
	public:
		/**
		 * \brief Constructs a mutex
		 */
		Mutex();
		
		/**
		 * \brief Locks the mutex
		 */
		void lock();
		
		/**
		 * \brief Unlocks the mutex
		 */
		void unlock();
		
		/**
		 * \brief Set whenever the mutex is locked or not
		 * \param locked true to lock the mutex, false to unlock
		 */
		void setLocked(bool locked);
	
	private:
		pthread_mutex_t _mutex;
	};

protected:
	/**
	 * \brief Implements the thread code to execute
	 */
	virtual void run() = 0;

private:
	/**
	 * \brief Static function called by pthread in order to start the thread
	 * \param thread The thread instance to start
	 */
	static void* pthreadRun(void *thread);

protected:
	/**
	 * \brief The pthread object
	 */
	pthread_t _thread;
};

#endif
