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
 * @file Libs/Thread.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-19
 */

#ifndef _WPP_LIBS_THREAD_H_
#define _WPP_LIBS_THREAD_H_

#include <pthread.h>

/**
 * @class Thread Libs/Thread.h <Thread>
 * @brief A thread instance
 */
class Thread
{
public:
	/**
	 * @brief Constructs a thread instance
	 */
	Thread(void* (*funcPtr)(void*) = nullptr);

	virtual ~Thread(){}

	/**
	 * @brief Starts the thread
	 */
	void start();

	/**
	 * @brief Waits until the thread is finished
	 */
	void wait();

	/**
	 * @brief Stops the thread
	 */
	void stop();



	/**
	 * @brief A thread mutex
	 */
	class Mutex
	{
	public:
		/**
		 * @brief Constructs a mutex
		 */
		Mutex();

		/**
		 * @brief Locks the mutex
		 */
		void lock();

		/**
		 * @brief Unlocks the mutex
		 */
		void unlock();

		/**
		 * @brief Set whenever the mutex is locked or not
		 * @param locked true to lock the mutex, false to unlock
		 */
		void setLocked(bool locked);

	private:
		pthread_mutex_t _mutex;
	};

protected:
	/**
	 * @brief Implements the thread code to execute
	 */
	virtual void run();

private:
	/**
	 * @brief Static function called by pthread in order to start the thread
	 * @param thread The thread instance to start
	 */
	static void* pthreadRun(void *thread);

protected:
	/**
	 * @brief The pthread object
	 */
	pthread_t _thread;

	void* (*_funcPtr)(void*);
};

#endif // !_WPP_LIBS_THREAD_H_
