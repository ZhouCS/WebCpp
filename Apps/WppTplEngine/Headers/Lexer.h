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
 * @file Lexer.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-08
 */

#ifndef _LEXER_H_
#define _LEXER_H_

#include <String>
#include <List>
#include <OrderedMap>

class Operator;
class CompiledTpl;

class Lexem
{
public:
	enum Type
	{
		NoToken,
		OperatorToken,
		LeftParToken,
		RightParToken,
		LeftBracketToken,
		RightBracketToken,
		LeftBraceToken,
		RightBraceToken,
		PeriodToken,
		CommaToken,
		ColonToken,
		PipeToken,
		IdentifierToken,
		LiteralToken
	};

	Lexem();
	Lexem(Operator* op);
	Lexem(const String& identifier);
	Lexem(const Variant& literal);
	Lexem(Type type);

	String typeString() const;
	void   dump() const;

	Type      type;
	Operator* op;
	bool      opIsUnary;
	String    identifier;
	Variant   literal;
};

class Lexer
{
public:
	Lexer(CompiledTpl* tpl, const String& src);

	List<Lexem> lexems() const;

	static void registerTokens();

private:
	bool readLiteral();
	bool readToken();
	void readIdentifier();
	void readLiteralString();
	void readLiteralNumber();
	bool isKeyword(const String& token);
	void skipWhitespaces();

private:
	CompiledTpl* _tpl;
	String       _src;
	int          _i;
	List<Lexem>  _lexems;

private:
	static OrderedMap<String, Lexem, std::greater<String>> _tokens;
};

#endif // !_LEXER_H_
