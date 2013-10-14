/*************************************************************************
 * Copyright © 2011-2012 Kévin Lesénéchal <kevin.lesenechal@bilbax.com>  *
 *                                                                       *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.            *
 *                                                                       *
 * * WebCpp is free software: you can redistribute it and/or modify it     **
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/

/**
 * \file MVC/Templates/WppEngine/WppTplExpr.h
 * \author Kévin Lesénéchal
 * \date 2012-01-20
 */

#ifndef _MVC_TEMPLATES_WPPENGINE_WPPTPLEXPR_H
#define _MVC_TEMPLATES_WPPENGINE_WPPTPLEXPR_H

#include "Types/Renderable.h"
#include "Types/List.h"
#include "Types/Pair.h"
#include "Types/Map.h"

class WppTplVar;
class Template;
class WppTplFuncInstance;

/**
 * \class WppTplExpr MVC/Templates/WppEngine/WppTplExpr.h <WppTplExpr>
 * \brief A WebCpp template engine expression
 */
class WppTplExpr
{
	enum Operator{NoOperator, Filter, OpenParenthesis, CloseParenthesis, Brackets, OpenBracket, CloseBracket, Comma, Not, Product, Quotient, Modulo, Sum, Difference, Lower, LowerOrEgal, Greater, GreaterOrEgal, Egal, NotEgal, And, Or};
public:
	
	//WppTplExpr(const String& src);
	WppTplExpr();
	
	static WppTplExpr* parse(const String& src);
	
	Renderable exec(const Template* tpl) const;
	
	void debug() const;

private:
	static int opPriority(Operator op);
	
	static String opToStr(Operator op);
	
private:
	Operator _op;
	
	WppTplExpr* _left;
	
	WppTplExpr* _right;
	
	Renderable _literal;
	
	WppTplVar* _variable;
	
	WppTplFuncInstance* _func;
};

#endif
