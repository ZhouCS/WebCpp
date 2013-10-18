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
 * @file MysqlConnection.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-18
 */

#include "MysqlConnection.h"
#include "MysqlResult.h"

#include <Chrono>
#include <String>
#include <Exceptions/Db.h>

MysqlConnection::MysqlConnection()
{
	mysql_init(&_handle);
	mysql_options(&_handle, MYSQL_READ_DEFAULT_GROUP, "option");
}

MysqlConnection::~MysqlConnection()
{
	disconnect();
}

void MysqlConnection::connect(const String& host, const String& login,
                              const String& password, const String& db,
                              unsigned int port)
{
	if (!mysql_real_connect(&_handle, host.toCString(), login.toCString(),
	                        password.toCString(), db.toCString(), port, 0, 0))
		throw Exceptions::DbConnection(host, login, port, db,
		                               mysql_error(&_handle));
}

void MysqlConnection::disconnect()
{
	mysql_close(&_handle);
}

AbstractDbResult* MysqlConnection::queryExec(const String& sql)
{
	Chrono chrono(true);
	
	if (mysql_real_query(&_handle, sql.toCString(), sql.size()) != 0)
		throw Exceptions::SqlQuery(sql, mysql_error(&_handle));
	
	if (mysql_field_count(&_handle) == 0)
		return new MysqlResult(0, chrono.elapsed(), mysql_affected_rows(&_handle));
	
	MYSQL_RES* res = mysql_use_result(&_handle);
	chrono.stop();
	
	//MysqlResult* r = new MysqlResult(res, chrono->elapsed());
	return new MysqlResult(res, chrono.elapsed());
	//return DbResult(std::shared_ptr<const AbstractDbResult>(r));
}

String MysqlConnection::escapeString(const String& str)
{
	char* datas = new char[str.size() * 2 + 1];
	mysql_real_escape_string(&_handle, datas, str.toCString(), str.size());
	String r(datas);
	delete[] datas;
	return r;
}
