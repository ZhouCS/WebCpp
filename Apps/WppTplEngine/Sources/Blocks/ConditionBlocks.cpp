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
 * @file Blocks/ConditionBlocks.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-30
 */

#include "Blocks/ConditionBlocks.h"

#include "Expr.h"
#include "CompiledTpl.h"

#include <Exceptions/Templates>

namespace Blocks {

If::If()
  : Block("if", Block::RequiredArgument, Block::HasBody)
{}

If::If(Block* parent)
  : Block(parent, "if"),
    _hasElse(false)
{}

If::~If()
{
	for (Expr* cond : _conditions)
		delete cond;
}

Block* If::newInstance(Block *parent) const
{ return new If(parent); }

void If::setArgument(const String& arg)
{
	_conditions.append(new Expr(this, arg));
}

void If::compiledEvent()
{
	MultiMap<int, Block*> subBlocks = blocks();
	for (MultiMap<int, Block*>::Iterator i(subBlocks); i.hasNext(); i++)
	{
		if (i.value()->name() == "elseif" || i.value()->name() == "else")
		{
			if (_hasElse)
				throw Exceptions::TemplateCompilation(_tpl, String("unexpected block "
			                                                     "\"%1\" after else "
			                                                     "block")
			                                        .format(i.value()->name()));
			_indexes.append(i.key());
			if (i.value()->name() == "else")
				_hasElse = true;
		}
	}
	if (_indexes.count() == 0)
		_indexes.append(-1);
}

String If::render(Template* tpl, int, int)
{
	int start = 0;
	for (int i = 0, c = _conditions.count(); i < c; i++)
	{
		if (_conditions[i]->exec(tpl).toBool())
			return Block::render(tpl, start, _indexes[i]);
		start = _indexes[i];
	}
	if (!_hasElse)
		return "";
	return Block::render(tpl, start);
}

//----------------------------------------------------------------------------//

ElseIf::ElseIf()
  : Block("elseif", Block::RequiredArgument, Block::HasNoBody)
{}

ElseIf::ElseIf(Block* parent)
  : Block(parent, "elseif")
{}

Block* ElseIf::newInstance(Block* parent) const
{ return new ElseIf(parent); }

void ElseIf::setArgument(const String& arg)
{
	dynamic_cast<If*>(_parent)->_conditions.append(new Expr(this, arg));
}

void ElseIf::compiledEvent()
{
	if (_parent->name() != "if")
		throw Exceptions::TemplateCompilation(_tpl,
	                                        String("unexpected \"%1\" parent to "
	                                               "\"elseif\" block, expecting "
	                                               "\"if\" parent")
	                                        .format(_parent->name()));
}

//----------------------------------------------------------------------------//

Else::Else()
  : Block("else", Block::NoArgument, Block::HasNoBody)
{}

Else::Else(Block* parent)
  : Block(parent, "else")
{}

Block* Else::newInstance(Block* parent) const
{ return new Else(parent); }

void Else::compiledEvent()
{
	if (_parent->name() != "if")
		throw Exceptions::TemplateCompilation(_tpl,
	                                        String("unexpected \"%1\" parent to "
	                                               "\"else\" block, expecting "
	                                               "\"if\" parent")
	                                        .format(_parent->name()));
}

} // ns Blocks
