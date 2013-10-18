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
 * @file Blocks/ConditionBlocks.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-30
 */

#ifndef _BLOCKS_CONDITIONBLOCKS_H_
#define _BLOCKS_CONDITIONBLOCKS_H_

#include "Block.h"

namespace Blocks {

class If : public Block
{
	friend class ElseIf;
public:
	If();
	If(Block* parent);
	virtual ~If();

	virtual Block* newInstance(Block* parent) const override;
	virtual void setArgument(const String& arg) override;
	virtual void compiledEvent() override;
	virtual String render(Template* tpl, int, int) override;

private:
	List<Expr*> _conditions;
	List<int>   _indexes;
	bool        _hasElse;
};

//----------------------------------------------------------------------------//

class ElseIf : public Block
{
public:
	ElseIf();
	ElseIf(Block* parent);

	virtual Block* newInstance(Block* parent) const override;
	virtual void setArgument(const String& arg) override;
	virtual void compiledEvent() override;
};

//----------------------------------------------------------------------------//

class Else : public Block
{
public:
	Else();
	Else(Block* parent);

	virtual Block* newInstance(Block* parent) const override;
	virtual void compiledEvent() override;
};

} // ns Blocks

#endif // !_BLOCKS_CONDITIONBLOCKS_H_
