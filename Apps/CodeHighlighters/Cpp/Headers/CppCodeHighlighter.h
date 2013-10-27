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
 * @file CppCodeHighlighter.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-25
 */

#ifndef _WPP_CPPCODEHIGHLIGHTER_H_
#define	_WPP_CPPCODEHIGHLIGHTER_H_

#include <CodeHighlighter>
#include <Plugin>
#include <StringList>

class CppCodeHighlighter : public CodeHighlighter
{
public:
	CppCodeHighlighter();

	/**
	 * @brief Implements how to highlight code
	 * @param line The code to format
	 * @return The formatted code (HTML)
	 */
	virtual void highlightImpl(const String& code);

private:
	StringList _keywords;
	StringList _types;
};

PLUGIN_INSTANCE(CppCodeHighlighter)

#endif // !_WPP_CPPCODEHIGHLIGHTER_H_

