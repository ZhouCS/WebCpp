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
 * @file MysqlResult.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-28
 */

#ifndef _MYSQLRESULT_H_
#define	_MYSQLRESULT_H_

#include <DB/AbstractDbResult.h>

#include <mysql/mysql.h>

/**
 * @brief A MySQL query result
 */
class MysqlResult : public AbstractDbResult
{
public:
	/**
	 * @brief Constructs a MySQL result
	 * @param result The MySQL result
	 * @param executionTime The query execution time
	 * @param affectedRows The number of rows affected by the query
	 */
	MysqlResult(MYSQL_RES* result, double executionTime, int affectedRows = -1);
	
	/**
	 * @brief Destructs the MySQL result
	 */
	virtual ~MysqlResult();
	
	/**
	 * @brief Fetch to next row
	 * @return The fetched row
	 */
	virtual AbstractDbRow* fetch();
	
	/**
	 * @brief Implements the getter to know if the result is at the end
	 * @return true if the result has more rows, otherwise false
	 */
	virtual bool hasNext() const;

protected:
	/**
	 * @brief Implements how to get the column count
	 */
	virtual int getColumnCount() const;
	
	/**
	 * @brief Implements how to get the column names list
	 */
	virtual StringList getColumnNames() const;

private:
	/**
	 * @brief The MySQL result
	 */
	MYSQL_RES* _result;
	
	/**
	 * @brief Defines whenever the result has more rows
	 */
	bool _hasNext; // Ugly...
};

#endif // !_MYSQLRESULT_H_
