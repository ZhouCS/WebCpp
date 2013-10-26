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
 * @file Block.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#include "Block.h"
#include "CompiledTpl.h"
#include "Expr.h"

#include "Blocks/ConditionBlocks.h"
#include "Blocks/ForBlocks.h"
#include "Blocks/InheritanceBlocks.h"

#include <Exceptions/Templates>

#include <iostream>

typedef Exceptions::TemplateCompilation ECompile;

Map<String, Block*> Block::_blocks;

Block::Block(const String& name, ArgumentPolicy argPolicy, HasBodyBool hasBody)
  : _argPolicy(argPolicy),
    _hasBody(static_cast<bool>(hasBody)),
    _tpl(nullptr),
    _parent(nullptr),
    _name(name)
{}

Block::Block(Block* parent, const String& name)
  : _tpl(parent->_tpl),
    _parent(parent),
    _name(name)
{}

Block::Block(CompiledTpl* tpl,
             const String& src,
             Block* parent,
             const String& name)
  : _tpl(tpl),
    _parent(parent),
    _name(name),
    _src(src),
    _innerStart(0),
    _outerStart(0)
{
	int i = 0;
	Stack<Block*> blocks;

	blocks.push(this);
	while (_src[i] != '\0')
	{
		while (_src[i] != '\0' && _src[i] != '{')
			i++;
		if (_src[i] != '\0' && !isEscaped(&i))
		{
			bool isBlock = _src[i + 1] == '{';
			if (isBlock)
				parseBlock(&i, &blocks);
			else
			{
				int exprLen = exprLength(false, i + 1);
				if (exprLen < 0)
					throw ECompile(_tpl, "unexpected end of template, expecting end of"
				                 "expression");
				else if (exprLen == 0)
					throw ECompile(_tpl, "empty expression");
				blocks.top()->_vals.insert(i - blocks.top()->_innerStart,
				                           Value(new Expr(blocks.top(),
				                            _src.substr(i + 1, exprLen))));
				_src = _src.replace(i, i + exprLen + 1, "");
			}
		}
		else if (_src[i] != '\0')
			i++;
	}

	if (blocks.count() > 1)
	{
		Block* block = blocks.pop();
		throw ECompile(_tpl, String("unexpected end of template, expecting closing "
		                            "of block “%1”").format(block->name()));
	}
}

Block::~Block()
{
	for (MultiMap<int, Value>::Iterator i(_vals); i.hasNext(); i++)
	{
		if (i.value().block != nullptr)
			delete i.value().block;
		else
			delete i.value().expr;
	}
}

bool Block::isEscaped(int* i)
{
	int count = 0, origin = *i;
	while (*i > 0 && _src[--(*i)] == '\\')
		count++;
	_src = _src.replace(origin - (count - count / 2), origin - 1, "");
	*i = origin - (count - count / 2);
	return count % 2 > 0;
}

void Block::parseBlock(int* i, Stack<Block*>* blocks)
{
	String name, arg;
	int origin = *i; // origin = ...<{>{...

	*i += 2;
	skipWhitespaces(i);
	if (_src[*i] == '/')
	{
		closeBlock(i, blocks);
		return;
	}

	while (_src[*i] != '\0' && _src[*i] != ' ' && _src[*i] != '\t'
	       && _src[*i] != '\n' && _src[*i] != '}')
	{
		name += _src[*i];
		(*i)++;
	}

	if (name.isEmpty())
		throw ECompile(_tpl, "expected block name");
	else if (_src[*i] == '\0')
		throw ECompile(_tpl, String("unexpected end of template after "
	                              "block name “%1”").format(name));
	Block* blockId = _blocks.get(name, nullptr);
	if (blockId == nullptr)
		throw ECompile(_tpl, String("unknown block “%1”").format(name));

	skipWhitespaces(i);
	int argLen = exprLength(true, *i);
	if (argLen < 0)
		throw ECompile(_tpl, "unexpected end of template, expecting end of block");
	arg = _src.substr(*i, argLen);
	*i += argLen + 2; // }}[.]..

	if (blockId->_argPolicy == RequiredArgument && arg.isEmpty())
		throw ECompile(_tpl, String("expected argument to block “%1”")
	                 .format(name));
	else if (blockId->_argPolicy == NoArgument && !arg.isEmpty())
		throw ECompile(_tpl, String("unexpected argument to block “%1”")
	                 .format(name));

	Block* block = blockId->newInstance(blocks->top());
	block->setArgument(arg);

	if (blockId->_hasBody)
	{
		block->_outerStart = blockSourceIndex(origin - 1, *i, true);
		block->_innerStart = blockSourceIndex(origin - 1, *i, false) + 1;
		blocks->push(block);
	}
	else
	{
		_src = _src.replace(origin, *i - 1, "");
		blocks->top()->_vals.insert(origin - blocks->top()->_innerStart,
		                            Value(block));
		*i = origin;
	}
}

