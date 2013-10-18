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
 * @file Operators/CompOps.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-07-31
 */

#ifndef _OPERATORS_COMPOPS_H_
#define _OPERATORS_COMPOPS_H_

#include "Operator.h"

namespace Operators {

class Equal : public Operator
{
public:
	Equal();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class NotEqual : public Operator
{
public:
	NotEqual();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Less : public Operator
{
public:
	Less();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class LessEqual : public Operator
{
public:
	LessEqual();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Greater : public Operator
{
public:
	Greater();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class GreaterEqual : public Operator
{
public:
	GreaterEqual();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

} // ns Operators

#endif // !_OPERATORS_COMPOPS_H_
