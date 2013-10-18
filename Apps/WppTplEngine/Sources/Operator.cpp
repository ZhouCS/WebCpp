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
 * @file Operator.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#include "Operator.h"

#include "Operators/ArithmOps.h"
#include "Operators/LogicOps.h"
#include "Operators/CompOps.h"
#include "Operators/MiscOps.h"

List<Operator*> Operator::_operators;

Operator::Operator(const String& name,
                   const String& token,
                   int type)
  : _name(name),
    _token(token),
    _type(type),
    _unaryIsRightAssociative(true),
    _binaryIsRightAssociative(false),
    _hasSideEffect(false)
{}

void Operator::registerOperator(Operator* op)
{
	_operators.append(op);
}

void Operator::registerBuiltins()
{
	registerOperator(new Operators::Sum);
	registerOperator(new Operators::Difference);
	registerOperator(new Operators::Product);
	registerOperator(new Operators::Quotient);
	registerOperator(new Operators::Modulo);

	registerOperator(new Operators::And);
	registerOperator(new Operators::Or);
	registerOperator(new Operators::Not);

	registerOperator(new Operators::Equal);
	registerOperator(new Operators::NotEqual);
	registerOperator(new Operators::Less);
	registerOperator(new Operators::LessEqual);
	registerOperator(new Operators::Greater);
	registerOperator(new Operators::GreaterEqual);

	registerOperator(new Operators::Typeof);
	registerOperator(new Operators::Count);
}

void Operator::deleteOperators()
{
	for (Operator* op : _operators)
		delete op;
}

//----------------------------------------------------------------------------//

String Operator::name() const
{ return _name; }

String Operator::token() const
{ return _token; }

int Operator::precedence(bool isUnary) const
{ return isUnary ? _unaryPrecedence : _binaryPrecedence; }

bool Operator::isRightAssociative(bool isUnary) const
{ return isUnary ? _unaryIsRightAssociative : _binaryIsRightAssociative; }

bool Operator::isUnary() const
{ return _type & Unary; }

bool Operator::isBinary() const
{ return _type & Binary; }

List<Operator*> Operator::operators()
{ return _operators; }
