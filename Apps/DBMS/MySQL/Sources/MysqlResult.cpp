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
 * @file MysqlResult.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-28
 */

#include "MysqlResult.h"
#include "MysqlRow.h"

#include <cstdlib>

MysqlResult::MysqlResult(MYSQL_RES* result, double executionTime,
                         int affectedRows)
  : AbstractDbResult(executionTime, affectedRows)
{
	_result = result;
	_hasNext = false;
	init();
}

MysqlResult::~MysqlResult()
{
	if (_result != nullptr)
		mysql_free_result(_result);
}

AbstractDbRow* MysqlResult::fetch()
{
	MYSQL_ROW row = mysql_fetch_row(_result);
	if (!row)
		return nullptr;
	return new MysqlRow(this, row);
}

int MysqlResult::getColumnCount() const
{
	if (_result == nullptr)
		return -1;
	return mysql_num_fields(_result);
}

StringList MysqlResult::getColumnNames() const
{
	StringList names;
	if (_result == nullptr)
		return names;
	
	int count = columnCount();
	MYSQL_FIELD* fields = mysql_fetch_fields(_result);
	for (int i = 0; i < count; i++)
		names.append(fields[i].name);
	return names;
}

bool MysqlResult::hasNext() const
{ return _hasNext; }
