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
 * @file Types/IpAddr.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-31
 */

#ifndef _TYPES_IPADDR_H_
#define	_TYPES_IPADDR_H_

#include "Types/String.h"
#include "Types/ByteArray.h"

/**
 * @class IpAddr Types/IpAddr.h <IpAddr>
 * @brief An IPv4/6 address
 * @note This class is user-safe
 */
class IpAddr
{
public:
	/**
	 * @brief Constructs a null IP address
	 */
	IpAddr();

	/**
	 * @brief Constructs an IPv4 from string
	 * @param ip The IPv4 address in dot-decimal notation (e.g. "192.168.0.50")
	 */
	IpAddr(const String& ip);

	/**
	 * @brief Get the IP address as string in dot-decimal notation
	 */
	String toString() const;

	/**
	 * @brief Get the IP address as 32 bits integer
	 */
	uint32_t toUInt32() const;

	bool isNull() const;

	/**
	 * @brief Defines equality operator
	 * @param ip The address to test equality
	 */
	bool operator==(const IpAddr& ip) const;

	/**
	 * @brief Defines non-equality operator
	 * @param ip The address to test non-equality
	 */
	bool operator!=(const IpAddr& ip) const;

	/**
	 * @brief Get the IP address as string in dot-decimal notation
	 */
	operator String() const;

private:
	bool _isNull;

	/**
	 * @brief The IP address as string notation
	 */
	String _strIp;

	/**
	 * @brief The IP address in binary
	 */
	//ByteArray _ip;

	uint32_t _intIp;
};

#endif // !_TYPES_IPADDR_H_
