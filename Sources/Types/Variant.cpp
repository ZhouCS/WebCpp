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
 * @file Types/Variant.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#include "Types/Variant.h"

#include "Libs/Locale/Locale.h"

Variant::Variant()
  : _type(Type::None),
    _raw(false)
{}

Variant::Variant(const Variant& other)
  : _type(other._type),
    _raw(other._raw)
{
	if (_type == Type::Integer)
		_int = other._int;
	else if (_type == Type::UInt64)
		_uint64 = other._uint64;
	else if (_type == Type::Float)
		_float = other._float;
	else if (_type == Type::Bool)
		_bool = other._bool;
	else if (_type == Type::String)
		_ptr = new String(*(reinterpret_cast<String*>(other._ptr)));
	else if (_type == Type::Date)
		_ptr = new Date(*(reinterpret_cast<Date*>(other._ptr)));
	else if (_type == Type::Time)
		_ptr = new Time(*(reinterpret_cast<Time*>(other._ptr)));
	else if (_type == Type::DateTime)
		_ptr = new DateTime(*(reinterpret_cast<DateTime*>(other._ptr)));
	else if (_type == Type::List)
		_ptr = new List<Variant>(*(reinterpret_cast<List<Variant>*>(other._ptr)));
	else if (_type == Type::Map)
		_ptr = new Map<String, Variant>(*(reinterpret_cast<Map<String, Variant>*>(
		                                    other._ptr)));
}

Variant::Variant(int n)
  : _type(Type::Integer),
    _raw(false),
    _int(n)
{}

Variant::Variant(uint64_t n)
  : _type(Type::UInt64),
    _raw(false),
    _uint64(n)
{}

Variant::Variant(float n)
  : _type(Type::Float),
    _raw(false),
    _float(n)
{}

Variant::Variant(bool b)
  : _type(Type::Bool),
    _raw(false),
    _bool(b)
{}

Variant::Variant(const char* str)
  : _type(Type::String),
    _raw(false),
    _ptr(new String(str))
{}

Variant::Variant(const String& str)
  : _type(Type::String),
    _raw(false),
    _ptr(new String(str))
{}

Variant::Variant(const Date& date)
  : _type(Type::Date),
    _raw(false),
    _ptr(new Date(date))
{}

Variant::Variant(const Time& time)
  : _type(Type::Time),
    _raw(false),
    _ptr(new Time(time))
{}

Variant::Variant(const DateTime& dateTime)
  : _type(Type::DateTime),
    _raw(false),
    _ptr(new DateTime(dateTime))
{}

Variant::Variant(const List<Variant>& list)
  : _type(Type::List),
    _raw(false),
    _ptr(new List<Variant>(list))
{}

Variant::Variant(const Map<String, Variant>& map)
  : _type(Type::Map),
    _raw(false),
    _ptr(new Map<String, Variant>(map))
{}

Variant::~Variant()
{
	if (_type == Type::String)
		delete reinterpret_cast<String*>(_ptr);
	else if (_type == Type::Date)
		delete reinterpret_cast<Date*>(_ptr);
	else if (_type == Type::Time)
		delete reinterpret_cast<Time*>(_ptr);
	else if (_type == Type::DateTime)
		delete reinterpret_cast<DateTime*>(_ptr);
	else if (_type == Type::List)
		delete reinterpret_cast<List<Variant>*>(_ptr);
	else if (_type == Type::Map)
		delete reinterpret_cast<Map<String, Variant>*>(_ptr);
}

//----------------------------------------------------------------------------//

String Variant::toString() const
{
	if (_type == Type::Integer)
		return String(_int);
	else if (_type == Type::Float)
		return String(_float);
	else if (_type == Type::Bool)
		return _bool ? "true" : "false";
	else if (_type == Type::String)
		return *(reinterpret_cast<String*>(_ptr));
	return String();
}

String Variant::htmlRender(Locale* locale) const
{
	if (_raw)
		return toString();
	if (_type == Type::String)
		return reinterpret_cast<String*>(_ptr)->htmlEscape();
	else if (_type == Type::Integer)
		return locale->parseNumber(static_cast<long>(_int));
	else if (_type == Type::Float)
		return locale->parseNumber(_float);
	else if (_type == Type::DateTime)
		return locale->parseDateTime(*reinterpret_cast<DateTime*>(_ptr));
	else if (_type == Type::Bool)
		return _bool ? "Oui" : "Non";
	else
		throw 42; // FIX ME
}

