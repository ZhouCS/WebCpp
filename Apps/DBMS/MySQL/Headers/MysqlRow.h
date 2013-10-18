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
 * @file MysqlRow.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-28
 */

#ifndef _MYSQLROW_H_
#define	_MYSQLROW_H_

#include <DB/AbstractDbRow.h>

#include <mysql/mysql.h>

#include <cstdlib>

class MysqlResult;

/**
 * @brief A MySQL result row
 */
class MysqlRow : public AbstractDbRow
{
public:
	/**
	 * @brief Constructs a MySQL result row
	 * @param result The MySQL result
	 * @param row The MySQL row
	 */
	MysqlRow(const MysqlResult* result, MYSQL_ROW row);

private:
	/**
	 * @brief Implements how to get a value
	 * @param index The index of the column
	 * @return The value of the column at index @p index
	 */
	virtual String get(int index) const;

private:
	/**
	 * @brief The MySQL result
	 */
	MysqlResult* _result;
	
	/**
	 * @brief The MySQL row
	 */
	MYSQL_ROW _row;
};

#endif // !_MYSQLROW_H_
