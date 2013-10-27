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
 * @file System.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-23
 */

#ifndef _WPP_SYSTEM_H_
#define _WPP_SYSTEM_H_

#include "Types/String.h"
#include "Types/StringList.h"
#include "Types/IpAddr.h"

#include "Libs/Settings.h"

class Site;
class Thread;
class SystemRouter;
class Plugin;
class CliOptions;

/**
 * @brief Macro to get the absolute directory path
 */
#define ABS (System::get()->absolutePath())

/**
 * @brief The WebCpp version
 */
#define VERSION Version("0.1-dev1")

struct SystemSettings
{
	bool   handleExceptions;
	bool   behindProxy;
	String defaultTemplateEngine;
	String defaultContentType;
	String defaultCharset;
	bool   sessionsEnabled;
	String sessionIdCookieName;
	String sessionTokenCookieName;
	bool   sessionIpCheck;
	String defaultLocale;
};

/**
 * @class System System.h <System>
 * @brief The WebCpp central system
 */
class System
{
public:
	enum LogSeverity{Debug, Information, Warning, Critical};

	/**
	 * @brief Destructs the system instance
	 */
	~System();

	/**
	 * @brief Get the system instance
	 * @return The system instance
	 */
	static System* get();

	/**
	 * @brief Runs the system
	 * @param args Parameters list (from main())
	 * @return The program terminate code
	 * @warning This function must be called once
	 */
	int run(const StringList& args);

	/**
	 * @brief Returns the WebCpp's version
	 * @return The WebCpp's version
	 */
	String version() const;

	/**
	 * @brief Get the executable directory absolute path
	 */
	String absolutePath() const;

	String runDir() const;

	/**
	 * @brief Get a setting value
	 * @param key The setting value key
	 * @return The setting value to key @p key
	 */
	static String setting(const String& key);

	static const SystemSettings* settings();

	static void log(const String& logName,
	                const String& message,
	                LogSeverity severity = Information,
	                const IpAddr& ip = IpAddr());

	static void log(const String& logName,
	                const String& message,
	                const IpAddr& ip);

	void addLoadedPlugin(Plugin* plugin);

	/**
	 * @brief Get the site instance
	 */
	Site* site() const;

	SystemRouter* systemRouter() const;

	/**
	 * @brief Get the socket descriptor
	 */
	int socket() const;

private:
	/**
	 * @brief Constructs the system instance
	 */
	System();

public:
	/**
	 * @brief Callback function to be called in case of SIGSEGV signal
	 */
	static void segfault(int);

	static bool isDebug();

	static bool isRunning();

	static bool hasExceptionHandling();

private:
	/**
	 * @brief Defines whenever the system is running or not
	 */
	bool _running;

	bool _debug;

	/**
	 * @brief Command line options
	 */
	CliOptions* _cliOptions;

	/**
	 * @brief The executable directory absolute path
	 */
	String _absolutePath;

	String _runDir;

	/**
	 * @brief General settings
	 */
	Settings _settings;

	static SystemSettings _cachedSettings;

	/**
	 * @brief The site instance
	 */
	Site* _site;

	SystemRouter* _systemRouter;

	/**
	 * @brief The list of processing threads
	 */
	List<Thread*> _threads;

	List<Plugin*> _loadedPlugins;

	int _socket;
};

#endif // !_WPP_SYSTEM_H_
