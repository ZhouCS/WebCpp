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
 * @file Expr.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#include "Expr.h"
#include "ExprNode.h"
#include "Block.h"
#include "Lexer.h"
#include "Parser.h"

#include <Template>
#include <Request>

Expr::Expr(Block* parent, const String& src)
  : _parent(parent),
    _src(src)
{
	Lexer lexer(_parent->tpl(), _src);
	//for (Lexem lexem : lexer.lexems()) lexem.dump();
	Parser parser(this, lexer.lexems());
	_root = parser.rootExprNode();
	//std::cout << std::endl;
	//dumpAst();
}

Variant Expr::exec(Template* tpl)
{
	return _root->exec(tpl);
}

String Expr::render(Template* tpl)
{
	return exec(tpl).htmlRender(tpl->request()->locale());
}

void Expr::dumpAst() const
{
	dumpAstNode(_root, 0);
}

void Expr::dumpAstNode(ExprNode* node, int level) const
{
	String indent;
	int i = 0;
	ExprNode* curNode = node;
	while (i < level)
	{
		if (i == 0)
			indent = (node == curNode->parent()->subNodes().last() ? " └─" : " ├─")
			         + indent;
		else
		{
			curNode = curNode->parent();
			indent = (curNode == curNode->parent()->subNodes().last() ? "   " : " │ ")
			         + indent;
		}
		i++;
	}
	std::cout << indent << node->dump() << std::endl;
	for (ExprNode* subNode : node->subNodes())
		dumpAstNode(subNode, level + 1);
}

Block* Expr::block() const
{ return _parent; }
