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
 * \file MysqlConnection.h
 * \author Kévin Lesénéchal
 * \date 2011-12-18
 */

#ifndef _WPP_MYSQLCONNECTION_H_
#define	_WPP_MYSQLCONNECTION_H_

#include <DB/AbstractDbConnection.h>

#include <mysql/mysql.h>

/**
 * @brief A MySQL connection
 */
class MysqlConnection : public AbstractDbConnection
{
public:
	/**
	 * @brief Constructs a MySQL connection
	 */
	MysqlConnection();
	
	/**
	 * @brief Destructs the MySQL connection
	 */
	virtual ~MysqlConnection();
	
	/**
	 * @brief Implements how to connect to the database
	 * @param host The host
	 * @param login The login
	 * @param password The password
	 * @param db The database name
	 * @param port The port to connect to
	 */
	virtual void connect(const String& host, const String& login,
	                     const String& password, const String& db,
	                     unsigned int port = 0);
	
	/**
	 * @brief Implements how to disconnect from the database
	 */
	virtual void disconnect();
	
	/**
	 * @brief Escape a string for an SQL request
	 * @param str The string to escape
	 * @return The escaped string
	 */
	virtual String escapeString(const String& str);

private:
	/**
	 * @brief Implements how to execute a query on the database
	 * @param sql The SQL query as string
	 * @return The SQL result
	 */
	virtual AbstractDbResult* queryExec(const String& sql);

private:
	MYSQL _handle;
};

#endif // !_WPP_MYSQLCONNECTION_H_
