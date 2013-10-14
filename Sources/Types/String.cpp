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
 * @file Types/String.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#include "Types/String.h"
#include "Types/StringList.h"
#include "Types/Map.h"
#include "Types/ByteArray.h"

#include "Libs/Regex.h"
#include "Sites/Site.h"
#include "System.h"
#include "DB/AbstractDbConnection.h"
#include "Exceptions/Types.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>

#include <boost/algorithm/string.hpp>

String::String()
  : std::string()
{ _isNull = true; }

String::String(const std::string& str)
  : std::string(str),
    _isNull(false)
{}

String::String(const char* str)
  : std::string(str),
    _isNull(false)
{}

String::String(const ByteArray& ba)
  : std::string(),
    _isNull(false)
{
	if (ba.at(ba.size() - 1) == '\0')
		assign(ba.data(), ba.size());
	std::string str(ba.data(), ba.size());
	str[ba.size()] = '\0';
	assign(str);
}

String::String(char ch)
  : std::string(),
    _isNull(false)
{
	append(1, ch);
}

String::String(int n)
  : std::string(),
    _isNull(false)
{
	std::stringstream ss;
	ss << n;
	*this = ss.str();
}

String::String(unsigned int n)
  : std::string(),
    _isNull(false)
{
	std::stringstream ss;
	ss << n;
	*this = ss.str();
}

String::String(long unsigned int n)
  : std::string(),
    _isNull(false)
{
	std::stringstream ss;
	ss << n;
	*this = ss.str();
}

String::String(double n)
  : std::string(),
    _isNull(false)
{
	std::stringstream ss;
	ss << n;
	*this = ss.str();
}


int String::length() const
{
	const char* s = c_str();
	int len = 0;

	while (*s != '\0')
		len += (*(s++) & 0xc0) != 0x80;

	return len;
}

int String::size() const
{ return std::string::size(); }

void String::reserve(int size)
{ std::string::reserve(size); }


char String::charAt(int index) const
{ return std::string::operator[](index); }


bool String::contains(const String& str) const
{ return find(str) != std::string::npos; }

bool String::in(const StringList& list) const
{ return list.contains(*this); }

bool String::startsWith(const String& str) const
{ return indexOf(str) == 0; }

bool String::endsWith(const String& str) const
{
	size_t pos = std::string::rfind(str);
	return pos != std::string::npos && pos + (unsigned int)str.size()
	                                   == (unsigned int)size();
}

int String::indexOf(const String& str, int from) const
{
	size_t pos = find(str, from);
	if (pos == std::string::npos)
		return -1;
	return pos;
}

int String::reversedIndexOf(const String& str, int from) const
{
	size_t pos = rfind(str, from);
	if (pos == std::string::npos)
		return -1;
	return pos;
}

int String::count(const String& str) const
{
	int n = 0, pos = -str.size();
	while ((pos = indexOf(str, pos+str.size())) != -1)
		n++;
	return n;
}

bool String::match(Regex regex) const
{ return regex.exec(*this); }

bool String::match(const String& pattern) const
{ return match(Regex(pattern)); }

String String::substr(int start, int n) const
{ return std::string::substr(start, n == -1 ? std::string::npos : n); }

String String::left(int n) const
{ return substr(0, n); }

String String::right(int n) const
{ return substr(size() - n); }

String String::mid(int start, int end) const
{ return substr(start, end - start + 1); }

String String::midToRight(int left, int right) const
{ return substr(left, right - left); }

String String::removeLeft(int n) const
{ return substr(n); }

String String::removeRight(int n) const
{ return substr(0, size() - n); }

String String::tokenLeft(const String& token) const
{ return substr(0, indexOf(token)); }

String String::tokenRight(const String& token) const
{ return substr(indexOf(token) + token.size()); }

String String::section(const String& delimiter, int start, int end) const
{
	String output;
	size_t pos = 0, oldPos = 0;
	int i = 0, j = 0, nSections = 1, delimLen = delimiter.size();
	bool found = false;

	pos = -delimLen;
	while ((pos = find(delimiter, pos + delimLen)) != std::string::npos)
		nSections++;
	pos = 0;

	if (start < 0)
		start = start + nSections;
	if (end < 0)
		end = end + nSections;

	if (start >= nSections)
		start = nSections - 1;
	if (end >= nSections)
		end = nSections - 1;

	if (start < 0)
		start = 0;
	if (end < 0)
		end = 0;

	if (start > end)
	{
		int tmp = start;
		start = end;
		end = tmp;
	}

	int nSelect = end - start + 1;

	while (true)
	{
		pos = find(delimiter, oldPos);
		found = true;

		String section;
		if (pos == std::string::npos)
			section = substr(oldPos);
		else
			section = substr(oldPos, pos - oldPos);

		if (i >= start && i <= end)
		{
			output += section;

			j++;
			if (j < nSelect)
				output += delimiter;
			else
				break;
		}

		oldPos = pos + delimLen;
		i++;

		if (pos == std::string::npos)
			break;
	}

	if (found)
		return output;
	return *this;
}

