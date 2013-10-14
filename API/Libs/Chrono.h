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
 * @file Libs/Chrono.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-25
 */

#ifndef _LIBS_CHRONO_H_
#define	_LIBS_CHRONO_H_

//#include <sys/time.h>
#include <chrono>

/**
 * @brief A chronometer with microseconds precision
 */
class Chrono
{
public:
	/**
	 * @brief Constructs a chronometer
	 * @param autoStart if true, starts the chronometer
	 */
	explicit Chrono(bool autoStart = false);

	/**
	 * @brief Starts the chronometer
	 */
	void start();

	/**
	 * @brief Stops the chronometer
	 */
	void stop();

	/**
	 * @brief Resets elapsed time
	 */
	void reset();

	/**
	 * @brief Returns the elapsed time
	 */
	double elapsed() const;

private:
	/**
	 * @brief Defines whenever the chronometer is running
	 */
	bool _running;

	/**
	 * @brief The elapsed time
	 */
	double _elapsed;

	/**
	 * @brief The POSIX timeval object
	 */
	std::chrono::time_point<std::chrono::system_clock> _startTime;
};

#endif // !_LIBS_CHRONO_H_
