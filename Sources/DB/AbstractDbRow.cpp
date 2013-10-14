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
 * @file DB/AbstractDbRow.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-28
 */

#include "DB/AbstractDbRow.h"
#include "DB/AbstractDbResult.h"

#include "Types/Variant.h"

AbstractDbRow::AbstractDbRow(const AbstractDbResult* result)
{
	_result = result;
}

String AbstractDbRow::col(const String& columnName) const
{ return get(_result->columnIndex(columnName)); }

String AbstractDbRow::col(const char* columnName) const
{ return get(_result->columnIndex(columnName)); }

String AbstractDbRow::col(int index) const
{ return get(index); }

StringList AbstractDbRow::columnNames() const
{ return _result->columnNames(); }

Map<String, String> AbstractDbRow::values() const
{
	Map<String, String> vals;
	StringList cols = columnNames();

	for (const String& colName : cols)
		vals[colName] = col(colName);
	return vals;
}

Map<String, Variant> AbstractDbRow::renderableValues() const
{
	Map<String, Variant> vals;
	StringList cols = columnNames();

	for (const String& colName : cols)
		vals[colName] = col(colName);
	return vals;
}