StringList String::split(const String& delimiter) const
{
	StringList list;
	int delimLen = delimiter.size();
	size_t oldPos = 0;

	while (size_t pos = find(delimiter, oldPos))
	{
		if (pos == std::string::npos)
			list.append(substr(oldPos));
		else
			list.append(substr(oldPos, pos - oldPos));
		oldPos = pos + delimLen;

		if (pos == std::string::npos)
			break;
	}

	return list;
}


String String::replace(int start, int end, const String& dest) const
{
	String r = *this;
	r.std::string::replace(start, end - start + 1, dest);
	return r;
}

String String::replace(const String& source, const String& dest) const
{
	String r = *this;
	size_t pos = 0, oldPos = 0;

	while ((pos = r.find(source, oldPos)) != std::string::npos)
	{
		r.std::string::replace(pos, source.size(), dest);
		oldPos = pos + (dest.size() - source.size() + 1);
	}

	return r;
}

String String::replace(Regex regex, const String& dest) const
{
	String r = dest;
	regex.exec(*this);

	List<Pair<int, int>> captured = regex.capturedIndexes();
	for (int i = 0; i < captured.count(); i++)
		r = r.replace(String("\\") + i,
		              (*this).substr(captured[i].first(), captured[i].second()));

	return r;
}


String String::insert(int pos, const String& str) const
{
	String r = *this;
	r.std::string::insert(pos, str);
	return r;
}


Map<String, String> String::parseQueryString() const
{
	Map<String, String> map;

	StringList args = split("&");
	for (int j = 0; j < args.count(); j++)
	{
		String key, value;
		if (args[j].contains("="))
		{
			key = args[j].tokenLeft("=");
			value = args[j].tokenRight("=");
		}
		else
			key = args[j];
		map[key] = value;
	}

	return map;
}


String String::secure() const
{
	String str = *this;
	int i = 0, size = 0, j = 0, code;

	while (str[i] != '\0')
	{
		if ((str[i] & 0xC0) == 0xC0)
		{
			size = 0;
			if ((str[i] & 0xE0) == 0xC0)      size = 2;
			else if ((str[i] & 0xF0) == 0xE0) size = 3;
			else if ((str[i] & 0xF8) == 0xF0) size = 4;
			else if ((str[i] & 0xFC) == 0xF8) size = 5;
			else if ((str[i] & 0xFE) == 0xFC) size = 6;
			else
				str = str.replace(i, i, "");
			if (size > 0)
			{
				code = (str[i] & (0xFF >> (size + 1))) << ((size - 1) * 6);
				i++;
				j = size - 2;
				while (str[i] != '\0' && j >= 0)
				{
					if ((str[i] & 0xC0) != 0x80)
					{
						str = str.replace(i - (size - j - 1), i - 1, "");
						break;
					}
					code |= (str[i] & 0x3F) << (j * 6);
					i++;
					j--;
				}
				if (str[i] == '\0' && j >= 0)
				{
					str = str.replace(i - (size - j - 1), i - 1, "");
					break;
				}
				else if (j < 0 && (code < ' ' || code == 0x7F))
					str = str.replace(i - size, i - 1, "");
				else if (j < 0)
				{
					int normSize;
					if (code < 0x80)           normSize = 1;
					else if (code < 0x800)     normSize = 2;
					else if (code < 0x10000)   normSize = 3;
					else if (code < 0x200000)  normSize = 4;
					else if (code < 0x4000000) normSize = 5;
					else                       normSize = 6;
					if (size > normSize)
						str = str.replace(i - size, i - 1,
						                  String::fromUnicode(code));
				}
			}
		}
		else if ((str[i] < ' ' || str[i] > '~') && str[i] != '\t' && str[i] != '\n')
			str = str.replace(i, i, "");
		else
			i++;
	}
	return str;
}

String String::htmlEscape() const
{
	return replace("&",  "&amp;")
	       .replace("<",  "&lt;")
	       .replace(">",  "&gt;")
	       .replace("\"", "&quot;");
}

String String::urlEscape() const
{
	return *this;
}

