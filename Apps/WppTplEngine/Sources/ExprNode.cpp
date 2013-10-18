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
 * @file ExprNode.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#include "ExprNode.h"
#include "Expr.h"
#include "Block.h"
#include "Operator.h"
#include "CompiledTpl.h"

#include <Template>

#include <Exceptions/Templates>

ExprNode::ExprNode(Expr *expr)
  : _tpl(expr->block()->tpl()),
    _expr(expr),
    _parent(nullptr)
{}

ExprNode::~ExprNode()
{
	for (ExprNode* node : _subNodes)
		delete node;
}

void ExprNode::addSubNode(ExprNode* node)
{
	node->_parent = this;
	_subNodes.append(node);
}

ExprNode* ExprNode::parent() const
{ return _parent; }

List<ExprNode*> ExprNode::subNodes() const
{ return _subNodes; }

//----------------------------------------------------------------------------//

LiteralNode::LiteralNode(Expr* expr, const Variant& value)
  : ExprNode(expr),
    _value(value)
{}

Variant LiteralNode::exec(Template*)
{
	return _value;
}

String LiteralNode::dump() const
{
	return "[Literal] " + _value.typeString() + " = " + _value.toString();
}

//----------------------------------------------------------------------------//

OpNode::OpNode(Expr* expr, Operator* op)
  : ExprNode(expr),
    _op(op)
{}

Variant OpNode::exec(Template* tpl)
{
	List<Variant> args;
	for (ExprNode* node : _subNodes)
		args.append(node->exec(tpl));
	return _op->exec(args);
}

String OpNode::dump() const
{
	return "[Operator] " + _op->token() + " (" + _op->name() + ")";
}

//----------------------------------------------------------------------------//

VarNode::VarNode(Expr* expr, const String& varName)
  : ExprNode(expr),
    _varName(varName)
{}

Variant VarNode::exec(Template* tpl)
{
	return _expr->block()->var(tpl, _varName);
}

String VarNode::dump() const
{
	return "[Variable] " + _varName;
}

String VarNode::varName() const
{ return _varName; }

//----------------------------------------------------------------------------//

FuncNode::FuncNode(Expr* expr, const String& name, bool isFilter)
  : ExprNode(expr),
    _name(name),
    _isFilter(isFilter)
{
	if ((!isFilter && !Function::hasFunction(_name))
	    || (isFilter && !Function::hasFilter(name)))
		throw Exceptions::TemplateCompilation(_tpl, String("no such %1 "
	                                                     "\"%2\" found")
	                                        .format(isFilter
	                                                ? "filter" : "function",
	                                                _name));
	_func = isFilter ? Function::filterByName(name) : Function::byName(_name);
	/*if (_func.argsCount > -1 && _func.argsCount != _subNodes.count())
		throw Exceptions::TemplateCompilation(_tpl,
	                                        String("expecting %1 arguments to "
	                                               "function \"%2\", %3 given")
	                                        .format(_func.argsCount, _name,
	                                                _subNodes.count()));*/
}

Variant FuncNode::exec(Template* tpl)
{
	List<Variant> args;
	for (ExprNode* node : _subNodes)
		args.append(node->exec(tpl));
	Variant r = _func.func(tpl, args);
	if (_func.isRaw)
		r.setRaw();
	return r;
}

String FuncNode::dump() const
{
	return (_isFilter ? "[Filter] " : "[Function] ") + _name;
}

Function FuncNode::func() const
{ return _func; }

//----------------------------------------------------------------------------//

IndexNode::IndexNode(Expr* expr)
  : ExprNode(expr)
{}

Variant IndexNode::exec(Template* tpl)
{
	Variant val = _subNodes[0]->exec(tpl);
	Variant key = _subNodes[1]->exec(tpl);

	if (val.type() == Variant::Type::List)
	{
		if (key.type() != Variant::Type::Integer)
			throw 42; // FIX ME
		return val.toList()[key.toInt()];
	}
	else if (val.type() == Variant::Type::Map)
	{
		if (key.type() != Variant::Type::String)
			throw 42; // FIX ME
		return val.toMap()[key.toString()];
	}
	else if (val.type() == Variant::Type::String)
	{
		if (key.type() != Variant::Type::Integer)
			throw 42; // FIX ME
		return val.toString()[key.toInt()];
	}
	else
		throw 42; // FIX ME
}

String IndexNode::dump() const
{
	return "[Index] ";
}

//----------------------------------------------------------------------------//

ListNode::ListNode(Expr* expr)
  : ExprNode(expr)
{}

Variant ListNode::exec(Template* tpl)
{
	List<Variant> list;
	for (ExprNode* node : _subNodes)
		list.append(node->exec(tpl));
	return list;
}

String ListNode::dump() const
{
	return "[List]";
}

//----------------------------------------------------------------------------//

MapNode::MapNode(Expr* expr, const StringList& keys)
  : ExprNode(expr),
    _keys(keys)
{}

Variant MapNode::exec(Template* tpl)
{
	Map<String, Variant> map;
	for (int i = 0, c = _keys.count(); i < c; i++)
		map[_keys[i]] = _subNodes[i]->exec(tpl);
	return map;
}

String MapNode::dump() const
{
	return "[Map] keys = " + _keys.dump();
}
