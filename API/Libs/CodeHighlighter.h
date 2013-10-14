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
 * @file Libs/CodeHighlighter.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-25
 */

#ifndef _LIBS_CODEHIGHLIGHTER_H_
#define	_LIBS_CODEHIGHLIGHTER_H_

#include "Types/String.h"
#include "Types/Map.h"
#include "Types/OrderedMap.h"

class Plugin;

/**
 * @class CodeHighlighter Libs/CodeHighlighter.h <CodeHighlighter>
 * @brief An abstract code highlighter
 */
class CodeHighlighter
{
public:
	/**
	 * @brief Constructs a code highlighter
	 * @param id The code highlighter's ID
	 */
	CodeHighlighter(const String& id);

	/**
	 * @brief Destructs a code highlighter
	 */
	virtual ~CodeHighlighter();

	/**
	 * @brief Highlights a code using the code highlighter
	 * @param code The code to highlight
	 * @return The highlighted code
	 */
	String highlight(const String& code);

	/**
	 * @brief Returns a highlighted code block with line numbers
	 * @param id The code highlighter ID to use for highlighting
	 * @param code The code to highlight
	 * @return A highlighted code block with line numbers
	 */
	static String codeBlock(const String& id, const String& code);

	/**
	 * @brief Reloads the code highlighters from .so files
	 */
	static void reloadCodeHighlighters();

	/**
	 * @brief Deletes all code highlighters
	 */
	static void deleteCodeHighlighters();

	/**
	 * @brief Get a code highlighter by ID
	 * @param id The code highlighter ID
	 * @return The code highlighter associated to @p id
	 */
	static CodeHighlighter* byId(const String& id);


	/**
	 * @brief Get the code highlighter ID
	 * @return The code highlighter ID
	 */
	String id() const;

protected:
	/**
	 * @brief Implements how to highlight code
	 * @param line The code to format
	 * @return The formatted code (HTML)
	 */
	virtual void highlightImpl(const String& code) = 0;

	/**
	 * @brief Apply a style to a code snippet
	 * @param styleName The style name to apply
	 * @param startPos The start position
	 * @param endPos The end position
	 */
	void setStyle(const String& styleName, int startPos, int endPos);

private:
	struct StyleMarker
	{
		String name;
		int startPos;
		int endPos;
	};

private:
	/**
	 * @brief Code highlighters list
	 */
	static Map<String, CodeHighlighter*> _codeHighlighters;

	/**
	 * @brief The code highlighter ID
	 */
	String _id;

	/**
	 * @brief The associated plugin
	 */
	Plugin* _plugin;

	/**
	 * @brief Style markers for the current highlighting
	 */
	OrderedMap<int, StyleMarker> _styles;
};

#endif // !_LIBS_CODEHIGHLIGHTER_H_
