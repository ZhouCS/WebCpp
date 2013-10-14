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
 * @file Exceptions/Exception.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-08
 */

#ifndef _EXCEPTIONS_EXCEPTION_H_
#define	_EXCEPTIONS_EXCEPTION_H_

#include <exception>
#include <stdint.h>

#include "Types/String.h"
#include "Types/Path.h"

class StackTrace;

#define EXCEPTION(_Name_, _Message_, ...) \
	class _Name_ : public Exception         \
	{                                       \
	public:                                 \
		_Name_(__VA_ARGS__) :                 \
			Exception(#_Name_, _Message_)       \
		{}                                    \
	};

/**
 * @class Exception Exceptions/Exception.h <Exception>
 * @brief A basic exception
 */
class Exception : public std::exception
{
public:
	struct StackFrame
	{
		uint64_t address;
		Path object;
		String functionName;
		String fileName;
		int line;
	};

	/**
	 * @brief Constructs a basic exception
	 * @param message The exception message
	 */
	Exception(const String& type, const String& message) throw();

	/**
	 * @brief Destructs the exception
	 */
	virtual ~Exception() throw();

	String type() const;
	String message() const;
	String htmlMessage() const;
	StackTrace* stackTrace() const;

	/**
	 * @brief Implements how to get the exception message in a standard way
	 * @return The exception message as C-string
	 */
	virtual const char* what() const throw();

protected:
	/**
	 * @brief The exception type
	 */
	String _type;

	/**
	 * @brief The exception message
	 */
	String _message;

	/**
	 * @brief The exception HTML description to display in error pages
	 */
	String _htmlMessage;

private:
	//static Map<String, uint64_t> _soMapsCache;

private:
	/*mutable List<StackFrame> _stackTrace;
	size_t _stackTraceSize;
	void* _stackTraceBuffer[64];
	char** _stackTraceLines;*/
	StackTrace* _stackTrace;
};

/**
 * @brief Namespace containing all exceptions
 */
namespace Exceptions {

class ExceptionNotImplemented : public Exception
{
public:
	ExceptionNotImplemented()
	  : Exception("ExceptionNotImplemented",
	              "There is no exception implemented yet")
	{}
};

class InternalError : public Exception
{
public:
	InternalError(const String& msg)
	  : Exception("InternalError",
	              String("Internal error: %1. Please file a bug on "
	                     "<http://bugs.webcpp.org/>.").format(msg))
	{
		_htmlMessage = "<p>An internal error occured, this should never happen. "
		               "Please file a bug report on "
		               "<a href=\"http://bugs.webcpp.org/\">bugs.webcpp.org</a>."
		               "</p><blockquote>" + msg.htmlEscape() + "</blockquote>";
	}
};

}

#endif // !_EXCEPTIONS_EXCEPTION_H_