String String::urlUnescape() const
{
	String r = replace("+", " ");
	size_t pos = -1;

	while ((pos = r.find('%', pos + 1)) != std::string::npos)
	{
		String ch = r.substr(pos + 1, 2);
		if (ch.length() < 2)
			continue;

		char val = (char)ch.toInt(16);
		const char str[2] = {val, '\0'};
		r.std::string::replace(pos, 3, (const char*)str);
	}
	return r;
}

String String::sqlEscape(AbstractDbConnection* dbConnection) const
{
	if (dbConnection == nullptr)
		dbConnection = System::get()->site()->dbConnection();
	return dbConnection->escapeString(*this);
}


String String::trim() const
{
	int start = 0, end = size() - 1;

	while (at(start) == ' ' || at(start) == '\t' || at(start) == '\n')
		start++;
	if (end > 0)
	{
		while (end >= 0 && (at(end) == ' ' || at(end) == '\t' || at(end) == '\n'))
			end--;
	}
	return mid(start, end + 1);
}


String String::format(const StringList& args) const
{
	String r = *this;

	for (int i = 0; i < args.count(); i++)
		r = r.replace(String("%") + (i + 1), args[i]);
	return r;
}

String String::format(const String& arg1) const
{ return format(StringList({arg1})); }

String String::format(const String& arg1, const String& arg2) const

{ return format({arg1, arg2}); }
String String::format(const String& arg1,
                      const String& arg2,
                      const String& arg3) const
{ return format({arg1, arg2, arg3}); }


int String::toInt(int base) const
{
	std::istringstream i(*this);
	int n;

	i >> std::setbase(base);
	if (!(i >> n))
		throw Exceptions::CannotConvertToInt(*this);
	return n;
}

uint64_t String::toUInt64(int base) const
{
	std::istringstream i(*this);
	uint64_t n;

	i >> std::setbase(base);
	if (!(i >> n))
		throw Exceptions::CannotConvertToInt(*this);
	return n;
}

float String::toFloat() const
{
	std::istringstream i(*this);
	float n;

	if (!(i >> n))
		throw Exceptions::CannotConvertToFloat(*this);
	return n;
}

String String::toUpper() const
{
	std::wstring wstr = toStdWString();
	const wchar_t* src = wstr.c_str();
	int size = wstr.size();
	wchar_t* str = new wchar_t[size + 1];

	for (int i = 0; i < size; i++)
		str[i] = src[i];
	str[size] = '\0';

	std::use_facet<std::ctype<wchar_t>>(std::locale()).toupper(str, str + size);

	std::wstring out(str);
	delete[] str;

	return String(stdWStringToStdString(out));
}

String String::toAsciiUpper() const
{
	const char* src = c_str();
	int sz = size();
	char* str = new char[sz + 1];

	for (int i = 0; i < sz; i++)
	{
		if (src[i] >= 'a' && src[i] <= 'z')
			str[i] = src[i] - 32;
		else
			str[i] = src[i];
	}
	str[sz] = '\0';
	return String(str);
}

String String::upperFirst() const
{
	if (isEmpty())
		return String();
	return String(charAt(0)).toUpper() + removeLeft(1);
}

String String::upperAsciiFirst() const
{
	if (isEmpty())
		return String();
	return String(charAt(0)).toAsciiUpper() + removeLeft(1);
}

String String::toLower() const
{
	std::wstring wstr = toStdWString();
	const wchar_t* src = wstr.c_str();
	int size = wstr.size();
	wchar_t* str = new wchar_t[size + 1];

	for (int i = 0; i < size; i++)
		str[i] = src[i];
	str[size] = '\0';

	std::use_facet<std::ctype<wchar_t>>(std::locale()).tolower(str, str + size);

	std::wstring out(str);
	delete[] str;

	return String(stdWStringToStdString(out));
}

String String::toAsciiLower() const
{
	const char* src = c_str();
	int sz = size();
	char* str = new char[sz + 1];

	for (int i = 0; i < sz; i++)
	{
		if (src[i] >= 'A' && src[i] <= 'Z')
			str[i] = src[i] + 32;
		else
			str[i] = src[i];
	}

	str[sz] = '\0';
	String r(str);
	delete[] str;
	return r;

	//return String(boost::to_lower_copy(toStdString()));

	/*const char* src = c_str();
	int sz = size();
	char* str = new char[sz+1];
	for(int i = 0; i < sz; i++)
		str[i] = src[i];
	str[sz] = '\0';

	std::use_facet<std::ctype<char>>(std::locale()).tolower(str, str + size());

	std::string r(str);
	delete[] str;
	return String(r);*/
}


