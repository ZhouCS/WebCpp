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
 * @file Libs/Locale/Locale.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-24
 */

#ifndef _LIBS_LOCALE_LOCALE_H_
#define	_LIBS_LOCALE_LOCALE_H_

#include "Types/String.h"
#include "Types/Map.h"

#include <locale>

class DateTime;

/**
 * @class Locale Libs/Locale/Locale.h <Locale>
 * @brief A locale
 */
class Locale
{
public:
	enum DatePosition{YMD, DMY, MDY};
	enum DateFormat{NoDate, DigitalDate, ShortDate, LongDate};
	enum TimeFormat{NoTime, HoursMinutes, HoursMinutesSeconds};
	enum DateFormatOptions
	{
		NoOptions     = 0x0,
		RelativeDays  = 0x1,
		ArticleBefore = 0x2
	};

	/**
	 * @brief Constructs a locale
	 * @param name The locale name like “en_US”
	 */
	Locale(const String& name);

	/**
	 * @brief Get the default locale
	 */
	static Locale* defaultLocale();

	String parseNumber(long n) const;

	String parseNumber(float n, int precision = -1) const;

	String parseNumber(double n, int precision = -1) const;

	String parseSize(uint64_t size);

	String parseMoney(double n, String currency = String()) const;

	String parseDateTime(const DateTime& dateTime, const String& format) const;

	String parseDateTime(const DateTime& dateTime,
	                     DateFormat dateFormat = LongDate,
	                     TimeFormat = HoursMinutes,
	                     int options = RelativeDays | ArticleBefore) const;

	String parseDateTime(const DateTime& dateTime,
	                     DateFormatOptions options) const;

	String name() const;

	String lang() const;

	static Locale* get(const String& name);

private:
	static Map<String, Locale*> _locales;

	/**
	 * @brief The default locale
	 */
	static Locale* _defaultLocale;

	/**
	 * @brief The standard locale object
	 */
	std::locale _locale;

	/**
	 * @brief The language code (e.g. “en”)
	 */
	String _lang;

	/**
	 * @brief The country code (e.g. “US”)
	 */
	String _country;

	DatePosition _datePosition;

	Map<String, String> _currencySymbols;
};

#endif // !_LIBS_LOCALE_LOCALE_H_
