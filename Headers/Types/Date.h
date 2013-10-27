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
 * @file Types/Date.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-23
 */

#ifndef _WPP_TYPES_DATE_H_
#define	_WPP_TYPES_DATE_H_

#include <boost/date_time/gregorian/greg_date.hpp>

class String;
class DateDuration;

/**
 * @class Date Types/Date.h <Date>
 * @brief A date representation
 */
class Date
{
public:
	/**
	 * @brief The week days
	 */
	enum DayOfWeek{Mon, Tue, Wed, Thu, Fri, Sat, Sun};

	/**
	 * @brief The months list
	 */
	enum Month{NoMonth, Jan, Feb, Mar, Apr, May,
		         Jun, Jul, Aug, Sep, Oct, Nov, Dec};

	/**
	 * @brief Constructs an empty date
	 */
	Date();

	/**
	 * @brief Constructs a date from year, month and day
	 * @param year The year (e.g. 2012)
	 * @param month The month (e.g. 1 or Jan)
	 * @param day The month day (e.g. 23)
	 */
	Date(int year, int month, int day);

	/**
	 * @brief Constructs a date from a string
	 * @param date The date string (e.g. "2012-01-23")
	 */
	Date(const String& date);

	/**
	 * @brief Get the current UTC date
	 * @return The current UTC date
	 */
	static Date now();

	/**
	 * @brief Get the year
	 */
	int year() const;

	/**
	 * @brief Get the month
	 */
	Month month() const;

	/**
	 * @brief Get the month day
	 */
	int day() const;

	/**
	 * @brief Get the day of the week (e.g. Mon)
	 */
	DayOfWeek dayOfWeek() const;

	/**
	 * @brief Get the day of the year (e.g. 287)
	 */
	int dayOfYear() const;

	/**
	 * @brief Returns the string representation of the date (e.g. "2012-01-23")
	 */
	String toString() const;

	Date operator+(const DateDuration& duration) const;
	void operator+=(const DateDuration& duration);

	bool operator==(const Date& date) const;

	bool operator<(const Date& date) const;
	bool operator>(const Date& date) const;
	bool operator<=(const Date& date) const;
	bool operator>=(const Date& date) const;

protected:
	boost::gregorian::date _date;
};

class DateDuration
{
	friend class DateTimeDuration;
public:
	DateDuration();

	DateDuration(const String& dateDuration);

	int years() const;

	int months() const;

	int days() const;

	DateDuration operator+(const DateDuration& duration) const;
	void operator+=(const DateDuration& duration);

private:
	bool _isNull;
	int _years;
	int _months;
	int _days;
};

#endif // !_WPP_TYPES_DATE_H_
