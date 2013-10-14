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
 * @file Libs/Locale/Locale.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-24
 */

#include "Libs/Locale/Locale.h"
#include "Types/DateTime.h"
#include "Types/StringList.h"
#include "System.h"

#include <sstream>
#include <iostream>
#include <boost/date_time/time_facet.hpp>

Map<String, Locale*> Locale::_locales;
Locale* Locale::_defaultLocale = nullptr;

Locale::Locale(const String& name)
  : _locale(name + ".UTF-8")
{
	_lang = name.section("_", 0, 0);
	_country = name.section("_", -1, -1);

	if (_country.in({"AL", "CN", "HK", "HU", "IR", "JP", "KE", "KR", "LV", "LT",
	                "MN", "NP", "SG", "SI", "ZA", "DE", "MM", "SE"}))
		_datePosition = YMD;
	else if (_country.in({"BZ", "PH", "PW", "US"}))
		_datePosition = MDY;
	else
		_datePosition = DMY;

	_currencySymbols["EUR"] = "€";
	_currencySymbols["USD"] = "US$";
	_currencySymbols["CAD"] = "CA$";
	_currencySymbols["GBP"] = "£";
	_currencySymbols["JPY"] = "¥";
}

Locale* Locale::get(const String& name)
{
	Locale* locale = _locales.get(name, nullptr);
	if (locale == nullptr)
	{
		locale = new Locale(name);
		_locales[name] = locale;
	}
	return locale;
}

Locale* Locale::defaultLocale()
{
	if (_defaultLocale == nullptr)
		_defaultLocale = Locale::get(System::settings()->defaultLocale);
	return _defaultLocale;
}

String Locale::parseNumber(long n) const
{
	std::stringstream ss;
	ss.imbue(_locale);
	ss << n;
	return String(ss.str()).replace(" ", "\u202F").replace("-", "\u2212");
}

String Locale::parseNumber(float n, int precision) const
{
	std::stringstream ss;
	ss.imbue(_locale);
	if (precision == -1)
		ss << std::setprecision(7);
	else
		ss << std::fixed << std::setprecision(precision);
	ss << n;
	return String(ss.str()).replace(" ", "\u202F").replace("-", "\u2212");
}

String Locale::parseNumber(double n, int precision) const
{
	std::stringstream ss;
	ss.imbue(_locale);
	if (precision == -1)
		ss << std::setprecision(15);
	else
		ss << std::fixed << std::setprecision(precision);
	ss << n;
	return String(ss.str()).replace(" ", "\u202F").replace("-", "\u2212");
}

String Locale::parseSize(uint64_t size)
{
	String unit = _lang == "fr" ? "o" : "B";

	if (size < 1024)
		return parseNumber(static_cast<long>(size)) + "\u00A0" + unit;
	else if (size < 1024 * 1024)
		return parseNumber(size / 1024.0, 2) + "\u00A0Ki" + unit;
	else if (size < 1024 * 1024 * 1024)
		return parseNumber(size / (1024.0 * 1024.0), 2) + "\u00A0Mi" + unit;
	return parseNumber(size / (1024.0 * 1024.0 * 1024.0), 2) + "\u00A0Gi" + unit;
}

String Locale::parseMoney(double n, String currency) const
{
	String value = parseNumber(n, 2);

	if (currency.isNull())
		currency = System::setting("Locale.DefaultCurrency");
	String currencySymbol = _currencySymbols.get(currency, currency);

	if (_lang.in({"en"}))
		value = currencySymbol + value;
	else
		value = value + " " + currencySymbol;

	return value;
}

String Locale::parseDateTime(const DateTime& dateTime,
                             const String& format) const
{
	std::stringstream ss;
	boost::posix_time::time_facet* f
	    = new boost::posix_time::time_facet(format.toCString());
	ss.imbue(std::locale(_locale, f));
	ss << dateTime.ptime();
	return String(ss.str());
}

String Locale::parseDateTime(const DateTime& dateTime,
                             DateFormat dateFormat,
														 TimeFormat timeFormat,
                             int options) const
{
	String datePattern, timePattern, pattern;

	if (options & RelativeDays
	    && static_cast<Date>(dateTime)
	        == static_cast<Date>(DateTime::now().toLocal(dateTime.timeZone())))
	{
		datePattern = "aujourd’hui";
	}
	else if (options & RelativeDays
	         && static_cast<Date>(dateTime) <= static_cast<Date>(
	           DateTime::now().toLocal(dateTime.timeZone()) - "0000-00-01")
	         && static_cast<Date>(dateTime) > static_cast<Date>(
	           DateTime::now().toLocal(dateTime.timeZone()) - "0000-00-02"))
	{
		datePattern = "hier";
	}
	else if (options & RelativeDays
	         && static_cast<Date>(dateTime) >= static_cast<Date>(
	           DateTime::now().toLocal(dateTime.timeZone()) + "0000-00-01")
	         && static_cast<Date>(dateTime) < static_cast<Date>(
	           DateTime::now().toLocal(dateTime.timeZone()) + "0000-00-02"))
	{
		datePattern = "demain";
	}
	else
	{
		if (dateFormat == DigitalDate)
			datePattern = "%x";
		else if (dateFormat == ShortDate)
		{
			if (_datePosition == YMD)
				datePattern = "%Y %b %d";
			else if (_datePosition == MDY)
				datePattern = "%b %d %Y";
			else
				datePattern = "%d %b %Y";
		}
		else if (dateFormat == LongDate)
		{
			if (_datePosition == YMD)
				datePattern = "%Y %B %d";
			else if (_datePosition == MDY)
				datePattern = "%B %d %Y";
			else
				datePattern = "%d %B %Y";
		}

		if (options & ArticleBefore)
			datePattern = "le " + datePattern;
	}

	if (timeFormat == HoursMinutes)
	{
		if (_country.in({"AU", "BD", "CA", "CO", "CR", "EG", "SV", "GH", "HN", "HK",
		                "IN", "IR", "IE", "JO", "MY", "MX", "NZ", "NI", "NG", "PK",
		                "PH", "SA", "SG", "UK", "US", "VE"}))
			timePattern = "%I:%M %p";
		else
			timePattern = "%H:%M";
	}
	else if (timeFormat == HoursMinutesSeconds)
		timePattern = "%X";

	if (dateFormat != NoDate && timeFormat != NoTime)
		pattern = datePattern + " à " + timePattern;
	else if (dateFormat != NoDate)
		pattern = datePattern;
	else
		pattern = timePattern;

	return parseDateTime(dateTime, pattern);
}

String Locale::parseDateTime(const DateTime& dateTime,
                             DateFormatOptions options) const
{ return parseDateTime(dateTime,
                       Locale::LongDate,
                       Locale::HoursMinutes,
                       options); }

//----------------------------------------------------------------------------//

String Locale::name() const
{ return _lang + "_" + _country; }

String Locale::lang() const
{ return _lang; }
