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
 * @file Parser.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#include "Parser.h"
#include "Lexer.h"
#include "Operator.h"
#include "CompiledTpl.h"
#include "Block.h"
#include "Expr.h"
#include "ExprNode.h"

#include <Exceptions/Templates>

typedef Exceptions::TemplateCompilation ECompile;

Parser::Parser(Expr* expr, const List<Lexem>& lexems)
  : _expr(expr),
    _tpl(expr->block()->tpl()),
    _lex(lexems),
    _i(0),
    _count(lexems.count())
{
	try
	{
		while (_i < _count)
		{
			if (isOperand(_i, true) && _lex[_i].type != Lexem::OperatorToken
			    && _i > 0 && isOperand(_i - 1, false)
			    && !(_i > 0 && (_lex[_i].type == Lexem::LeftParToken
			                    || _lex[_i].type == Lexem::LeftBracketToken)
			         && (_lex[_i - 1].type == Lexem::IdentifierToken
			             || _lex[_i - 1].type == Lexem::RightBracketToken
			             || _lex[_i - 1].type == Lexem::RightBraceToken)))
				throw ECompile(_tpl, String("unexpected %1 token after %2 token")
				               .format(_lex[_i].typeString(),
				                       _lex[_i - 1].typeString()));
			else if ((_lex[_i].type == Lexem::PipeToken
			          || _lex[_i].type == Lexem::PeriodToken) && _i == _count - 1)
				throw ECompile(_tpl, String("unexpected end of expression after token "
			                              "“%1”, expecting identifier token")
			                 .format(_lex[_i].typeString()));
			else if ((_lex[_i].type == Lexem::PipeToken
			          || _lex[_i].type == Lexem::PeriodToken)
			         && _lex[_i + 1].type != Lexem::IdentifierToken)
				throw ECompile(_tpl, String("unexpected token \"%1\" after token "
				                            "“%2”, expecting identifier token")
				                     .format(_lex[_i + 1].typeString(),
				                             _lex[_i].typeString()));

			if (_lex[_i].type == Lexem::LiteralToken)
				_exprs.push(new LiteralNode(_expr, _lex[_i++].literal));
			else if (_lex[_i].type == Lexem::LeftParToken
			         || _lex[_i].type == Lexem::LeftBracketToken
			         || _lex[_i].type == Lexem::LeftBraceToken
			         || _lex[_i].type == Lexem::CommaToken
			         || _lex[_i].type == Lexem::PipeToken
			         || _lex[_i].type == Lexem::PeriodToken
			         || _lex[_i].type == Lexem::ColonToken)
				_ops.push(_lex[_i++]);
			else if (_lex[_i].type == Lexem::OperatorToken)
				parseOp();
			else if (_lex[_i].type == Lexem::IdentifierToken)
				parseIdentifier();
			else if (_lex[_i].type == Lexem::RightParToken)
				popRightPar();
			else if (_lex[_i].type == Lexem::RightBracketToken)
				popRightBracket();
			else if (_lex[_i].type == Lexem::RightBraceToken)
				popRightBrace();
			else
				throw ECompile(_tpl, String("unexpected token “%1”")
				               .format(_lex[_i].typeString()));
		}
		finish();
	}
	catch (...)
	{
		while (!_exprs.isEmpty())
			delete _exprs.pop();
		throw;
	}
}

void Parser::finish()
{
	while (!_ops.isEmpty())
	{
		if (_ops.top().type == Lexem::LeftParToken)
			throw ECompile(_tpl, "unexpected end of expression, expecting closing "
										 "parenthesis");
		else if (_ops.top().type == Lexem::LeftBracketToken)
			throw ECompile(_tpl, "unexpected end of expression, expecting closing "
										 "bracket");
		else if (_ops.top().type == Lexem::LeftBraceToken)
			throw ECompile(_tpl, "unexpected end of expression, expecting closing "
										 "brace");
		else if (_ops.top().type != Lexem::OperatorToken)
			throw Exceptions::InternalError(String("tpl parser: unknown remaining "
			                                       "token “%1”")
			                                .format(_ops.top().typeString()));
		popOp(_ops.top().op, _ops.top().opIsUnary);
		_ops.pop();
	}
}

