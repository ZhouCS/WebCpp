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
 * @file CompiledTpl.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#include "CompiledTpl.h"
#include "Block.h"

#include <File>

CompiledTpl::CompiledTpl(const Path& filePath)
  : AbstractCompiledTemplate(filePath),
    _rootBlock(nullptr)
{
	Block* root = new Block(this, File::getContent(filePath));
	if (_rootBlock == nullptr)
		_rootBlock = root;
}

String CompiledTpl::render(Template* tpl)
{
	return _rootBlock->render(tpl);
}

//----------------------------------------------------------------------------//

Block* CompiledTpl::rootBlock() const
{ return _rootBlock; }

void CompiledTpl::setRootBlock(Block* rootBlock)
{ _rootBlock = rootBlock; }