String Variant::dump() const
{ return toString(); }

int Variant::toInt() const
{
	if (_type == Type::Integer)
		return _int;
	else if (_type == Type::UInt64)
		return static_cast<int>(_uint64);
	else if (_type == Type::Float)
		return static_cast<int>(_float);
	else if (_type == Type::Bool)
		return static_cast<int>(_bool);
	else if (_type == Type::String)
		return reinterpret_cast<String*>(_ptr)->toInt();
	else
		throw 42; // FIX ME
}

uint64_t Variant::toUInt64() const
{
	if (_type == Type::UInt64)
		return _uint64;
	else if (_type == Type::Integer)
		return static_cast<uint64_t>(_int);
	else if (_type == Type::Float)
		return static_cast<uint64_t>(_float);
	else if (_type == Type::Bool)
		return static_cast<uint64_t>(_bool);
	else if (_type == Type::String)
		return reinterpret_cast<String*>(_ptr)->toUInt64();
	else
		throw 42; // FIX ME
}

float Variant::toFloat() const
{
	if (_type == Type::Integer)
		return static_cast<float>(_int);
	else if (_type == Type::UInt64)
		return static_cast<float>(_uint64);
	else if (_type == Type::Float)
		return static_cast<float>(_float);
	else if (_type == Type::Bool)
		return static_cast<float>(_bool);
	else if (_type == Type::String)
		return reinterpret_cast<String*>(_ptr)->toFloat();
	else
		throw 42; // FIX ME
}

bool Variant::toBool() const
{
	if (_type == Type::Bool)
		return _bool;
	else if (_type == Type::Integer)
		return static_cast<bool>(_int);
	else if (_type == Type::UInt64)
		return static_cast<bool>(_uint64);
	else if (_type == Type::Float)
		return static_cast<bool>(_float);
	else
		throw 42; // FIX ME
}

const List<Variant>& Variant::toList() const
{
	if (_type != Type::List)
		throw 42; // FIX ME
	return *reinterpret_cast<List<Variant>*>(_ptr);
}

const Map<String, Variant>& Variant::toMap() const
{
	if (_type != Type::Map)
		throw 42; // FIX ME
	return *reinterpret_cast<Map<String, Variant>*>(_ptr);
}

Variant& Variant::operator=(const Variant& other)
{
	_type = other._type;
	_raw = other._raw;
	if (_type == Type::Integer)
		_int = other._int;
	else if (_type == Type::UInt64)
		_uint64 = other._uint64;
	else if (_type == Type::Float)
		_float = other._float;
	else if (_type == Type::Bool)
		_bool = other._bool;
	else if (_type == Type::String)
		_ptr = new String(*(reinterpret_cast<String*>(other._ptr)));
	else if (_type == Type::Date)
		_ptr = new Date(*(reinterpret_cast<Date*>(other._ptr)));
	else if (_type == Type::Time)
		_ptr = new Time(*(reinterpret_cast<Time*>(other._ptr)));
	else if (_type == Type::DateTime)
		_ptr = new DateTime(*(reinterpret_cast<DateTime*>(other._ptr)));
	else if (_type == Type::List)
		_ptr = new List<Variant>(*(reinterpret_cast<List<Variant>*>(other._ptr)));
	else if (_type == Type::Map)
		_ptr = new Map<String, Variant>(*(reinterpret_cast<Map<String, Variant>*>(
		                                    other._ptr)));
	return *this;
}

//----------------------------------------------------------------------------//

Variant::Type Variant::type() const
{ return _type; }

void Variant::setRaw(bool raw)
{ _raw = raw; }

String Variant::typeString() const
{
	static Map<int, String> types;
	static bool init = false;

	if (!init)
	{
		types[static_cast<int>(Type::Integer)] = "Integer";
		types[static_cast<int>(Type::UInt64)] = "UInt64";
		types[static_cast<int>(Type::Float)] = "Float";
		types[static_cast<int>(Type::Bool)] = "Bool";
		types[static_cast<int>(Type::String)] = "String";
		types[static_cast<int>(Type::Date)] = "Date";
		types[static_cast<int>(Type::Time)] = "Time";
		types[static_cast<int>(Type::DateTime)] = "DateTime";
		types[static_cast<int>(Type::List)] = "List";
		types[static_cast<int>(Type::Map)] = "Map";
		init = true;
	}
	return types[static_cast<int>(_type)];
}
