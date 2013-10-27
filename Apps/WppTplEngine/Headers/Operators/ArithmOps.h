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
 * @file Operators/ArithmOps.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-09
 */

#ifndef _WPP_OPERATORS_ARITHMOPS_H_
#define _WPP_OPERATORS_ARITHMOPS_H_

#include "Operator.h"

namespace Operators {

class Sum : public Operator
{
public:
	Sum();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Difference : public Operator
{
public:
	Difference();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Product : public Operator
{
public:
	Product();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Quotient : public Operator
{
public:
	Quotient();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

class Modulo : public Operator
{
public:
	Modulo();
	virtual bool checkArgTypes(const List<Variant::Type>& types) const override;
	virtual Variant exec(const List<Variant>& args) const override;
};

} // ns Operators

#endif // !_WPP_OPERATORS_ARITHMOPS_H_
