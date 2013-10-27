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
 * @file Expr.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#ifndef _WPP_EXPR_H_
#define _WPP_EXPR_H_

#include <List>

class Block;
class String;
class Variant;
class Template;
class ExprNode;

class Expr
{
public:
	Expr(Block* parent, const String& src);

	Variant exec(Template* tpl);
	String  render(Template* tpl);

	void   dumpAst() const;
	Block* block() const;

private:
	void dumpAstNode(ExprNode* node, int level) const;

private:
	Block*    _parent;
	String    _src;
	ExprNode* _root;
};

#endif // !_WPP_EXPR_H_
