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
 * @file Requests/RequestError.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-04-19
 */

#include "Requests/RequestError.h"

#include "Requests/Request.h"
#include "MVC/Templates/Template.h"
#include "System.h"
#include "Libs/StackTrace.h"

#include <cmath>
#include <iostream>
#include <iomanip>

void RequestError::exception(Request* request, Exception& e)
{
	int code = 500;
	if (e.type() == "NotFound")
		code = 404;
	else if (e.type() == "Forbidden")
		code = 403;

	if (code == 404)
		System::log("NotFound", e.message(), request->ip());
	else if (code == 403)
		System::log("Forbidden", e.message(), System::Warning, request->ip());
	else
		System::log("Exceptions",
		            String("“%1” exception: %2.").format({e.type(), e.message()}),
		            System::Warning, request->ip());

#ifndef DEBUG
	if (!request->headersSent())
		request->setStatus(code);
	Template* tpl = new Template("Errors/" + String(code) + ".html",
	                             nullptr, request);
	tpl->render();
	delete tpl;
	return;
#endif

	try
	{
		View tpl = new Template("Sys::Exception.html", nullptr, request);

		tpl["exceptionName"] = e.type();
		tpl["exceptionMessage"] = e.htmlMessage();
		tpl["webcppVersion"] = System::get()->version();
		tpl["serverName"] = request->env("SERVER_NAME", "");
		loadStackTrace(e, dynamic_cast<Template*>(*tpl));

		if (!request->headersSent())
			request->setStatus(500);
		tpl->render();
	}
	catch (const Exception& e2)
	{ fallbackErrorPage(request, e, e2.type()); }
	catch (const std::exception& e2)
	{ fallbackErrorPage(request, e, typeid(e2).name()); }
}

void RequestError::stdException(Request* request, const std::exception& e)
{
#ifndef DEBUG
	if (!request->headersSent())
		request->setStatus(500);
	Template* tpl = new Template("Errors/500.html", nullptr, request);
	tpl->render();
	delete tpl;
	return;
#endif

	/*try
	{
		View tpl = new Template("Sys::Exception.html", nullptr, request);
		tpl["exceptionName"] = (typeid e).name();
		tpl["exceptionMessage"] = e.what();
		tpl["webcppVersion"] = System::get()->version();
		tpl["serverName"] = request->env("SERVER_NAME", "");

		if (!request->headersSent())
			request->setStatus(500);
		tpl->render();
	}
	catch (const Exception& e2)
	{*/ fallbackErrorPage(request, e, ""); /* e, e2.type() */ /*}
	catch (const std::exception& e2)
	{ fallbackErrorPage(request, e, typeid(e2).name()); }*/
}

void RequestError::segfault(Request* request, Exceptions::Segfault& e)
{
	std::cerr << std::endl
	          << "        \033[31;1m******** SEGMENTATION FAULT ********\033[0m"
	          << std::endl << std::endl
	          << "WebCpp received a SIGSEGV signal: segmentation fault."
	          << std::endl << std::endl
	          << "This should never happen. Please file a bug to the WebCpp's "
	          << std::endl << "developers on <http://bugs.webcpp.org/>."
	          << std::endl << std::endl
	          << "\033[33;1m*** STACK TRACE ***\033[0m" << std::endl << std::endl;

	StackTrace* trace = new StackTrace(2);
	List<StackTrace::Frame> frames = trace->stackFrames();
	int i = 0, iLen = std::ceil(std::log10(frames.count()));
	for (const StackTrace::Frame& frame : frames)
	{
		std::cerr << "  " << std::setw(iLen) << i++ << ". "
		          << "\033[34;1m" << frame.function << "\033[0m"
		          << " + 0x" << String::fromNumber(frame.functionOffset, 16)
		          << " @ 0x" << String::fromNumber(frame.address, 16)
		          << std::endl << std::setw(iLen + 6) << " "
		          << "Sources/System.cpp line 112"
		          << " (from " << frame.object.absolutePath() << ")" << std::endl;
	}
	delete trace;
	std::cerr << std::endl;

	try
	{
		View tpl = new Template("Sys::Segfault.html", nullptr, request);

		tpl["webcppVersion"] = System::get()->version();
		tpl["serverName"] = request->env("SERVER_NAME", "");
		loadStackTrace(e, dynamic_cast<Template*>(*tpl));

		if (!request->headersSent())
			request->setStatus(500);
		tpl->render();
	}
	catch (const Exception& e2)
	{ fallbackErrorPage(request, e, e2.type()); }
	catch (const std::exception& e2)
	{ fallbackErrorPage(request, e2, typeid(e2).name()); }
}

void RequestError::loadStackTrace(Exception& e, Template* tpl)
{
	List<Variant> entries;
	List<StackTrace::Frame> stack = e.stackTrace()->stackFrames();
	for (const StackTrace::Frame& frame : stack)
	{
		Map<String, Variant> entry;
		entry["address"] = frame.address;
		entry["functionName"] = frame.function;
		entry["object"] = frame.object.relativePath();
		entry["fileName"] = frame.fileName;
		entry["line"] = frame.line;
		entries.append(entry);
	}
	tpl->set("stackTrace", entries);
}

void RequestError::fallbackErrorPage(Request* request,
                                     const Exception& e,
                                     const String& e2Name)
{
	if (!request->headersSent())
	{
		request->setStatus(500);
		request->sendHeaders();
	}
	request->stream() << "<h1>“" << e.type().htmlEscape() << "” exception</h1>"
	                  << "<p>" << e.htmlMessage() << "</p>"
	                  << "<p><strong>Additionally, a “" << e2Name
	                  << "” exception was encountered while handling the "
	                  << "exception.</strong></p>"
	                  << "<h2>Stack trace</h2><ol start=\"0\">";
	List<StackTrace::Frame> stack = e.stackTrace()->stackFrames();
	for (const StackTrace::Frame& frame : stack)
	{
		request->stream() << "<li><strong><code>" << frame.function.htmlEscape()
		                  << "</code></strong> (<code>0x"
		                  << String::fromNumber(frame.address, 16)
		                  << "</code>)<br />"
		                  << "<small>in <code>" << frame.object.relativePath()
		                  << "</code>, file <code>" << frame.fileName
		                  << "</code>, line " << frame.line << "</small></li>";
	}
	request->stream() << "</ol>";
}

void RequestError::fallbackErrorPage(Request* request,
                                     const std::exception& e,
                                     const String& e2Name)
{
	if (!request->headersSent())
	{
		request->setStatus(500);
		request->sendHeaders();
	}
	request->stream() << "<h1>“" << String(typeid(e).name()).htmlEscape()
	                  << "” standard exception</h1>"
	                  << "<p>" << String(e.what()).htmlEscape() << "</p>"
	                  << "<p><strong>Additionally, a “" << e2Name
	                  << "” exception was encountered while handling the "
	                  << "exception.</strong></p>";
}
