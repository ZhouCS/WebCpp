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
 * @file Types/IpAddr.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-31
 */

#include "Types/IpAddr.h"
#include "Types/StringList.h"

#include "Exceptions/Types.h"

IpAddr::IpAddr()
{
	_isNull = true;
	_intIp = 0;
}

IpAddr::IpAddr(const String& ip)
{
	_isNull = false;
	_intIp = 0;

	StringList parts = ip.split(".");
	if (parts.count() != 4)
		throw Exceptions::BadIpAddr(ip);

	for(int i = 0; i < 4; i++)
	{
		int p;

		try
		{ p = parts[i].toInt(); }
		catch(const Exceptions::CannotConvertToInt&)
		{ throw Exceptions::BadIpAddr(ip); }

		if (p < 0 || p > 255)
			throw Exceptions::BadIpAddr(ip);

		_intIp += p << (3 - i) * 8;
	}

	_strIp = ip;
}

String IpAddr::toString() const
{ return _strIp; }

uint32_t IpAddr::toUInt32() const
{ return _intIp; }

bool IpAddr::isNull() const
{ return _isNull; }

bool IpAddr::operator==(const IpAddr& ip) const
{ return ip._intIp == _intIp; }

bool IpAddr::operator!=(const IpAddr& ip) const
{ return !operator==(ip); }

IpAddr::operator String() const
{ return _strIp; }
