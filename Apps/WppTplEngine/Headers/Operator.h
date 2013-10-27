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
 * @file Operator.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#ifndef _WPP_OPERATOR_H_
#define _WPP_OPERATOR_H_

#include <List>

class String;
class Variant;

class Operator
{
public:
	enum Type {Unary = 0x1, Binary = 0x2};

	Operator(const String& name, const String& token, int type);

	virtual ~Operator(){}

	/**
	 * @brief Implements arguments' type checks
	 * @param types The list of arguments' type
	 * @return true if the operator is applicable for those types, otherwise false
	 */
	virtual bool checkArgTypes(const List<Variant::Type>& types) const = 0;

	/**
	 * @brief Implements how to execute the operator
	 * @param args The operator's arguments
	 * @return The resulting value
	 */
	virtual Variant exec(const List<Variant>& args) const = 0;

	String name() const;
	String token() const;
	int    precedence(bool isUnary = false) const;
	bool   isRightAssociative(bool isUnary = false) const;
	bool   isUnary() const;
	bool   isBinary() const;

public:
	static void registerOperator(Operator* op);
	static void registerBuiltins();
	static void deleteOperators();
	static List<Operator*> operators();

protected:
	String _name;
	String _token;
	int    _type;
	int    _unaryPrecedence;
	int    _binaryPrecedence;
	bool   _unaryIsRightAssociative;
	bool   _binaryIsRightAssociative;
	bool   _hasSideEffect;

private:
	static List<Operator*> _operators;
};

#endif // !_WPP_OPERATOR_H_
