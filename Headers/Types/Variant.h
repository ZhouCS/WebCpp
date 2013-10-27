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
 * @file Types/Variant.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#ifndef _WPP_TYPES_VARIANT_H_
#define _WPP_TYPES_VARIANT_H_

#include <stdint.h>

#include "Types/String.h"
#include "Types/DateTime.h"
#include "Types/List.h"
#include "Types/Map.h"

class Locale;

/**
 * @class Variant Types/Variant.h <Variant>
 * @brief An abstract data type
 */
class Variant
{
public:
	enum class Type
	{
		None,
		Integer,
		UInt64,
		Float,
		Bool,
		String,
		Date,
		Time,
		DateTime,
		List,
		Map
	};

	Variant();
	Variant(const Variant& other);
	Variant(int n);
	Variant(uint64_t n);
	Variant(float n);
	Variant(bool b);
	Variant(const char* str);
	Variant(const String& str);
	Variant(const Date& date);
	Variant(const Time& time);
	Variant(const DateTime& dateTime);
	Variant(const List<Variant>& list);
	Variant(const Map<String, Variant>& map);

	~Variant();

	/**
	 * @brief Converts the data into a string object
	 * @return The converted data to string
	 */
	String toString() const;

	/**
	 * @brief Returns a HTML rendering of the value
	 * @return A HTML rendering of the value
	 */
	String htmlRender(Locale* locale) const;

	void setRaw(bool raw = true);

	/**
	 * @brief Dumps the data for debugging
	 * @return The dumped data string
	 */
	String dump() const;

	int      toInt() const;
	uint64_t toUInt64() const;
	float    toFloat() const;
	bool     toBool() const;
	const List<Variant>& toList() const;
	const Map<String, Variant>& toMap() const;

	/**
	 * @brief Returns the data type
	 * @return The data type
	 */
	Type type() const;

	/**
	 * @brief Returns the data type as string (e.g. "DateTime")
	 * @return The data type as string
	 */
	String typeString() const;

	Variant& operator=(const Variant& other);

private:
	/**
	 * @brief The type
	 */
	Type _type;

	bool _raw;

	union
	{
		int      _int;
		uint64_t _uint64;
		float    _float;
		bool     _bool;
		void*    _ptr;
	};
};

#endif // !_WPP_TYPES_VARIANT_H_
