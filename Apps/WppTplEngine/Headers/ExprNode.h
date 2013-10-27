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
 * @file ExprNode.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-08
 */

#ifndef _WPP_EXPRNODE_H_
#define _WPP_EXPRNODE_H_

#include "Function.h"

#include <Variant>
#include <List>
#include <String>

class Expr;
class Template;
class CompiledTpl;
class Operator;

class ExprNode
{
public:
	ExprNode(Expr* expr);
	virtual ~ExprNode();

	virtual Variant exec(Template* tpl) = 0;
	virtual String dump() const = 0;

	void addSubNode(ExprNode* node);

	ExprNode*       parent() const;
	List<ExprNode*> subNodes() const;

protected:
	CompiledTpl*    _tpl;
	Expr*           _expr;
	ExprNode*       _parent;
	List<ExprNode*> _subNodes;
};

//----------------------------------------------------------------------------//

class LiteralNode : public ExprNode
{
public:
	LiteralNode(Expr* expr, const Variant& value);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;

public: //FIX
	Variant _value;
};

//----------------------------------------------------------------------------//

class OpNode : public ExprNode
{
public:
	OpNode(Expr* expr, Operator* op);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;

private:
	Operator* _op;
};

//----------------------------------------------------------------------------//

class VarNode : public ExprNode
{
public:
	VarNode(Expr* expr, const String& varName);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;

	String varName() const;

private:
	String _varName;
};

//----------------------------------------------------------------------------//

class FuncNode : public ExprNode
{
public:
	FuncNode(Expr* expr, const String& name, bool isFilter);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;

	Function func() const;

private:
	String   _name;
	Function _func;
	bool     _isFilter;
};

//----------------------------------------------------------------------------//

class IndexNode : public ExprNode
{
public:
	IndexNode(Expr* expr);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;
};

//----------------------------------------------------------------------------//

class ListNode : public ExprNode
{
public:
	ListNode(Expr* expr);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;
};

//----------------------------------------------------------------------------//

class MapNode : public ExprNode
{
public:
	MapNode(Expr* expr, const StringList& keys);

	virtual Variant exec(Template* tpl) override;
	virtual String dump() const override;

private:
	StringList _keys;
};

#endif // !_WPP_EXPRNODE_H_
