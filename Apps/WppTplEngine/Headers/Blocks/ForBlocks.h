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
 * @file Blocks/ForBlocks.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-30
 */

#ifndef _BLOCKS_FORBLOCKS_H_
#define _BLOCKS_FORBLOCKS_H_

#include "Block.h"

namespace Blocks {

class For : public Block
{
public:
	For();
	For(Block* parent);

	virtual Block* newInstance(Block* parent) const override;
	virtual void   setArgument(const String& arg) override;
	virtual String render(Template* tpl, int, int) override;

private:
	String _keyName;
	String _valueName;
	Expr*  _value;

private:
	void skipWhitespaces(const String& arg, int* i);
};

//----------------------------------------------------------------------------//

class Empty : public Block
{
public:
	Empty();
	Empty(Block* parent);

	virtual Block* newInstance(Block* parent) const override;
};

} // ns Blocks

#endif // !_BLOCKS_FORBLOCKS_H_
