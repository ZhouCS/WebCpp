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
 * @file Exceptions/Db.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-25
 */

#ifndef _EXCEPTIONS_DB_H_
#define	_EXCEPTIONS_DB_H_

#include "Exceptions/Exception.h"

#include "Libs/CodeHighlighter.h"

namespace Exceptions
{

class DbConnection : public Exception
{
public:
	DbConnection(const String& host,
	             const String& login,
	             int port,
	             const String& db,
	             const String& error) :
	Exception("DbConnection",
	          String("Failed to connect to database server %1@%2 on port %3 "
	                 "database '%4': %5").format({host, login, port, db, error}))
	{}
};

class SqlQuery : public Exception
{
public:
	SqlQuery(const String& query, const String& error)
	  : Exception("SqlQuery",
	              String("SQL query failed: %1").format(error))
	{
		_htmlMessage = String("<p>An SQL query failed.</p><h3>SQL query</h3><pre>")
		               + CodeHighlighter::codeBlock("cpp", query)
		               + "</pre><h3>Error message</h3>" + error.htmlEscape();
	}
};

class NoSuchDbms : public Exception
{
public:
	NoSuchDbms(const String& id)
	  : Exception("NoSuchDbms",
	              String("There is no DBMS with ID “%1”").format(id))
	{}
};

}

#endif // !_EXCEPTIONS_DB_H_
