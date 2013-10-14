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
 * @file StringList.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-26
 */

#include "Types/StringList.h"

StringList::StringList() : List<String>()
{

}

StringList::StringList(const List<String>& list) : List<String>(list)
{ }

StringList::StringList(std::initializer_list<String> initList) : List<String>(initList)
{ }


String StringList::join(const String& delem) const
{
	String r;
	for(int i = 0; i < count(); i++)
		r += at(i) + (i < count()-1 ? delem : "");
	return r;
}

String StringList::dump() const
{
	//String r = String("String list (%1 items) [").format(count());
	String r = "[";
	for(int i = 0; i < count(); i++)
	{
		r += String("\"") + at(i) + "\"";
		if(i + 1 < count())
			r += ", ";
	}
	return r + "]";
}
