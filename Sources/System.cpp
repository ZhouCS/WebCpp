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
 * @file System.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-23
 */

#include "System.h"

#include "Requests/Request.h"
#include "Sites/Site.h"
#include "Requests/RequestThread.h"
#include "CliOptions.h"

#include "Libs/Thread.h"
#include "Libs/Settings.h"
#include "Plugins/Plugin.h"

#include "MVC/Routers/Router.h"
#include "MVC/Templates/TemplatesManager.h"
#include "Libs/Xml/XmlDoc.h"
#include "Libs/Locale/TransManager.h"
#include "Libs/IO/File.h"
#include "Libs/StackTrace.h"
#include "Types/DateTime.h"
#include "Libs/CodeHighlighter.h"
#include "DB/DatabaseSystem.h"
#include "Requests/SystemRouter.h"
#include "Requests/RequestProfile.h"
#include "Requests/Session.h"
#include "Shell/Shell.h"

#include "Exceptions/Segfault.h"
#include "Exceptions/Db.h"

#include <unistd.h>
#include <signal.h>
#include <fcgios.h>

SystemSettings System::_cachedSettings;

System::System()
{
	_running = false;
	_socket = 0;
	_systemRouter = nullptr;
	_site = nullptr;
}

System::~System()
{
	OS_LibShutdown(); // Fixes a memory leak in FastCGI

	DatabaseSystem::deleteDbmsList();
	CodeHighlighter::deleteCodeHighlighters();
	Shell::deleteCommands();
	Session::deleteSessions();
	RequestProfile::deleteProfiles();

	if (_site != nullptr)
		delete _site;
	delete TransManager::get();
	delete TemplatesManager::get();
	for (Plugin* plugin : _loadedPlugins)
		delete plugin;
	delete _cliOptions;
}

System* System::get()
{
	static System* system = new System;
	return system;
}

int System::run(const StringList& args)
{
	if (_running)
		return 1;
	_running = true;

#ifdef DEBUG
	_debug = true;
#else
	_debug = false;
#endif

	//if (_debug)
	//	signal(SIGSEGV, &segfault);

	_cliOptions = new CliOptions(args);

	//std::locale::global(std::locale("en_US.UTF-8"));

	if (_cliOptions->flag(CliOptions::Version))
	{
		std::cout << "WebCpp v" << version() << std::endl;
		return 0;
	}

	std::cout << "Starting WebCpp v" << version() << " <http://www.webcpp.org/>."
	          << std::endl
	          << "Copyright © 2011-2013 Kévin Lesénéchal <kevin@lesenechal.org>."
	          << std::endl
	          << "This program is free software and distributed under the "
	          << std::endl
	          << "GNU General Public License. See <http://www.gnu.org/licenses/>."
						<< std::endl << std::endl;

	char exe[512];
	ssize_t exeSize;
	if ((exeSize = readlink("/proc/self/exe", exe, (sizeof exe) - 1)) < 0)
		return 1;
	exe[exeSize] = '\0';
	_absolutePath = String(exe).section("/", 0, -3);
	char* dirName = get_current_dir_name();
	_runDir = String(dirName);
	free(dirName);

	_settings = Settings::fromIniFile("WebCpp/Config.ini");
	_cachedSettings.handleExceptions = _settings["General.HandleExceptions"];
	_cachedSettings.behindProxy = _settings["General.BehindProxy"];
	_cachedSettings.defaultTemplateEngine
	    = _settings["General.DefaultTemplateEngine"];
	_cachedSettings.defaultContentType = _settings["Content.DefaultContentType"];
	_cachedSettings.defaultCharset = _settings["Content.DefaultCharset"];
	_cachedSettings.sessionsEnabled = _settings["Sessions.Enabled"];
	_cachedSettings.sessionIdCookieName = _settings["Sessions.IdCookieName"];
	_cachedSettings.sessionTokenCookieName
	    = _settings["Sessions.TokenCookieName"];
	_cachedSettings.sessionIpCheck = _settings["Sessions.IpCheck"];
	_cachedSettings.defaultLocale = _settings["Locale.DefaultLocale"];

	DatabaseSystem::reloadDbmsList();
	CodeHighlighter::reloadCodeHighlighters();

	_systemRouter = new SystemRouter;

	try
	{
		_site = Site::load();
	}
	catch (const Exceptions::DbConnection& e)
	{
		std::cerr << "Critical: " << e.message() << std::endl;
		return 1;
	}

	TransManager::get()->reloadFromFiles();

	FCGX_Init();
	_socket = FCGX_OpenSocket(setting("FastCGI.Socket").toCString(), 100);

	int threadsCount = setting("FastCGI.Threads");
	if (threadsCount < 1)
	{
		std::cerr << args[0] << ": invalid number of threads." << std::endl;
		return 1;
	}

	if ((!_debug || _cliOptions->flag(CliOptions::NoPrompt))
	    && !_cliOptions->flag(CliOptions::ForcePrompt))
		threadsCount--;
	for (int i = 0; i < threadsCount; i++)
	{
		Thread* thread = new Thread(&fcgiProcessingLoop);
		_threads.append(thread);
		thread->start();
	}

	if (((!_debug || _cliOptions->flag(CliOptions::NoPrompt))
	     && !_cliOptions->flag(CliOptions::ForcePrompt))
	    || _cliOptions->flag(CliOptions::Debug))
		fcgiProcessingLoop();
	else
		Shell::run();

	std::cout << "Shuting down…" << std::endl;
	_running = false;
	for (Thread* thread : _threads)
	{
		//thread->stop();
		thread->wait();
		delete thread;
	}
	return 0;
}

void System::log(const String& logName,
                 const String& message,
                 LogSeverity severity,
                 const IpAddr& ip)
{
	String content = "[" + DateTime::now().toString("%Y-%m-%d %H:%M:%S") + "] ";

	if (!ip.isNull())
		content += "<" + ip.toString() + "> ";

	if (severity == Debug)
		content += "Debug: ";
	else if (severity == Warning)
		content += "Warning: ";
	else if (severity == Critical)
		content += "CRITICAL: ";

	content += message + "\n";

	File file("WebCpp/Logs/" + logName + ".log");
	file.open(IODevice::WriteOnly | IODevice::Append);
	file.write(content);
	file.close();
}

void System::log(const String& logName, const String& message, const IpAddr& ip)
{ log(logName, message, Information, ip); }

void System::addLoadedPlugin(Plugin* plugin)
{
	_loadedPlugins.append(plugin);
}

void System::segfault(int)
{
	//signal(SIGSEGV, SIG_DFL);
	throw Exceptions::Segfault();
}

bool System::isDebug()
{ return System::get()->_debug; }

bool System::isRunning()
{ return System::get()->_running; }

bool System::hasExceptionHandling()
{
	return System::get()->_cachedSettings.handleExceptions
	    && !System::get()->_cliOptions->flag(CliOptions::Debug);
}

//----------------------------------------------------------------------------//

String System::absolutePath() const
{ return _absolutePath; }

String System::runDir() const
{ return _runDir; }

String System::version() const
{ return "0.1-dev1"; }

String System::setting(const String& key)
{ return get()->_settings[key]; }

const SystemSettings* System::settings()
{ return &_cachedSettings; }

Site* System::site() const
{ return _site; }

SystemRouter* System::systemRouter() const
{ return _systemRouter; }

int System::socket() const
{ return _socket; }
