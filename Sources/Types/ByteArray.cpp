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
 * @file Types/ByteArray.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-20
 */

#include "Types/ByteArray.h"
#include "Types/String.h"

#include <cmath>
#include <iostream>

ByteArray::ByteArray()
{}

ByteArray::ByteArray(const char* datas, int size)
{
	assign(datas, size);
}

ByteArray::ByteArray(const char* datas)
{
	assign(datas);
}

ByteArray::ByteArray(const String& str)
{
	assign(str.toCString(), str.size());
}


void ByteArray::append(const char* datas, int size)
{
	std::string str;
	str.assign(datas, size);
	*this += str;
}


String ByteArray::toHex() const
{
	const char* hexDigits = "0123456789abcdef";
	int s = size();
	String r;
	r.reserve(s * 2 + 1);

	for(int i = 0; i < s; i++)
	{
		r += hexDigits[(at(i) & 0xf0) >> 4];
		r += hexDigits[at(i) & 0x0f];
	}
	return r;
}

String ByteArray::toBase64() const
{
	const char* base64Digits = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvw"
	                           "xyz0123456789+/";
	String r;
	r.reserve(ceil(size() * 8.0 / 6.0) + 1);

	int s = size(), i;
	for (i = 0; i < s; i += 3)
	{
		if (i + 3 > s)
			break;

		r += base64Digits[(at(i) & 0xfc) >> 2];
		r += base64Digits[((at(i) & 0x03) << 4) + ((at(i + 1) & 0xf0) >> 4)];
		r += base64Digits[((at(i + 1) & 0x0f) << 2) + ((at(i + 2) & 0xc0) >> 6)];
		r += base64Digits[at(i + 2) & 0x3f];
	}

	float d = ceil(size() * 8.0 / 6.0) - (size() * 8.0 / 6.0);
	if (d > 0.6)
	{
		r += base64Digits[(at(i) & 0xfc) >> 2];
		r += base64Digits[(at(i) & 0x03) << 4];
		r += "==";
	}
	else if (d > 0.3)
	{
		r += base64Digits[(at(i) & 0xfc) >> 2];
		r += base64Digits[((at(i) & 0x03) << 4) + ((at(i + 1) & 0xf0) >> 4)];
		r += base64Digits[(at(i + 1) & 0x0f) << 2];
		r += "=";
	}

	return r;
}

String ByteArray::toString() const
{ return String(*this); }


ByteArray ByteArray::fromHex(const String& hex)
{
	const int s = hex.size() / 2;
	char* r = new char[s];

	for(int i = 0; i < s; i++)
		r[i] = ((hex[i * 2] < 0x3a
		         ? hex[i * 2] - 0x30
		         : hex[i * 2] - 0x61 + 0x0a) << 4)
		       + (hex[i*2+1] < 0x3a
		         ? hex[i*2+1] - 0x30
		         : hex[i*2+1] - 0x61 + 0x0a);

	return ByteArray(r, s);
}

ByteArray ByteArray::fromBase64(const String& base64)
{
	int s = ceil(base64.size() * 6.0 / 8.0);
	int l = base64.size();
	int j = 0, padding = 0;
	char d1, d2, d3, d4;

	if (base64[l-2] == '=')
		padding = 2;
	else if (base64[l-1] == '=')
		padding = 1;

	s -= padding;
	char* r = new char[s];

	for (int i = 0; i < l; i += 4)
	{
		d1 = _base64DigitValue(base64[i]);
		d2 = _base64DigitValue(base64[i + 1]);
		d3 = _base64DigitValue(base64[i + 2]);
		d4 = _base64DigitValue(base64[i + 3]);

		r[j] = (d1 << 2) + ((d2 & 0x30) >> 4);
		if (i < l - 3 || padding == 0)
		{
			r[j + 1] = ((d2 & 0x0f) << 4) + ((d3 & 0x3c) >> 2);
			r[j + 2] = ((d3 & 0x03) << 6) + d4;
		}
		else if (i < l - 3 || padding == 1)
			r[j + 1] = ((d2 & 0x0f) << 4) + ((d3 & 0x3c) >> 2);

		j += 3;
	}

	return ByteArray(r, s);
}
char ByteArray::_base64DigitValue(char ch)
{
	if (ch == '+')
		return 62;
	else if (ch == '/')
		return 63;
	else if (ch < 0x3a)
		return ch + 4;
	else if (ch < 0x5b)
		return ch - 0x41;
	return ch - 71;
}

const char* ByteArray::data() const
{ return std::string::data(); }

char ByteArray::at(int index) const
{ return std::string::operator[](index); }

char ByteArray::operator[](int index) const
{ return std::string::operator[](index); }

ByteArray::operator const char*() const
{ return data(); }
