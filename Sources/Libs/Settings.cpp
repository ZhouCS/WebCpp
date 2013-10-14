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
 * @file Libs/Settings.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-01-29
 */

#include "Libs/Settings.h"
#include "Libs/IO/File.h"
#include "Types/ByteArray.h"

#include <set>

#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>

Settings::Settings()
{

}

Settings Settings::fromIniFile(const Path& filePath)
{
	Settings s;

	std::stringstream ss(String(File::getContent(filePath)).toStdString());
	std::set<std::string> options;
	options.insert("*");

	for (boost::program_options::detail::config_file_iterator i(ss, options), e;
	     i != e; ++i)
	{
		String section = String(i->string_key).contains(".")
		                 ? String(i->string_key).section(".", 0, 0)
		                 : "General";
		s._values[section + "." + String(i->string_key).section(".", 1, -1)]
		    = String(i->value[0]);
	}

	return s;
}

Map<String, Map<String, String>> Settings::values() const
{
	Map<String, Map<String, String>> r;
	for (Map<String, String>::Iterator i(_values); i.hasNext(); i++)
		r[i.key().tokenLeft(".")][i.key().tokenRight(".")] = i.value();
	return r;
}

String Settings::operator[](const String& key) const
{ return _values[key]; }
