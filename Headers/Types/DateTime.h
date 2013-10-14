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
 * @file Types/DateTime.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

#ifndef _TYPES_DATETIME_H_
#define	_TYPES_DATETIME_H_

#include "Types/Date.h"
#include "Types/Time.h"
#include "Types/String.h"

class DateTimeDuration;

/**
 * @class DateTime Types/DateTime.h <DateTime>
 * @brief A date / time representation
 */
class DateTime : public Date, public Time
{
	friend class TimeZone;
public:
	DateTime();

	DateTime(int years,
	         int months,
	         int days,
	         int hours,
	         int minutes,
	         int seconds,
	         const TimeZone* tz = nullptr);

	DateTime(const String& dateTime, const TimeZone* tz = nullptr);

	static DateTime now();

	DateTime toLocal(const String& tz) const;
	DateTime toLocal(const TimeZone* tz) const;

	String toString(const String& format = "%Y-%m-%d %H:%M:%S") const;

	std::tm toStdTm() const;

	String toRfc822() const;

	boost::posix_time::ptime ptime() const;

	DateTime operator+(const Time& time) const;
	void operator+=(const Time& time);

	DateTime operator+(const DateDuration& date) const;
	void operator+=(const DateDuration& date);

	DateTime operator+(const DateTimeDuration& duration) const;
	void operator+=(const DateTimeDuration& duration);

	DateTime operator+(const String& duration) const;
	void operator+=(const String& duration);

	DateTime operator-(const Time& time) const;
	void operator-=(const Time& time);

	DateTime operator-(const DateDuration& date) const;
	void operator-=(const DateDuration& date);

	DateTime operator-(const DateTimeDuration& duration) const;
	void operator-=(const DateTimeDuration& duration);

	DateTime operator-(const String& duration) const;
	void operator-=(const String& duration);

	bool operator<(const DateTime& dateTime) const;
	bool operator>(const DateTime& dateTime) const;
};

class DateTimeDuration
{
	friend class DateTime;
public:
	DateTimeDuration();

	DateTimeDuration(const String& dateTimeDuration);

	bool isNull() const;

	DateTimeDuration operator+(const DateTimeDuration& duration) const;
	void operator+=(const DateTimeDuration& duration);

private:
	bool _isNull;
	DateDuration _dateDuration;
	Time _timeDuration;
};

#endif // !_TYPES_DATETIME_H_