void Parser::parseOp()
{
	Operator* op = _lex[_i].op;
	_lex[_i].opIsUnary = opIsUnary();

	if (!op->isUnary() && (_i == 0 || !isOperand(_i - 1, false)))
		throw ECompile(_tpl, String("unexpected binary operator “%1” (‘%2’), "
		                            "expecting operand").format(op->name(),
		                                                        op->token()));
	else if (op->isUnary() && !op->isRightAssociative(true)
	         && (_i == 0 || !isOperand(_i - 1, false)))
		throw ECompile(_tpl, String("unexpected unary operator “%1” (‘%2’), "
		                            "expecting operand").format(op->name(),
		                                                        op->token()));
	else if (!_lex[_i].opIsUnary && _i == _count - 1)
		throw ECompile(_tpl, String("unexpected end of expression after binary "
		                            "operator “%1” (‘%2’), expecting operand")
		               .format(op->name(), op->token()));
	else if (_lex[_i].opIsUnary && op->isRightAssociative(true)
	         && _i == _count - 1)
		throw ECompile(_tpl, String("unexpected end of expression, expecting "
		                            "operand after unary operator “%1” (‘%2’)")
		               .format(op->name(), op->token()));
	else if (_lex[_i].opIsUnary && op->isRightAssociative(true)
	         && _i > 0 && isOperand(_i - 1, false))
		throw ECompile(_tpl, String("unexpected unary operator “%1” (‘%2’) after "
		                            "operand").format(op->name(), op->token()));

	while (!_ops.isEmpty() && _ops.top().type == Lexem::OperatorToken
	       && (op->precedence(_lex[_i].opIsUnary)
	           < _ops.top().op->precedence(_ops.top().opIsUnary)
	           || (!op->isRightAssociative(_lex[_i].opIsUnary)
	               && op->precedence(_lex[_i].opIsUnary)
	               == _ops.top().op->precedence(_ops.top().opIsUnary))))
	{
		popOp(_ops.top().op, _ops.top().opIsUnary);
		_ops.pop();
	}
	_ops.push(_lex[_i++]);
}

void Parser::parseIdentifier()
{
	if (!_ops.isEmpty() && _ops.top().type == Lexem::PipeToken
	    && (_i == _count - 1 || _lex[_i + 1].type != Lexem::LeftParToken))
	{
		FuncNode* node = new FuncNode(_expr, _lex[_i].identifier, true);
		node->addSubNode(_exprs.pop());
		_exprs.push(node);
		_ops.pop();
		_i++;
	}
	else if (!_ops.isEmpty() && _ops.top().type == Lexem::PeriodToken)
	{
		IndexNode* node = new IndexNode(_expr);
		node->addSubNode(_exprs.pop());
		node->addSubNode(new LiteralNode(_expr, _lex[_i].identifier));
		_exprs.push(node);
		_ops.pop();
		_i++;
	}
	else
		_exprs.push(new VarNode(_expr, _lex[_i++].identifier));
}

void Parser::popRightPar()
{
	Stack<ExprNode*> nodes;

	while (!_ops.isEmpty() && _ops.top().type != Lexem::LeftParToken)
	{
		if (_ops.top().type == Lexem::CommaToken)
		{
			nodes.push(_exprs.pop());
			_ops.pop();
			continue;
		}
		else if (_ops.top().type != Lexem::OperatorToken)
			throw Exceptions::InternalError("dunno what to do");
		popOp(_ops.top().op, _ops.top().opIsUnary);
		_ops.pop();
	}
	if (_ops.isEmpty())
		throw ECompile(_tpl, "unexpected closing parenthesis");
	_ops.pop();

	nodes.push(_exprs.pop());

	if (!_exprs.isEmpty() && typeid (*_exprs.top()) == typeid (VarNode))
	{
		String funcName = dynamic_cast<VarNode*>(_exprs.top())->varName();
		delete _exprs.pop();
		bool isFilter = !_ops.isEmpty() && _ops.top().type == Lexem::PipeToken;
		FuncNode* funcNode = new FuncNode(_expr, funcName, isFilter);

		if (isFilter)
		{
			funcNode->addSubNode(_exprs.pop());
			_ops.pop();
		}
		while (!nodes.isEmpty())
			funcNode->addSubNode(nodes.pop());
		_exprs.push(funcNode);
	}
	else if (nodes.count() > 1)
		throw ECompile(_tpl, "unexpected function parameters, expecting function "
		               "name");
	else
		_exprs.push(nodes.top());
	_i++;
}

