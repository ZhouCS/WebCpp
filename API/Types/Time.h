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
 * @file Types/Time.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

#ifndef _TYPES_TIME_H_
#define	_TYPES_TIME_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

#include "Types/String.h"
#include "Types/Map.h"

class DateTime;
class TimeZone;

/**
 * @class Time Types/Time.h <Time>
 * @brief A time representation
 */
class Time
{
	friend class DateTimeDuration;
	friend class DateTime;
	friend class TimeZone;
public:
	Time();
	Time(int hours, int minutes, int seconds, const TimeZone* tz = nullptr);
	Time(const String& time, const TimeZone* tz = nullptr);

	static Time now();

	int hours() const;
	int minutes() const;
	int seconds() const;

	const TimeZone* timeZone() const;

	String toString() const;

	Time operator+(const Time& time) const;
	void operator+=(const Time& time);

private:
	bool _isNull;

protected:
	const TimeZone* _tz;

	boost::posix_time::time_duration _time;
};

//----------------------------------------------------------------------------//

class TimeZone
{
public:
	explicit TimeZone(const String& name);

	static TimeZone* get(const String& name);

	Time local(const Time& time) const;
	DateTime local(const DateTime& dateTime) const;

private:
	static Map<String, TimeZone*> _tzList;
	String _posixTz;
	boost::local_time::time_zone_ptr _tz;
};

#endif // !_TYPES_TIME_H_
