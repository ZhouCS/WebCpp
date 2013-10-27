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
 * @file DB/AbstractDbRow.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-28
 */

#ifndef _WPP_DB_ABSTRACTDBROW_H_
#define	_WPP_DB_ABSTRACTDBROW_H_

#include "Types/String.h"

class AbstractDbResult;
class String;
class Variant;

/**
 * @class AbstractDbRow DB/AbstractDbRow.h <AbstractDbRow>
 * @brief An interface to a SQL result row
 */
class AbstractDbRow
{
public:
	/**
	 * @brief Constructs an interface to a SQL result row
	 */
	AbstractDbRow(const AbstractDbResult* result);

	virtual ~AbstractDbRow()
	{ }

	/**
	 * @brief Get a value by column name
	 * @param columnName The column name
	 * @return The value
	 */
	String col(const String& columnName) const;

	/**
	 * @brief Get a value by column name
	 * @param columnName The column name
	 * @return The value
	 */
	String col(const char* columnName) const;

	/**
	 * @brief Get a value by column index
	 * @param index The column index
	 * @return The value
	 */
	String col(int index) const;

	/**
	 * @brief Get the column list
	 */
	StringList columnNames() const;

	/**
	 * @brief Get the values as map
	 */
	Map<String, String> values() const;

	/**
	 * @brief Get the values as renderable map
	 */
	Map<String, Variant> renderableValues() const;

protected:
	/**
	 * @brief Implements how to get a value
	 * @param index The index of the column
	 * @return The value of the column at index @p index
	 */
	virtual String get(int index) const = 0;

protected:
	/**
	 * @brief The associated SQL result
	 */
	const AbstractDbResult* _result;
};

class DbRow
{
public:
	DbRow(AbstractDbRow* row) : _row(row)
	{ }

	~DbRow()
	{
		if (_row != nullptr)
			delete _row;
	}

	String operator[](const String& columnName) const
	{ return _row->col(columnName); }

	String operator[](const char* columnName) const
	{ return _row->col(columnName); }

	String operator[](int index) const
	{ return _row->col(index); }

	operator bool() const
	{ return _row != nullptr; }

private:
	AbstractDbRow* _row;
};

#endif // !_WPP_DB_ABSTRACTDBROW_H_
