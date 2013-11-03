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
 * @file Blocks/InheritanceBlocks.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-12
 */

#include "Blocks/InheritanceBlocks.h"
#include "CompiledTpl.h"
#include "WppTplEngine.h"

#include <MVC/Templates/TemplatesManager.h>

#include <Exceptions/Templates>

typedef Exceptions::TemplateCompilation ECompile;

namespace Blocks {

Inherit::Inherit()
  : Block("inherit", Block::RequiredArgument, Block::HasNoBody)
{}

Inherit::Inherit(Block* parent)
  : Block(parent, "inherit"),
    _base(nullptr)
{}

Inherit::~Inherit()
{
	for (Block* block : _inheritBlocks.values())
		delete block;
}

Block* Inherit::newInstance(Block *parent) const
{ return new Inherit(parent); }

void Inherit::setArgument(const String& arg)
{
	String path = Path(Template::resolveName(arg, nullptr)).absolutePath();
	_base = dynamic_cast<CompiledTpl*>(TemplatesManager::compiledTemplate(path,
	                                   TemplatesManager::engineByName("WppTpl")));
	if (_base == nullptr)
	{
		throw ECompile(_tpl, String("template “%1” not found for inheritance")
		                     .format(arg));
	}
	_tpl->addDependency(_base);
}

void Inherit::compiledEvent()
{
	if (!_parent->name().isEmpty())
	{
		throw ECompile(_tpl, "“inherit” block can only be a direct child of the "
		                     "root block");
	}
	if (_parent->exprs().count() > 0)
	{
		throw ECompile(_tpl, "unexpected expression between blocks for template "
		                     "inheritance");
	}
	bool found = false;
	for (Block* block : _parent->blocks().values())
	{
		if (block->name() != "block" && block->name() != "inherit")
		{
			throw ECompile(_tpl, String("unexpected block “%1” between blocks for "
			                            "template inheritance")
			                     .format(block->name()));
		}
		else if (block->name() == "inherit" && found)
			throw ECompile(_tpl, "“inherit” must be the template's first block");
		else if (block->name() == "block")
		{
			InheritBlock* subBlock = dynamic_cast<InheritBlock*>(block);
			_inheritBlocks[subBlock->inheritName()] = subBlock;
		}
		found = true;
	}
	if (!_parent->staticContent().trim().isEmpty())
	{
		throw ECompile(_tpl, "unexpected content between blocks for template "
		                     "inheritance");
	}

	_parent->vals().clear();
	_parent = nullptr;
	_tpl->setRootBlock(this);
}

String Inherit::render(Template* tpl, int, int)
{
	return _base->render(tpl);
}

//---------------------------------//

CompiledTpl* Inherit::base() const
{ return _base; }

Block* Inherit::inheritBlock(const String& name) const
{ return _inheritBlocks.get(name, nullptr); }

//----------------------------------------------------------------------------//

InheritBlock::InheritBlock()
  : Block("block", Block::RequiredArgument, Block::HasBody)
{}

InheritBlock::InheritBlock(Block* parent)
  : Block(parent, "block")
{}

Block* InheritBlock::newInstance(Block* parent) const
{ return new InheritBlock(parent); }

void InheritBlock::setArgument(const String& arg)
{
	if (!arg.match("^[a-zA-Z0-9-_]+$"))
	{
		throw ECompile(_tpl, String("invalid inheritance block name “%1”")
	                       .format(arg));
	}
	_inheritName = arg;
}

void InheritBlock::compiledEvent()
{
	if (_tpl->rootBlock() != nullptr && _tpl->rootBlock()->name() == "inherit")
		_parent = nullptr;
}

String InheritBlock::render(Template* tpl, int, int)
{
	CompiledTpl* compiled = dynamic_cast<CompiledTpl*>(tpl->compiledTpl());
	while (compiled->rootBlock()->name() == "inherit")
	{
		Inherit* root = dynamic_cast<Inherit*>(compiled->rootBlock());
		Block* block = root->inheritBlock(_inheritName);
		if (block != nullptr)
			return block->Block::render(tpl);
		compiled = root->base();
	}
	return Block::render(tpl);
}

//---------------------------------//

String InheritBlock::inheritName() const
{ return _inheritName; }

} // ns Blocks
