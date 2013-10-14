/********************************************************************************
 * Copyright © 2011 Kévin Lesénéchal <kevin@lesenechal.org>                     *
 *                                                                              *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.                   *
 *                                                                              *
 * WebCpp is free software: you can redistribute it and/or modify it     *
 * it under the terms of the GNU Affero General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU Affero General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the GNU Affero General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 ********************************************************************************/

/**
 * @file Libs/Crypt/Hash.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-20
 */

#ifndef _LIBS_CRYPT_HASH_H_
#define _LIBS_CRYPT_HASH_H_

#include "Libs/Crypt/Sha2.h"

class ByteArray;
class String;

/**
 * @class Hash Libs/Hash.h <Hash>
 * @brief A cryptographic hash calculator
 */
class Hash
{
public:
	/**
	 * @brief Algorithms list
	 */
	enum Algorithm{/*Md4, Md5, Sha1,*/ Sha256, Sha384, Sha512};

	/**
	 * @brief Constructs a hash calculator
	 * @param algo The algorithm to hash datas
	 */
	Hash(Algorithm algo = Sha512);

	/**
	 * @brief Appends datas to the hash calculator
	 * @param datas The datas to append
	 */
	void append(const ByteArray& datas);

	/**
	 * @brief Computes the hash and returns it
	 * @return The computed hash
	 */
	ByteArray result();

	/**
	 * @brief Easily hash short datas
	 * @param datas The datas to hash
	 * @param algo The algorithm to use
	 * @return The hashed datas
	 */
	static ByteArray hash(const ByteArray& datas, Algorithm algo = Sha512);

private:
	Algorithm _algo;

	SHA256_CTX _contextSha256;
	SHA384_CTX _contextSha384;
	SHA512_CTX _contextSha512;
};

#endif // !_LIBS_CRYPT_HASH_H_