String& String::operator=(const String& str)
{
	std::string::operator=((const std::string&)str);
	_isNull = false;
	return *this;
}

char String::operator[](int index) const
{ return std::string::operator[](index); }

String String::operator+(const String& str) const
{ return (*this).toStdString() + str.toStdString(); }

String String::operator+(const char* str) const
{ return *this + String(str); }

String String::operator+(int n) const
{ return *this + String(n); }

String String::operator+(char ch) const
{ return *this + String(ch); }

String String::operator+=(const String& str)
{ return (*this = *this + str); }

String String::operator+=(char ch)
{ return (*this = *this + String(ch)); }


bool String::operator==(const String& str) const
{ return compare(str) == 0; }

bool String::operator==(const char* str) const
{ return compare(str) == 0; }

bool String::operator!=(const String& str) const
{ return compare(str) != 0; }

bool String::operator!=(const char* str) const
{ return compare(str) != 0; }

String::operator const char*() const
{ return toCString(); }

String::operator int() const
{ return toInt(); }

String::operator float() const
{ return toFloat(); }

String::operator bool() const
{ return *this == "1" || *this == "true" || toAsciiLower() == "true"; }

std::size_t String::hash() const
{ return std::hash<std::string>()(toStdString()); }

String::operator std::string() const
{ return (std::string)(*this); }

//----------------------------------------------------------------------------//

const char* String::toCString() const
{ return toStdString().c_str(); }

std::string& String::toStdString()
{ return static_cast<std::string&>(*this); }

std::string String::toStdString() const
{ return static_cast<std::string>(*this); }

std::wstring String::toStdWString() const
{
	typedef std::codecvt<wchar_t, char, std::mbstate_t> facet_type;
	std::string s = toStdString();

	std::mbstate_t state = std::mbstate_t();
	std::vector<wchar_t> buffer(s.size());

	const char* endInPtr = nullptr;
	wchar_t* endOutPtr = nullptr;

	std::use_facet<facet_type>(std::locale()).in(
		state, s.data(), s.data() + s.length(), endInPtr,
		&buffer.front(), &buffer.front() + buffer.size(), endOutPtr
	);

	return std::wstring(&buffer.front(), endOutPtr);
}

std::string String::stdWStringToStdString(const std::wstring& wstr)
{
	/*typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
	const converter_type& converter = std::use_facet<converter_type>(std::locale());
	std::vector<char> to(wstr.length() * converter.max_length());
	std::mbstate_t state;
	const wchar_t* from_next;
	char* to_next;
	converter.out(state, wstr.data(), wstr.data() + wstr.length(), from_next, &to[0], &to[0] + to.size(), to_next);
	return String(std::string(&to[0], to_next));*/
	return std::string(wstr.begin(), wstr.end());
}

String String::fromNumber(uint64_t n, int base)
{
	std::stringstream ss;

	ss.imbue(std::locale("C"));
	ss << std::setbase(base) << n;
	return ss.str();
}

String String::fromUnicode(int code)
{
	int  bytesCount;
	if (code < 0x80)
		return String(static_cast<char>(code & 0x7F));
	else if (code < 0x800)     bytesCount = 2;
	else if (code < 0x10000)   bytesCount = 3;
	else if (code < 0x200000)  bytesCount = 4;
	else if (code < 0x4000000) bytesCount = 5;
	else                       bytesCount = 6;

	char bytes[6];
	bytes[0] = (0xFF << (8 - bytesCount))
	           | ((code >> ((bytesCount - 1) * 6)) & (0xFF >> bytesCount));
	int i = 1;
	while (i < bytesCount)
	{
		bytes[i] = 0x80 | ((code >> ((bytesCount - i - 1) * 6)) & 0x3F);
		i++;
	}
	return ByteArray(bytes, bytesCount);
}

bool String::isEmpty() const
{ return _isNull || size() == 0; }

bool String::isNull() const
{ return _isNull; }

//----------------------------------------------------------------------------//

std::ostream& operator<<(std::ostream& stream, const String& string)
{ return stream << string.toStdString(); }

std::istream& operator>>(std::istream& stream, String& string)
{ return stream >> static_cast<std::string&>(string); }

bool operator<(const String& l, const String& r)
{ return l.compare(r.toStdString()) < 0; }

bool operator>(const String& l, const String& r)
{ return l.compare(r.toStdString()) > 0; }

String operator+(const char* str1, const String& str2)
{ return String(str1) + str2; }

String operator%(const String& pattern, const StringList& args)
{ return pattern.format(args); }

String operator%(const String& pattern, const String& arg1)
{ return pattern.format(arg1); }
