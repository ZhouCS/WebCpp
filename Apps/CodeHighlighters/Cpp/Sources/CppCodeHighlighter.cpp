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
 * @file CppCodeHighlighter.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-25
 */

#include "CppCodeHighlighter.h"

CppCodeHighlighter::CppCodeHighlighter()
  : CodeHighlighter("cpp")
{
	_keywords = {"NULL", "if", "else", "class", "return", "try", "catch", "new",
	             "delete", "static", "const", "public", "private", "protected",
	             "friend", "typedef", "template", "throw", "typename", "signed",
	             "unsigned", "true", "false", "this", "while", "constexpr",
	             "continue", "break", "explicit", "auto", "export", "asm", "goto",
	             "volatile", "using", "namespace", "inline", "operator", "final",
	             "mutable", "enum", "default", "bitand", "bitor", "xor", "compl",
	             "and_eq", "or_eq", "xor_eq", "and", "or", "not_eq", "not", "for",
	             "switch", "case", "struct", "union", "sizeof", "decltype", "do",
	             "const_cast", "dynamic_cast", "extern", "register", "override",
	             "reinterpret_cast", "static_cast", "typeid", "nullptr", ""};

	_types = {"bool", "int", "char", "wchar_t", "short", "long", "void", "size_t",
	          "double", "float", "int8_t", "int16_t", "int32_t", "int64_t",
	          "uint8_t", "uint16_t", "uint32_t", "uint64_t", "ptrdiff_t"};
}

void CppCodeHighlighter::highlightImpl(const String& code)
{
	const char* ch = code.toCString();
	const char* startPtr = ch;
	int pos, startPos;

	for (; *ch; ch++)
	{
		pos = ch - startPtr;

		if (*ch == '"')
		{
			startPos = pos;
			ch++;
			for (; *ch; ch++)
			{
				if (*ch == '"')
				{
					setStyle("string", startPos, ch - startPtr);
					break;
				}
				else if (*ch == '\\')
				{
					setStyle("escapedChar", ch - startPtr, ch - startPtr + 1);
					ch++;
				}
			}
		}
		else if (*ch == '\'')
		{
			startPos = pos;
			ch++;
			for (; *ch; ch++)
			{
				if (*ch == '\'')
				{
					setStyle("char", startPos, ch - startPtr);
					break;
				}
				else if (*ch == '\\')
				{
					setStyle("escapedChar", ch - startPtr, ch - startPtr + 1);
					ch++;
				}
			}
		}
		else if (*ch == '/' && *(ch + 1) == '/')
		{
			while (*(ch++) && *ch != '\n');
			setStyle("commentLine", pos, ch - startPtr - 1);
		}
		else if (*ch == '#')
		{
			const char* ch2 = ch;
			while (*(ch2--) && (*ch2 == ' ' || *ch2 == '\t'));
			if (*ch2 != '\n')
				continue;
			ch = startPtr + code.indexOf("\n", pos);
			setStyle("preprocessor", pos, ch - startPtr - 1);
		}
		else if (*ch == '/' && *(ch + 1) == '*')
		{
			ch += 2;
			bool isDoc = *ch == '*' && *(ch + 1) != '*';
			int endPos = code.indexOf("*/", pos);
			setStyle(isDoc ? "docComment" : "commentBlock", pos, endPos + 1);

			if (isDoc)
			{
				for(; *ch; ch++)
				{
					if (ch - startPtr == endPos)
						break;
					if (*ch == '\\')
					{
						startPos = ch - startPtr;
						while(*(ch++) && *ch >= 'a' && *ch <= 'z');
						setStyle("token", startPos, ch - startPtr - 1);
					}
				}
			}
			else
				ch = startPtr + endPos + 1;
		}
		else if (*ch >= '0' && *ch <= '9')
		{
			if (*(ch - 1) && ( (*(ch - 1) >= 'A' && *(ch - 1) <= 'Z')
			    || (*(ch - 1) >= 'a' && *(ch - 1) <= 'z')
			    || *(ch - 1) == '_' ))
				continue;

			startPos = pos;
			String style = "number";

			if (*ch == '0' && *(ch + 1) && (*(ch + 1) == 'x' || *(ch+1) == 'b'
			    || (*(ch + 1) >= '0' && *(ch + 1) <= '7')))
			{
				if (*(ch + 1) && *(ch + 1) == 'x')
				{
					style += " hex";
					ch++;
					while (*(ch++) && ( (*ch >= '0' && *ch <= '9')
					       || (*ch >= 'a' && *ch <= 'f')
					       || (*ch >= 'A' && *ch <= 'F') ));
					ch--;
				}
				else if (*(ch + 1) && *(ch + 1) == 'b')
				{
					style += " bin";
					ch++;
					while (*(ch++) && (*ch == '0' || *ch == '1'));
					ch--;
				}
				else
				{
					style += " oct";
					ch++;
					while (*(ch++) && *ch >= '0' && *ch <= '7');
					ch--;
				}
			}
			else
			{
				bool point = false;
				for (; *ch; ch++)
				{
					if (*ch == '.')
					{
						if (point)
						{
							ch--;
							break;
						}
						else
							point = true;
					}
					else if (!(*ch >= '0' && *ch <= '9'))
					{
						ch--;
						break;
					}
				}
			}

			setStyle(style, startPos, ch - startPtr);
		}
		else if ((*ch >= 'a' && *ch <= 'z')
		         || (*ch >= 'A' && *ch <= 'Z')
		         || (*ch >= '0' && *ch <= '9')
		         || *ch == '_')
		{
			startPos = pos;
			while (*(ch++) && ((*ch >= 'a' && *ch <= 'z')
			       || (*ch >= 'A' && *ch <= 'Z')
			       || (*ch >= '0' && *ch <= '9')
			       || *ch == '_'));
			ch--;

			String word = code.mid(startPos, ch - startPtr);
			if (_keywords.contains(word))
				setStyle("keyword", startPos, ch - startPtr);
			else if (_types.contains(word))
				setStyle("type", startPos, ch - startPtr);
		}
	}
}
