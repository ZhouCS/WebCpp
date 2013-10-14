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
 * @file Types/Time.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

#include <boost/date_time/local_time/posix_time_zone.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>

#include "Types/Time.h"
#include "Types/String.h"
#include "Types/StringList.h"
#include "Types/ByteArray.h"
#include "Libs/IO/File.h"
#include "Types/Date.h"
#include "Types/DateTime.h"
#include "Types/Map.h"

Time::Time()
  : _isNull(true),
    _tz(TimeZone::get("UTC"))
{}

Time::Time(int hours, int minutes, int seconds, const TimeZone *tz)
  : _tz(tz == nullptr ? TimeZone::get("UTC") : tz),
    _time(hours, minutes, seconds)
{ }

Time::Time(const String& time, const TimeZone* tz)
  : _isNull(false),
    _tz(tz == nullptr ? TimeZone::get("UTC") : tz)
{
	_time = boost::posix_time::duration_from_string(time.toStdString());
}

Time Time::now()
{
	return Time(boost::posix_time::to_simple_string(
	              boost::posix_time::second_clock::universal_time()
	              .time_of_day()));
}

int Time::hours() const
{ return _time.hours(); }

int Time::minutes() const
{ return _time.minutes(); }

int Time::seconds() const
{ return _time.seconds(); }

const TimeZone* Time::timeZone() const
{ return _tz; }

String Time::toString() const
{ return boost::posix_time::to_simple_string(_time); }

Time Time::operator+(const Time& time) const
{
	Time t = *this;
	t += time;
	return t;
}
void Time::operator+=(const Time& time)
{
	_time = _time + time._time;
}

//----------------------------------------------------------------------------//

Map<String, TimeZone*> TimeZone::_tzList;

TimeZone::TimeZone(const String& name)
{
	setenv("TZ", ":" + name, 1);
	tzset();
	StringList lines = String(File::getContent("/usr/share/zoneinfo/" + name))
	                   .split("\n");

	for (int i = 0; i < lines.count(); i++)
	{
		if (lines[i].startsWith(tzname[0]))
		{
			_posixTz = lines[i];
			break;
		}
	}

	if (_posixTz.contains("-"))
		_posixTz = _posixTz.replace("-", "");
	else
		_posixTz = _posixTz.insert(strlen(tzname[0]), "-");

	_tz = boost::local_time::time_zone_ptr(
	        new boost::local_time::posix_time_zone(_posixTz.toStdString()));
}

TimeZone* TimeZone::get(const String& name)
{
	TimeZone* tz = _tzList.get(name, nullptr);
	if (tz == nullptr)
	{
		tz = new TimeZone(name);
		_tzList[name] = tz;
	}
	return tz;
}

Time TimeZone::local(const Time& time) const
{
	boost::local_time::local_date_time d(boost::posix_time::ptime(boost::gregorian::day_clock::universal_day(), time._time), _tz);
	return Time(String(boost::posix_time::to_iso_extended_string(d.local_time())).section("T", -1, -1), this);
}

DateTime TimeZone::local(const DateTime& dateTime) const
{
	boost::local_time::local_date_time d(boost::posix_time::ptime(dateTime._date, dateTime._time), _tz);
	return DateTime(String(boost::posix_time::to_iso_extended_string(d.local_time())).replace("T", " "), this);
}
