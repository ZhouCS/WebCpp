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
 * @file Types/ByteArray.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-20
 */

#ifndef _WPP_TYPES_BYTEARRAY_H_
#define	_WPP_TYPES_BYTEARRAY_H_

#include "Types/String.h"

/**
 * @brief An array of bytes
 */
class ByteArray : private std::string
{
public:
	using std::string::size;

	ByteArray();

	/**
	 * @brief Constructs a byte array from a C char array
	 * @param datas The C char array
	 * @param size The size of the C char array
	 */
	ByteArray(const char* datas, int size);

	/**
	 * @brief Constructs a byte array from C-string
	 * @param str The C-string
	 * @warning The C-string must be NULL-terminated
	 */
	ByteArray(const char* str);

	/**
	 * @brief Constructs a byte array from a string
	 * @param str The source string
	 * @note The ending NULL character will not be included in the byte array
	 */
	ByteArray(const String& str);


	void append(const char* datas, int size);

	/**
	 * @brief Converts to the hexadecimal representation of the byte array
	 */
	String toHex() const;

	/**
	 * @brief Converts to the base 64 representation of the byte array
	 */
	String toBase64() const;

	/**
	 * @brief Converts to string
	 */
	String toString() const;


	/**
	 * @brief Create a byte array from a hexadecimal representation
	 * @param hex The hexadecimal representation as string
	 * @return The byte array
	 */
	static ByteArray fromHex(const String& hex);

	/**
	 * @brief Create a byte array from a base 64 representation
	 * @param base64 The base 64 representation as string
	 * @return The byte array
	 */
	static ByteArray fromBase64(const String& base64);


	/**
	 * @brief Get the datas in byte array as C-table
	 */
	const char* data() const;

	/**
	 * @brief Get a byte by index
	 * @param index The byte index
	 * @return The byte to the index @p index
	 */
	char at(int index) const;

	/**
	 * @brief Get a byte by index
	 * @param index The byte index
	 * @return The byte to the index @p index
	 */
	char operator[](int index) const;

	/**
	 * @brief Converts the byte array to C char array
	 */
	operator const char*() const;

private:
	/**
	 * @brief Get the binary value (on 6 bits) of the base 64 character @p ch
	 * @param The base 64 character
	 * @return Te binary value of @p ch
	 */
	static inline char _base64DigitValue(char ch);
};

#endif // !_WPP_TYPES_BYTEARRAY_H_
