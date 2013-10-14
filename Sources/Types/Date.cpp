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
 * @file Types/Date.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

//#include <boost/date_time/gregorian/parsers.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/parsers.hpp>

#include "Types/Date.h"
#include "Types/String.h"

Date::Date()
{ }

Date::Date(int years, int months, int days)
  : _date(years, months, days)
{ }

Date::Date(const String& date)
{
	_date = boost::gregorian::from_string(date.toStdString());
}

Date Date::now()
{
	return Date(boost::gregorian::to_iso_extended_string(
	              boost::gregorian::day_clock::universal_day()));
}

int Date::year() const
{ return _date.year(); }

Date::Month Date::month() const
{ return static_cast<Month>(static_cast<int>(_date.month())); }

int Date::day() const
{ return _date.day(); }

Date::DayOfWeek Date::dayOfWeek() const
{
	int dow = _date.day_of_week();
	if (dow == 0)
		dow = 6;
	else
		dow--;
	return static_cast<DayOfWeek>(dow);
}

int Date::dayOfYear() const
{ return _date.day_of_year(); }

String Date::toString() const
{ return boost::gregorian::to_iso_extended_string(_date); }

Date Date::operator+(const DateDuration& duration) const
{
	Date d = *this;
	d += duration;
	return d;
}
void Date::operator+=(const DateDuration& duration)
{
	_date = _date + boost::date_time::year_functor<boost::gregorian::date>(
	          duration.years()).get_offset(_date);
	_date = _date + boost::date_time::month_functor<boost::gregorian::date>(
	          duration.months()).get_offset(_date);
	_date = _date + boost::date_time::day_functor<boost::gregorian::date>(
	          duration.days()).get_offset(_date);
}

bool Date::operator==(const Date& date) const
{ return _date == date._date; }

bool Date::operator<(const Date& date) const
{ return _date < date._date; }

bool Date::operator>(const Date& date) const
{ return _date > date._date; }

bool Date::operator<=(const Date& date) const
{ return _date <= date._date; }

bool Date::operator>=(const Date& date) const
{ return _date >= date._date; }

//----------------------------------------------------------------------------//

DateDuration::DateDuration()
{
	_isNull = true;
	_years = 0;
	_months = 0;
	_days = 0;
}

DateDuration::DateDuration(const String& dateDuration)
{
	_isNull = false;

	_years = dateDuration.section("-", 0, 0).toInt();
	_months = dateDuration.section("-", 1, 1).toInt();
	_days = dateDuration.section("-", 2, 2).toInt();
}

int DateDuration::years() const
{ return _years; }

int DateDuration::months() const
{ return _months; }

int DateDuration::days() const
{ return _days; }

DateDuration DateDuration::operator+(const DateDuration& duration) const
{
	DateDuration d = *this;
	d += duration;
	return d;
}
void DateDuration::operator+=(const DateDuration& duration)
{
	_days += duration._days;
	_months += duration._months;
	_years += duration._years;
}
