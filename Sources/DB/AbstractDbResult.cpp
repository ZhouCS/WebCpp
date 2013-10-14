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
 * @file DB/AbstractDbResult.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-27
 */

#include "DB/AbstractDbResult.h"

#include "Libs/Chrono.h"

AbstractDbResult::AbstractDbResult(double executionTime, int affectedRows)
{
	_executionTime = executionTime;
	_affectedRows = affectedRows;
}

void AbstractDbResult::init()
{
	_columnCount = getColumnCount();

	StringList names = getColumnNames();
	for (int i = 0; i < names.count(); i++)
		_columnNames[names[i]] = i;
}

double AbstractDbResult::executionTime() const
{ return _executionTime; }

int AbstractDbResult::columnCount() const
{ return _columnCount; }

StringList AbstractDbResult::columnNames() const
{ return _columnNames.keys(); }

int AbstractDbResult::columnIndex(const String& name) const
{ return _columnNames[name]; }
