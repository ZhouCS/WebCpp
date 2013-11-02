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
 * @file Blocks/ForBlocks.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-30
 */

#include "Blocks/ForBlocks.h"
#include "CompiledTpl.h"
#include "Expr.h"

#include <Exceptions/Templates>

namespace Blocks {

For::For()
  : Block("for", Block::RequiredArgument, Block::HasBody),
    _value(nullptr)
{}

For::For(Block* parent)
  : Block(parent, "for"),
    _value(nullptr)
{}

For::~For()
{
	if (_value != nullptr)
		delete _value;
}

Block* For::newInstance(Block *parent) const
{ return new For(parent); }

void For::setArgument(const String& arg)
{
	int i = 0;

	skipWhitespaces(arg, &i);
	int origin = i;
	String name;
	while ((arg[i] >= 'a' && arg[i] <= 'z')
	       || (arg[i] >= 'A' && arg[i] <= 'Z')
	       || (i > origin && arg[i] >= '0' && arg[i] <= '9'))
		name += arg[i++];
	if (name.isEmpty())
		throw Exceptions::TemplateCompilation(_tpl, "for: expecting variable name");

	skipWhitespaces(arg, &i);
	if (arg[i] == '-' && arg[i + 1] == '>')
	{
		i += 2;
		skipWhitespaces(arg, &i);
		_keyName = name;
		while ((arg[i] >= 'a' && arg[i] <= 'z')
		       || (arg[i] >= 'A' && arg[i] <= 'Z')
		       || (i > origin && arg[i] >= '0' && arg[i] <= '9'))
			_valueName += arg[i++];
		if (_valueName.isEmpty())
			throw Exceptions::TemplateCompilation(_tpl, "for: expecting variable "
			                                      "name after “->” token");
		skipWhitespaces(arg, &i);
	}
	else
		_valueName = name;

	if (!(arg[i] == 'i' && arg[i + 1] == 'n'
	      && (arg[i + 2] == ' ' || arg[i + 2] == '\t'
	          || arg[i + 2] == '\n' || arg[i + 2] == '\0')))
		throw Exceptions::TemplateCompilation(_tpl, "for: expecting \"in\" "
		                                      "keyword");
	i += 2;
	skipWhitespaces(arg, &i);

	if (arg[i] == '\0')
		throw Exceptions::TemplateCompilation(_tpl, "for: expecting expression");

	_value = new Expr(this, arg.substr(i));
}

String For::render(Template* tpl, int, int)
{
	Variant value = _value->exec(tpl);
	String r;

	if (value.type() == Variant::Type::List)
	{
		List<Variant> list = value.toList();
		for (int i = 0, c = list.count(); i < c; i++)
		{
			if (!_keyName.isNull())
				_vars[_keyName] = i;
			_vars[_valueName] = list[i];
			r += Block::render(tpl);
		}
	}
	else if (value.type() == Variant::Type::Map)
	{
		Map<String, Variant> map = value.toMap();
		for (Map<String, Variant>::Iterator i(map); i.hasNext(); i++)
		{
			if (!_keyName.isNull())
				_vars[_keyName] = i.key();
			_vars[_valueName] = i.value();
			r += Block::render(tpl);
		}
	}
	else if (value.type() == Variant::Type::String)
	{
		String str = value.toString();
		for (int i = 0, s = str.size(); i < s; i++)
		{
			if (!_keyName.isNull())
				_vars[_keyName] = i;
			_vars[_valueName] = String(str[i]);
			r += Block::render(tpl);
		}
	}
	else
		throw Exceptions::TemplateCompilation(_tpl, String("cannot execute for "
		                                                   "loop on type \"%1\"")
		                                      .format(value.typeString()));
	return r;
}

void For::skipWhitespaces(const String& arg, int* i)
{
	while (arg[*i] == ' ' || arg[*i] == '\t' || arg[*i] == '\n')
		(*i)++;
}

//----------------------------------------------------------------------------//

Empty::Empty()
  : Block("empty", Block::NoArgument, Block::HasNoBody)
{}

Empty::Empty(Block* parent)
  : Block(parent, "empty")
{}

Block* Empty::newInstance(Block *parent) const
{ return new Empty(parent); }

} // ns Blocks
