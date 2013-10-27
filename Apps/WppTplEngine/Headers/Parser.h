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
 * @file Parser.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <List>
#include <Stack>

class CompiledTpl;
class Expr;
class Lexem;
class ExprNode;
class Operator;

class Parser
{
public:
	struct Token
	{
		bool      isNode;
		ExprNode* node;

	};

	Parser(Expr* expr, const List<Lexem>& lexems);

	ExprNode* rootExprNode() const;

private:
	void finish();
	void parseOp();
	void parseIdentifier();
	void popRightPar();
	void popRightBracket();
	void popRightBrace();
	String popMapKey();
	void popOp(Operator* op, bool isUnary);
	bool isOperand(int i, bool toRight);
	bool opIsUnary(int i = -1);

private:
	Expr*            _expr;
	CompiledTpl*     _tpl;
	List<Lexem>      _lex;
	int              _i;
	int              _count;
	Stack<ExprNode*> _exprs;
	Stack<Lexem>     _ops;
};

#endif // !_PARSER_H_
