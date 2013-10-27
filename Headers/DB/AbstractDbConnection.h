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
 * @file DB/AbstractDbConnection.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-18
 */

#ifndef _WPP_DB_ABSTRACTDBCONNECTION_H_
#define	_WPP_DB_ABSTRACTDBCONNECTION_H_

class String;
class AbstractDbResult;
class Request;

//class DbResult;

/**
 * @class AbstractDbConnection DB/AbstractDbConnection.h <AbstractDbConnection>
 * @brief An interface to a database connection
 */
class AbstractDbConnection
{
public:
	virtual ~AbstractDbConnection(){}

	/**
	 * @brief Implements how to connect to the database
	 * @param host The host
	 * @param login The login
	 * @param password The password
	 * @param db The database name
	 * @param port The port to connect to
	 */
	virtual void connect(const String& host,
	                     const String& login,
	                     const String& password,
	                     const String& db,
	                     unsigned int port = 0) = 0;

	/**
	 * @brief Implements how to disconnect from the database
	 */
	virtual void disconnect() = 0;

	/**
	 * @brief Execute a query on the database
	 * @param sql The SQL query as string
	 * @param request The request instance
	 * @return The SQL result
	 */
	AbstractDbResult* query(const String& sql, Request* request = nullptr);

	/**
	 * @brief Escape a string for an SQL request
	 * @param str The string to escape
	 * @return The escaped string
	 */
	virtual String escapeString(const String& str) = 0;

protected:
	/**
	 * @brief Implements how to execute a query on the database
	 * @param sql The SQL query as string
	 * @return The SQL result
	 */
	virtual AbstractDbResult* queryExec(const String& sql) = 0;
};

#endif // !_WPP_DB_ABSTRACTDBCONNECTION_H_
