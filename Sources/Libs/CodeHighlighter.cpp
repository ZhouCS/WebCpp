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
 * @file Libs/CodeHighlighter.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-25
 */

#include <stack>

#include "Libs/CodeHighlighter.h"
#include "Libs/Dir.h"
#include "Plugins/Plugin.h"

#include "Exceptions/CodeHighlighters.h"
#include "Types/OrderedMap.h"
#include "Types/Stack.h"

Map<String, CodeHighlighter*> CodeHighlighter::_codeHighlighters;

CodeHighlighter::CodeHighlighter(const String& id)
{
	_id = id;
	_plugin = nullptr;
}

CodeHighlighter::~CodeHighlighter()
{

}

String CodeHighlighter::highlight(const String& code)
{
	_styles.clear();
	highlightImpl(code);

	String output = code;
	int srcPos, offset = 0;
	const char* ch = code.toCString();
	const char* const startPtr = ch;
	OrderedMap<int, StyleMarker>::Iterator stylesIter(_styles);
	int nextPos = stylesIter.hasNext() ? stylesIter.key() : -1;
	Stack<int> endPosStack;

	for (; *ch; ch++)
	{
		srcPos = ch - startPtr;

		if (*ch == '<')
		{
			output = output.replace(srcPos + offset, srcPos + offset, "&lt;");
			offset += 3;
		}
		else if (*ch == '>')
		{
			output = output.replace(srcPos + offset, srcPos + offset, "&gt;");
			offset += 3;
		}
		else if (*ch == '&')
		{
			output = output.replace(srcPos + offset, srcPos + offset, "&amp;");
			offset += 4;
		}

		if (srcPos == nextPos)
		{
			StyleMarker styleMarker = stylesIter.value();
			String span = "<span class=\"" + styleMarker.name + "\">";
			output = output.insert(srcPos + offset, span);
			offset += span.size();

			endPosStack.push(styleMarker.endPos);
			stylesIter++;
			nextPos = stylesIter.hasNext() ? stylesIter.key() : -1;
		}
		if (!endPosStack.isEmpty() && srcPos == endPosStack.top())
		{
			output = output.insert(srcPos + offset + 1, "</span>");
			offset += 7;
			endPosStack.pop();
		}
	}

	return output;
}

String CodeHighlighter::codeBlock(const String& id, const String& code)
{
	String html = "<div class=\"code codeBlock " + id
	              + "\"><div class=\"numbers\">";
	int lines = code.count("\n") + 1;
	html.reserve(html.size() + lines * 8);
	for (int i = 1; i <= lines; i++)
		html += String(i) + (i < lines ? "<br />" : "");
	return html + "</div><pre>" + (id == "plain"
	                               ? code.htmlEscape()
	                               : byId(id)->highlight(code)) + "</pre></div>";
}

void CodeHighlighter::reloadCodeHighlighters()
{
	deleteCodeHighlighters();
	StringList files = Dir("WebCpp/Plugins/CodeHighlighters").entries();
	for (const String& fileName : files)
	{
		Plugin* plugin = new Plugin("WebCpp/Plugins/CodeHighlighters/" + fileName);
		CodeHighlighter* codeHighlighter = plugin->instance<CodeHighlighter>();
		codeHighlighter->_plugin = plugin;
		_codeHighlighters[codeHighlighter->id()] = codeHighlighter;
	}
}

void CodeHighlighter::deleteCodeHighlighters()
{
	for (Map<String, CodeHighlighter*>::Iterator i(_codeHighlighters);
	     i.hasNext(); i++)
		delete i.value();
	_codeHighlighters.clear();
}

void CodeHighlighter::setStyle(const String& styleName,
                               int startPos,
                               int endPos)
{
	_styles[startPos] = StyleMarker({styleName, startPos, endPos});
}

CodeHighlighter* CodeHighlighter::byId(const String& id)
{
	CodeHighlighter* codeHighlighter = _codeHighlighters.get(id, nullptr);
	if (codeHighlighter == nullptr)
		throw Exceptions::NoSuchCodeHighlighter(id);
	return codeHighlighter;
}

//----------------------------------------------------------------------------//

String CodeHighlighter::id() const
{ return _id; }
