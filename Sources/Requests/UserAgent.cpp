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
 * @file Requests/UserAgent.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-16
 */

#include "Requests/UserAgent.h"
#include "Types/StringList.h"

#include <iostream>

Map<String, UserAgent> UserAgent::_cache;

UserAgent::UserAgent()
{
	_browser = OtherBrowser;
	_platform = OtherPlatform;
	_procArch = UnknownArch;
}

UserAgent UserAgent::fromString(const String& agent)
{
	if (_cache.hasKey(agent))
		return _cache[agent];

	UserAgent r;
	r._agent = agent;
	r._browser = OtherBrowser;
	r._platform = OtherPlatform;
	r._procArch = UnknownArch;

	String rest = agent;

	int pos = agent.indexOf("(");
	if (pos > -1)
	{
		int pos2 = agent.indexOf(")", pos);
		if (pos2 > -1)
		{
			StringList osParts = agent.mid(pos + 1, pos2).split("; ");

			for (int i = 0; i < osParts.count(); i++)
			{
				if (osParts[i].startsWith("Windows NT "))
				{
					String version = osParts[i].removeLeft(11);
					if (version == "5.1")
						r._platform = WinXP;
					else if (version == "6.0")
						r._platform = WinVista;
					else if (version == "6.1")
						r._platform = Win7;
				}
				else if (osParts[i].contains("Mac OS X"))
					r._platform = MacOSX;
				else if (osParts[i].contains("Linux"))
					r._platform = Linux;
				else if (osParts[i].contains("FreeBSD")
				         || osParts[i].contains("NetBSD")
				         || osParts[i].contains("OpenBSD"))
					r._platform = BSD;

				if (osParts[i].contains("x86_64")
				    || osParts[i].contains("x64")
				    || osParts[i].contains("Win64")
				    || osParts[i].contains("WOW64"))
					r._procArch = x86_64;
				else if (r.isWindows()
				         || osParts[i].contains("i686")
				         || osParts[i].contains("i386"))
					r._procArch = x86;

				if (osParts[i].startsWith("MSIE "))
				{
					r._browser = InternetExplorer;
					r._browserVersion = osParts[i].removeLeft(5);
				}
			}

			rest = agent.replace(pos - 1, pos2 + 1, "");
		}
	}

	if (r._browser == OtherBrowser)
	{
		StringList restParts = rest.split(" ");
		for (const String& part : restParts)
		{
			if (part.startsWith("Firefox"))
				r._browser = Firefox;
			else if (part.startsWith("Opera"))
				r._browser = Opera;
			else if (part.startsWith("Chrome"))
				r._browser = Chrome;
			else if (part.startsWith("Safari"))
				r._browser = Safari;

			int pos = part.indexOf("/");
			if (r._browser != OtherBrowser && pos > -1)
				r._browserVersion = part.substr(pos + 1);

			if (r._browser != OtherBrowser)
				break;
		}
	}

	_cache[agent] = r;
	return r;
}

bool UserAgent::isWindows() const
{ return _platform == WinXP || _platform == WinVista || _platform == Win7; }

UserAgent::Platform UserAgent::platform() const
{ return _platform; }

String UserAgent::platformName() const
{
	if (_platform == WinXP)
		return "Windows XP";
	else if (_platform == WinVista)
		return "Windows Vista";
	else if (_platform == Win7)
		return "Windows 7";
	else if (_platform == MacOSX)
		return "Mac OS X";
	else if (_platform == Linux)
		return "Linux";
	else if (_platform == BSD)
		return "*BSD";
	return "";
}

UserAgent::ProcArch UserAgent::procArch() const
{ return _procArch; }

UserAgent::Browser UserAgent::browser() const
{ return _browser; }

String UserAgent::browserName() const
{
	if (_browser == Firefox)
		return "Mozilla Firefox";
	else if (_browser == InternetExplorer)
		return "Internet Explorer";
	else if (_browser == Opera)
		return "Opera";
	else if (_browser == Chrome)
		return "Google Chrome";
	else if (_browser == Safari)
		return "Safari";
	return "";
}

Version UserAgent::browserVersion() const
{ return _browserVersion; }