void Parser::popRightBracket()
{
	Stack<ExprNode*> nodes;

	while (!_ops.isEmpty() && _ops.top().type != Lexem::LeftBracketToken)
	{
		if (_ops.top().type == Lexem::CommaToken)
		{
			nodes.push(_exprs.pop());
			_ops.pop();
			continue;
		}
		else if (_ops.top().type != Lexem::OperatorToken)
			throw Exceptions::InternalError("dunno what to do");
		popOp(_ops.top().op, _ops.top().opIsUnary);
		_ops.pop();
	}
	if (_ops.isEmpty())
		throw ECompile(_tpl, "unexpected closing bracket");
	_ops.pop();
	nodes.push(_exprs.pop());

	if (nodes.count() > 1)
	{
		//if (_i > 0 && _lex[_i - 1].type == Lexem::IdentifierToken)
		//	throw ECompile(_tpl, "unexpected literal list after identifier token");
		/*if (_i > 0 && isOperand(_i - 1, false))
			throw ECompile(_tpl, String("unexpected literal list after token \"%1\"")
		                 .format(_lex[_i - 1].typeString()));*/

		ListNode* node = new ListNode(_expr);
		while (!nodes.isEmpty())
			node->addSubNode(nodes.pop());
		_exprs.push(node);
	}
	else
	{
		IndexNode* node = new IndexNode(_expr);
		node->addSubNode(_exprs.pop());
		node->addSubNode(nodes.top());
		_exprs.push(node);
	}
	_i++;
}

void Parser::popRightBrace()
{
	Stack<ExprNode*> nodes;
	StringList keys;

	while (!_ops.isEmpty() && _ops.top().type != Lexem::LeftBraceToken)
	{
		if (_ops.top().type == Lexem::CommaToken)
		{
			_ops.pop();
			keys.prepend(popMapKey());
			continue;
		}
		else if (_ops.top().type == Lexem::ColonToken)
		{
			nodes.push(_exprs.pop());
			_ops.pop();
			continue;
		}
		else if (_ops.top().type != Lexem::OperatorToken)
			throw Exceptions::InternalError("tpl parser: popRightBrace: unknown "
		                                  "token");
		popOp(_ops.top().op, _ops.top().opIsUnary);
		_ops.pop();
	}
	if (_ops.isEmpty())
		throw ECompile(_tpl, "unexpected closing brace");
	_ops.pop();
	keys.prepend(popMapKey());

	MapNode* node = new MapNode(_expr, keys);
	while (!nodes.isEmpty())
		node->addSubNode(nodes.pop());
	_exprs.push(node);
	_i++;
}

String Parser::popMapKey()
{
	if (typeid (*_exprs.top()) != typeid (VarNode))
		throw ECompile(_tpl, "expected identifier as map key");
	/*else if (_ops.top().type != Lexem::CommaToken
	         && _ops.top().type != Lexem::LeftBraceToken)
		throw ECompile(_tpl, String("unexpected token \"%1\" before key "
	                              "identifier")
	                 .format(_ops.top().typeString()));*/
	String key = dynamic_cast<VarNode*>(_exprs.top())->varName();
	delete _exprs.pop();
	return key;
}

void Parser::popOp(Operator* op, bool isUnary)
{
	OpNode* node = new OpNode(_expr, op);
	if (isUnary)
		node->addSubNode(_exprs.pop());
	else
	{
		ExprNode* right = _exprs.pop();
		node->addSubNode(_exprs.pop());
		node->addSubNode(right);
	}
	_exprs.push(node);
}

bool Parser::isOperand(int i, bool toRight)
{
	if (_lex[i].type == Lexem::LiteralToken
	    || _lex[i].type == Lexem::IdentifierToken)
		return true;
	if (toRight && (_lex[i].type == Lexem::LeftParToken
	                || _lex[i].type == Lexem::LeftBracketToken
	                || _lex[i].type == Lexem::LeftBraceToken))
		return true;
	if (!toRight && (_lex[i].type == Lexem::RightParToken
	                 || _lex[i].type == Lexem::RightBracketToken
	                 || _lex[i].type == Lexem::RightBraceToken))
		return true;
	if (_lex[i].type == Lexem::OperatorToken
	    && _lex[i].opIsUnary
	    && !_lex[i].op->isRightAssociative(true))
		return true;
	return false;
}

bool Parser::opIsUnary()
{
	Operator* op = _lex[_i].op;
	if (!op->isUnary())
		return false;
	if (!op->isBinary())
		return true;
	return (op->isRightAssociative(true) && (_i == 0
	                                         || !isOperand(_i - 1, false)))
	    || (!op->isRightAssociative(true) && (_i == _count - 1
	                                          || !isOperand(_i + 1, true)));
}

ExprNode* Parser::rootExprNode() const
{ return _exprs.top(); }
