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
 * @file DB/AbstractDbResult.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-27
 */

#ifndef _DB_ABSTRACTDBRESULT_H_
#define	_DB_ABSTRACTDBRESULT_H_

#include "Types/StringList.h"
#include "Types/Map.h"
#include "DB/AbstractDbRow.h"

class Chrono;
class AbstractDbRow;

/**
 * @class AbstractDbResult DB/AbstractDbResult.h <AbstractDbResult>
 * @brief An interface to a SQL result
 */
class AbstractDbResult
{
public:
	virtual ~AbstractDbResult()
	{ }

	/**
	 * @brief Fetch to next row
	 * @return The fetched row
	 */
	virtual AbstractDbRow* fetch() = 0;

	/**
	 * @brief Get the query execution time
	 */
	double executionTime() const;

	/**
	 * @brief Get the column count
	 */
	int columnCount() const;

	/**
	 * @brief Get the column names list
	 */
	StringList columnNames() const;

	/**
	 * @brief Get the column index with the given name
	 * @param name The name of the column
	 * @return The column index
	 */
	int columnIndex(const String& name) const;

	/**
	 * @brief Implements the getter to know if the result is at the end
	 * @return true if the result has more rows, otherwise false
	 */
	virtual bool hasNext() const = 0;

protected:
	/**
	 * @brief Constructs an interface to a SQL result
	 * @param executionTime The query execution time
	 * @param affectedRows The number of rows affected by the query
	 */
	AbstractDbResult(double executionTime, int affectedRows = -1);

	/**
	 * @brief Implements how to get the column count
	 */
	virtual int getColumnCount() const = 0;

	/**
	 * @brief Implements how to get the column names list
	 */
	virtual StringList getColumnNames() const = 0;

	void init();

private:
	/**
	 * @brief The query execution time
	 */
	double _executionTime;

	/**
	 * @brief The number of rows affected by the query
	 */
	int _affectedRows;

	/**
	 * @brief The column count
	 */
	int _columnCount;

	/**
	 * @brief The column names list
	 */
	Map<String, int> _columnNames;
};

//typedef const AbstractDbResult& DbResult;

class DbResult
{
public:
	DbResult(AbstractDbResult* res) : _res(res)
	{ }

	~DbResult()
	{ delete _res; }

	AbstractDbRow* fetch() const
	{ return _res->fetch(); }

	double executionTime() const
	{ return _res->executionTime(); }

private:
	AbstractDbResult* _res;
};

#endif // !_DB_ABSTRACTDBRESULT_H_