void Block::closeBlock(int* i, Stack<Block*>* blocks)
{
	(*i)++;
	int argLen = exprLength(true, *i);
	if (argLen < 0)
		throw ECompile(_tpl, "unexpected end of template, expecting block "
	                 "close name");
	else if (argLen == 0)
		throw ECompile(_tpl, "expected block closing name");
	String name = _src.substr(*i, argLen).trim();

	Block* toClose = blocks->top();
	blocks->pop();
	if (toClose->_name != name)
		throw ECompile(_tpl, String("block closing mismatch: unexpected “%1” "
	                              "closing, expected “%2” closing")
	                 .format(name, toClose->_name));
	toClose->_innerEnd = blockSourceIndex(*i - 4, *i + argLen + 2, true) - 1;
	toClose->_outerEnd = blockSourceIndex(*i - 4, *i + argLen + 2, false);

	toClose->_src = _src.mid(toClose->_innerStart, toClose->_innerEnd);
	_src = _src.replace(toClose->_outerStart, toClose->_outerEnd, "");
	*i = toClose->_outerStart;
	blocks->top()->_vals.insert(*i - blocks->top()->_innerStart, Value(toClose));
	toClose->compiledEvent();
}

int Block::blockSourceIndex(int left, int right, bool wantLeft)
{
	int i = left;
	while (i > 0 && (_src[i] == ' ' || _src[i] == '\t'))
		i--;
	if (i > 0 && _src[i] != '\n')
		return wantLeft ? left + 1 : right - 1;
	i = right;
	while (_src[i] != '\0' && (_src[i] == ' ' || _src[i] == '\t'))
		i++;
	if (_src[i] != '\0' && _src[i] != '\n')
		return wantLeft ? left + 1 : right - 1;
	if (wantLeft)
	{
		i = left;
		while (i > 0 && (_src[i] == ' ' || _src[i] == '\t'))
			i--;
		return i == 0 ? 0 : i + 1;
	}
	else
	{
		i = right;
		while (_src[i] != '\0' && (_src[i] == ' ' || _src[i] == '\t'))
			i++;
		return _src[i] == '\0' ? i - 1 : i;
	}
}

int Block::exprLength(bool blockArg, int i) // FIXME: {{if {bar[}}]}
{
	int braces = 0;

	int origin = i;
	while (_src[i] != '\0')
	{
		if (_src[i] == '{' && (!blockArg || _src[i + 1] == '{'))
		{
			braces++;
			i++;
		}
		else if (_src[i] == '}' && (!blockArg || _src[i + 1] == '}'))
		{
			if (--braces < 0)
				return i - origin;
			i++;
		}
		else if (_src[i] == '\'')
			skipString(&i);
		else
			i++;
	}
	return -1;
}

void Block::skipString(int* i)
{
	(*i)++;
	while (_src[*i] != '\0')
	{
		if (_src[*i] == '\\' && _src[*i + 1] != '\0')
			(*i)++;
		else if (_src[*i] == '\'')
		{
			(*i)++;
			return;
		}
		(*i)++;
	}
	if (_src[*i] == '\0')
		throw ECompile(_tpl, "unexpected end of template, expecting end of string");
}

void Block::skipWhitespaces(int* i)
{
	while (_src[*i] == ' ' || _src[*i] == '\t' || _src[*i] == '\n')
		(*i)++;
}

//----------------------------------------------------------------------------//

String Block::render(Template* tpl, int from, int end)
{
	if (end == -1)
		end = _src.size();
	String src = _src.mid(from, end - 1);
	int offset = -from;

	for (MultiMap<int, Value>::Iterator i(_vals); i.hasNext(); i++)
	{
		if (i.key() < from)
			continue;
		if (i.key() > end)
			break;
		String render = i.value().block == nullptr
		                ? i.value().expr->render(tpl)
		                : i.value().block->render(tpl);
		src = src.insert(i.key() + offset, render);
		offset += render.size();
	}
	return src;
}

void Block::registerBlock(Block* block)
{
	_blocks[block->name()] = block;
}

void Block::registerBuiltins()
{
	registerBlock(new Blocks::If);
	registerBlock(new Blocks::ElseIf);
	registerBlock(new Blocks::Else);
	registerBlock(new Blocks::For);
	registerBlock(new Blocks::Empty);
	registerBlock(new Blocks::Inherit);
	registerBlock(new Blocks::InheritBlock);
}

void Block::deleteBlocks()
{
	for (Map<String, Block*>::Iterator i(_blocks); i.hasNext(); i++)
		delete i.value();
}

Block* Block::newInstance(Block*) const
{ return nullptr; }

void Block::setArgument(const String&)
{}

void Block::compiledEvent()
{}

//----------------------------------------------------------------------------//

String Block::name() const
{ return _name; }

CompiledTpl* Block::tpl() const
{ return _tpl; }

MultiMap<int, Block*> Block::blocks() const
{
	MultiMap<int, Block*> r;
	for (MultiMap<int, Value>::Iterator i(_vals); i.hasNext(); i++)
	{
		if (i.value().block != nullptr)
			r.insert(i.key(), i.value().block);
	}
	return r;
}

Variant Block::var(Template* tpl, const String& name) const
{
	if (_vars.hasKey(name))
		return _vars[name];
	if (_parent != nullptr)
		return _parent->var(tpl, name);
	if (!tpl->hasVar(name))
		throw 42; // FIX ME
	return tpl->get(name);
}
