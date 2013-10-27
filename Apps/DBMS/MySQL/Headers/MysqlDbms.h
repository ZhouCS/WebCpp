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
 * @file MysqlDbms.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-06-26
 */

#ifndef _WPP_MYSQLDBMS_H_
#define	_WPP_MYSQLDBMS_H_

#include <DB/DatabaseSystem.h>
#include <Plugin>

class MysqlDbms : public DatabaseSystem
{
public:
	MysqlDbms();
	
	virtual ~MysqlDbms();
	
	/**
	 * @brief Implements how to get a new DBMS connection instance
	 * @return The new DBMS connection instance
	 */
	virtual AbstractDbConnection* newConnection() const;
};

#endif // !_WPP_MYSQLDBMS_H_
