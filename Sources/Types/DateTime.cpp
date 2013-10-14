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
 * @file Types/DateTime.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

#include "Types/DateTime.h"
#include "Types/String.h"

DateTime::DateTime() : Date(), Time()
{ }

DateTime::DateTime(int years, int months, int days, int hours, int minutes,
                   int seconds, const TimeZone* tz)
  : Date(years, months, days),
    Time(hours, minutes, seconds, tz)
{ }

DateTime::DateTime(const String& dateTime, const TimeZone* tz)
  : Date(dateTime.section(" ", 0, 0)),
    Time(dateTime.section(" ", -1, -1), tz)
{ }

DateTime DateTime::now()
{
	return DateTime(String(boost::posix_time::to_iso_extended_string(
	                         boost::posix_time::second_clock::universal_time()))
	                .replace("T", " "));
}

DateTime DateTime::toLocal(const String& tz) const
{ return toLocal(TimeZone::get(tz)); }

DateTime DateTime::toLocal(const TimeZone* tz) const
{ return tz->local(*this); }

String DateTime::toString(const String& format) const
{
	std::stringstream ss;
	boost::posix_time::time_facet* facet = new boost::posix_time::time_facet;
	facet->format(format.toCString());
	ss.imbue(std::locale(std::locale::classic(), facet));
	ss << ptime();
	return ss.str();
}

std::tm DateTime::toStdTm() const
{
	std::tm t = std::tm();
	t.tm_year = year() - 1900;
	t.tm_mon = month();
	t.tm_mday = day();

	if (dayOfWeek() == Date::Mon)
		t.tm_wday = 6;
	else
		t.tm_wday = static_cast<int>(dayOfWeek()) - 1;

	t.tm_yday = dayOfYear();

	t.tm_hour = hours();
	t.tm_min = minutes();
	t.tm_sec = seconds();
	return t;
}

String DateTime::toRfc822() const
{ return toString("%a, %d %b %Y %H:%M:%S GMT"); }


boost::posix_time::ptime DateTime::ptime() const
{ return boost::posix_time::ptime(_date, _time); }


DateTime DateTime::operator+(const Time& time) const
{
	DateTime d = *this;
	d += time;
	return d;
}
void DateTime::operator+=(const Time& time)
{
	boost::posix_time::ptime p(_date, _time);
	p = p + time._time;
	_date = p.date();
	_time = p.time_of_day();
}

DateTime DateTime::operator+(const DateDuration& date) const
{
	DateTime d = *this;
	d += date;
	return d;
}
void DateTime::operator+=(const DateDuration& date)
{
	boost::gregorian::date d(year(), month(), day());
	d = d + boost::date_time::year_functor<boost::gregorian::date>(date.years())
	    .get_offset(d);
	d = d + boost::date_time::month_functor<boost::gregorian::date>(date.months())
	    .get_offset(d);
	d = d + boost::date_time::day_functor<boost::gregorian::date>(date.days())
	    .get_offset(d);

	boost::gregorian::date_duration dur = d - boost::gregorian::date(year(),
	                                                                 month(),
	                                                                 day());
	boost::posix_time::ptime p(_date, _time);
	p = p + boost::gregorian::days(dur.days());
	_date = p.date();
	_time = p.time_of_day();
}

DateTime DateTime::operator+(const DateTimeDuration& duration) const
{
	DateTime d = *this;
	d += duration;
	return d;
}
void DateTime::operator+=(const DateTimeDuration& duration)
{
	operator+=(duration._timeDuration);
	operator+=(duration._dateDuration);
}

DateTime DateTime::operator+(const String& duration) const
{
	DateTime d = *this;
	d += duration;
	return d;
}
void DateTime::operator+=(const String& duration)
{ operator+=(DateTimeDuration(duration)); }


DateTime DateTime::operator-(const Time& time) const
{
	DateTime d = *this;
	d -= time;
	return d;
}
void DateTime::operator-=(const Time& time)
{
	boost::posix_time::ptime p(_date, _time);
	p = p - time._time;
	_date = p.date();
	_time = p.time_of_day();
}

DateTime DateTime::operator-(const DateDuration& date) const
{
	DateTime d = *this;
	d -= date;
	return d;
}
void DateTime::operator-=(const DateDuration& date)
{
	boost::gregorian::date d(year(), month(), day());
	d = d - boost::date_time::day_functor<boost::gregorian::date>(date.days())
	    .get_offset(d);
	d = d - boost::date_time::month_functor<boost::gregorian::date>(date.months())
	    .get_offset(d);
	d = d - boost::date_time::year_functor<boost::gregorian::date>(date.years())
	    .get_offset(d);

	boost::gregorian::date_duration dur = boost::gregorian::date(year(), month(),
	                                                             day()) - d;
	boost::posix_time::ptime p(_date, _time);
	p = p - boost::gregorian::days(dur.days());
	_date = p.date();
	_time = p.time_of_day();
}

DateTime DateTime::operator-(const DateTimeDuration& duration) const
{
	DateTime d = *this;
	d -= duration;
	return d;
}
void DateTime::operator-=(const DateTimeDuration& duration)
{
	operator-=(duration._timeDuration);
	operator-=(duration._dateDuration);
}

DateTime DateTime::operator-(const String& duration) const
{
	DateTime d = *this;
	d -= duration;
	return d;
}
void DateTime::operator-=(const String& duration)
{ operator-=(DateTimeDuration(duration)); }


bool DateTime::operator<(const DateTime& dateTime) const
{ return ptime() < dateTime.ptime(); }

bool DateTime::operator>(const DateTime& dateTime) const
{ return ptime() > dateTime.ptime(); }

//----------------------------------------------------------------------------//

DateTimeDuration::DateTimeDuration()
{ _isNull = true; }

DateTimeDuration::DateTimeDuration(const String& dateTimeDuration)
{
	_isNull = false;
	String d = "0000-00-00", t = "00:00:00";
	if (dateTimeDuration.contains(" "))
	{
		d = dateTimeDuration.section(" ", 0, 0);
		t = dateTimeDuration.section(" ", -1, -1);
	}
	else if (dateTimeDuration.contains("-"))
		d = dateTimeDuration;
	else
		t = dateTimeDuration;

	_dateDuration = DateDuration(d);
	_timeDuration = Time(t);
}

bool DateTimeDuration::isNull() const
{ return _isNull; }

DateTimeDuration
DateTimeDuration::operator+(const DateTimeDuration& duration) const
{
	DateTimeDuration d;
	d += duration;
	return d;
}
void DateTimeDuration::operator+=(const DateTimeDuration& duration)
{
	_dateDuration += duration._dateDuration;
	_timeDuration += duration._timeDuration;
}
