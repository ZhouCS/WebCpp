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
 * @file Libs/Crypt/Hash.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-20
 */

#include "Libs/Crypt/Hash.h"

#include "Types/ByteArray.h"

#include <iostream>

Hash::Hash(Algorithm algo)
{
	_algo = algo;

	if (_algo == Sha256)
		SHA256_Init(&_contextSha256);
	else if (_algo == Sha384)
		SHA384_Init(&_contextSha384);
	else if (_algo == Sha512)
		SHA512_Init(&_contextSha512);
}

void Hash::append(const ByteArray& datas)
{
	if (_algo == Sha256)
		SHA256_Update(&_contextSha256,
		              reinterpret_cast<const u_int8_t*>(datas.data()),
		              datas.size());
	else if (_algo == Sha384)
		SHA384_Update(&_contextSha384,
		              reinterpret_cast<const u_int8_t*>(datas.data()),
		              datas.size());
	else if (_algo == Sha512)
		SHA512_Update(&_contextSha512,
		              reinterpret_cast<const u_int8_t*>(datas.data()),
		              datas.size());
}

ByteArray Hash::result()
{
	u_int8_t* digest;
	int len = 0;

	if (_algo == Sha256)
	{
		digest = new u_int8_t[32];
		SHA512_Final(digest, &_contextSha512);
		len = 32;
	}
	else if (_algo == Sha384)
	{
		digest = new u_int8_t[48];
		SHA512_Final(digest, &_contextSha512);
		len = 48;
	}
	else if (_algo == Sha512)
	{
		digest = new u_int8_t[64];
		SHA512_Final(digest, &_contextSha512);
		len = 64;
	}
	else
		return ByteArray(); //TODO: throw an exception instead

	return ByteArray(reinterpret_cast<const char*>(digest), len);
}

ByteArray Hash::hash(const ByteArray& datas, Algorithm algo)
{
	Hash hash(algo);
	hash.append(datas);
	return hash.result();
}
