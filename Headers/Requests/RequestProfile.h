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
 * @file Requests/RequestProfile.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-15
 */

#ifndef _REQUESTS_REQUESTPROFILE_H_
#define _REQUESTS_REQUESTPROFILE_H_

#include "Types/Map.h"

/**
 * @class RequestProfile Requests/RequestProfile.h <RequestProfile>
 * @brief A request profile
 */
class RequestProfile
{
public:
	enum Chrono{Total, System, Database, Templates};
	enum Counter{SqlQueries};

	/**
	 * @brief Constructs a request profile
	 */
	RequestProfile();

	/**
	 * @brief Adds time to a chronomer of the profile
	 * @param chrono The profile's chrono
	 * @param time The time to add
	 */
	void addChronoTime(Chrono chrono, double time);

	double chronoTime(Chrono chrono) const;

	void incrementCounter(Counter counter, int value = 1);

	int counter(Counter counter) const;

	uint8_t id() const;

public:
	static RequestProfile* profile(uint8_t id);
	static void deleteProfiles();

private:
	/**
	 * @brief The current profiles counter
	 */
	static uint8_t _counter;

	/**
	 * @brief The profiles list
	 */
	static Map<uint8_t, RequestProfile*> _profiles;

private:
	/**
	 * @brief The profile ID
	 */
	uint8_t _id;

	/**
	 * @brief Profile's chrono times
	 */
	Map<int, double> _chronos;

	Map<int, int> _counters;
};

#endif // !_REQUESTS_REQUESTPROFILE_H_
