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
 * @file Requests/UserAgent.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-16
 */

#ifndef _REQUESTS_USERAGENT_H_
#define	_REQUESTS_USERAGENT_H_

#include "Types/String.h"
#include "Types/Version.h"
#include "Types/Map.h"

/**
 * @class UserAgent Requests/UserAgent.h <UserAgent>
 * @brief A user agent
 */
class UserAgent
{
public:
	enum Browser{OtherBrowser, Firefox, InternetExplorer, Opera, Chrome, Safari};
	enum Platform{OtherPlatform, WinXP, WinVista, Win7, Linux, BSD, MacOSX};
	enum ProcArch{UnknownArch, x86, x86_64};

	UserAgent();

	static UserAgent fromString(const String& agent);

	Platform platform() const;

	String platformName() const;

	ProcArch procArch() const;

	bool isWindows() const;

	Browser browser() const;

	String browserName() const;

	Version browserVersion() const;

private:

	static Map<String, UserAgent> _cache;

private:
	/**
	 * @brief The user agent string
	 */
	String _agent;

	/**
	 * @brief The user's browser
	 */
	Browser _browser;

	/**
	 * @brief The user's browser version
	 */
	Version _browserVersion;

	/**
	 * @brief The user's platform
	 */
	Platform _platform;

	/**
	 * @brief The user's language
	 */
	String _lang;

	/**
	 * @brief Defines whether the user's system is 64 bits or not
	 */
	ProcArch _procArch;
};

#endif // !_REQUESTS_USERAGENT_H_
