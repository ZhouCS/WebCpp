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
 * @file Lexer.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-06-08
 */

#include "Lexer.h"
#include "CompiledTpl.h"
#include "Operator.h"

#include <Exceptions/Templates>

typedef Exceptions::TemplateCompilation ECompile;

OrderedMap<String, Lexem, std::greater<String>> Lexer::_tokens;

Lexer::Lexer(CompiledTpl* tpl, const String& src)
  : _tpl(tpl),
    _src(src),
    _i(0)
{
	while (_src[_i] != '\0')
	{
		skipWhitespaces();
		if (_src[_i] == '\0')
			break;
		else if (!readLiteral() && !readToken())
		{
			if ((_src[_i] < 'a' || _src[_i] > 'z')
			    && (_src[_i] < 'A' || _src[_i] > 'Z')
			    && (_src[_i] < '0' || _src[_i] > '9')
			    && _src[_i] != '_')
				throw ECompile(_tpl, String("unknown token '%1'").format(_src[_i]));
			readIdentifier();
		}
	}
}

bool Lexer::readLiteral()
{
	if (_src[_i] == '\'')
		readLiteralString();
	else if (_src[_i] >= '0' && _src[_i] <= '9')
		readLiteralNumber();
	else
		return false;
	return true;
}

bool Lexer::readToken()
{
	for (OrderedMap<String, Lexem, std::greater<String>>::Iterator i(_tokens);
	     i.hasNext(); i++)
	{
		int len = i.key().size();
		if (i.key() == _src.substr(_i, len)
		    && (!isKeyword(i.key())
		        || ((_src[_i + len] < 'a' || _src[_i + len] > 'z')
		            && (_src[_i + len] < 'A' || _src[_i + len] > 'Z')
		            && (_src[_i + len] < '0' || _src[_i + len] > '9')
		            && _src[_i + len] != '_')))
		{
			_lexems.append(i.value());
			_i += len;
			return true;
		}
	}
	return false;
}

void Lexer::readIdentifier()
{
	String name;
	while ((_src[_i] >= 'a' && _src[_i] <= 'z')
	       || (_src[_i] >= 'A' && _src[_i] <= 'Z')
	       || (_src[_i] >= '0' && _src[_i] <= '9')
	       || _src[_i] == '_')
		name += _src[_i++];

	if (name == "true")
		_lexems.append(Lexem(Variant(true)));
	else if (name == "false")
		_lexems.append(Lexem(Variant(false)));
	else if (name == "null")
		_lexems.append(Lexem(Variant()));
	else
		_lexems.append(Lexem(name));
}

void Lexer::readLiteralString()
{
	String str;

	_i++;
	while (_src[_i] != '\0')
	{
		if (_src[_i] == '\\')
		{
			_i++;
			if (_src[_i] == '\'')
				str += '\'';
			else if (_src[_i] == '\\')
				str += '\\';
			else if (_src[_i] == 'n')
				str += '\n';
			else if (_src[_i] == 't')
				str += '\t';
			else if (_src[_i] == 'x')
			{
				if (!(((_src[_i + 1] >= '0' && _src[_i + 1] <= '9')
				       || (_src[_i + 1] >= 'a' && _src[_i + 1] <= 'f')
				       || (_src[_i + 1] >= 'A' && _src[_i + 1] <= 'F'))
				      && ((_src[_i + 2] >= '0' && _src[_i + 2] <= '9')
				          || (_src[_i + 2] >= 'a' && _src[_i + 2] <= 'f')
				          || (_src[_i + 2] >= 'A' && _src[_i + 2] <= 'F'))))
					throw ECompile(_tpl, "invalid \\x escape sequence in literal string");
				str += static_cast<char>(_src.substr(_i + 1, 2).toInt(16));
				_i += 2;
			}
			else if (_src[_i] == 'u')
			{
				_i++;
				String seq;
				while (_src[_i] != ';')
				{
					if (!((_src[_i] >= '0' && _src[_i] <= '9')
					      || (_src[_i] >= 'a' && _src[_i] <= 'f')
					      || (_src[_i] >= 'A' && _src[_i] <= 'F')))
						throw ECompile(_tpl, "invalid unicode point code in \\u escape "
					                 "sequence of literal string");
					seq += _src[_i++];
				}
				str += String::fromUnicode(seq.toInt(16));
			}
			else if (_src[_i] != '\0')
				throw ECompile(_tpl, String("unknown \\%1 escape sequence in literal "
			                              "string").format(_src[_i]));
			_i++;
		}
		else if (_src[_i] == '\'')
			break;
		else
			str += _src[_i++];
	}
	if (_src[_i] == '\0')
		throw ECompile(_tpl, "unexpected end of expression, expecting end of "
	                 "literal string");
	_i++;
	_lexems.append(Lexem(Variant(str)));
}

void Lexer::readLiteralNumber()
{
	String n;
	bool foundPoint = false;
	bool isHex = false;

	if (_src[_i] == '0' && _src[_i + 1] == 'x')
	{
		_i += 2;
		isHex = true;
	}
	while (_src[_i] != '\0' && ((_src[_i] >= 'a' && _src[_i] <= 'z')
	                            || (_src[_i] >= 'A' && _src[_i] <= 'Z')
	                            || (_src[_i] >= '0' && _src[_i] <= '9')
	                            || _src[_i] == '_' || _src[_i] == '.'))
	{
		if (_src[_i] == '.' && !isHex && !foundPoint)
			foundPoint = true;
		else if ((_src[_i] < '0' || _src[_i] > '9')
		         && (!isHex || ((_src[_i] < 'a' || _src[_i] > 'f')
		                        && (_src[_i] < 'A' || _src[_i] > 'F'))))
			throw ECompile(_tpl, "invalid literal number");
		n += _src[_i++];
	}
	if (n.isEmpty() || n.endsWith("."))
		throw ECompile(_tpl, "invalid literal number");
	if (foundPoint)
		_lexems.append(Lexem(Variant(n.toFloat())));
	else
		_lexems.append(Lexem(Variant(n.toInt(isHex ? 16 : 10))));
}

bool Lexer::isKeyword(const String& token)
{
	int i = 0;

	while (token[i] != '\0')
	{
		if ((token[i] >= 'a' && token[i] <= 'z')
		    || (token[i] >= 'A' && token[i] <= 'Z')
		    || (token[i] >= '0' && token[i] <= '9')
		    || token[i] == '_')
			return true;
		i++;
	}
	return false;
}

void Lexer::skipWhitespaces()
{
	while (_src[_i] == ' ' || _src[_i] == '\t' || _src[_i] == '\n')
		_i++;
}

void Lexer::registerTokens()
{
	List<Operator*> ops = Operator::operators();
	for (Operator* op : ops)
		_tokens[op->token()] = Lexem(op);
	_tokens["("] = Lexem(Lexem::LeftParToken);
	_tokens[")"] = Lexem(Lexem::RightParToken);
	_tokens["["] = Lexem(Lexem::LeftBracketToken);
	_tokens["]"] = Lexem(Lexem::RightBracketToken);
	_tokens["{"] = Lexem(Lexem::LeftBraceToken);
	_tokens["}"] = Lexem(Lexem::RightBraceToken);
	_tokens["."] = Lexem(Lexem::PeriodToken);
	_tokens[","] = Lexem(Lexem::CommaToken);
	_tokens[":"] = Lexem(Lexem::ColonToken);
	_tokens["|"] = Lexem(Lexem::PipeToken);
}

List<Lexem> Lexer::lexems() const
{ return _lexems; }

//----------------------------------------------------------------------------//

Lexem::Lexem()
  : type(NoToken),
    op(nullptr)
{}

Lexem::Lexem(Operator* _op)
  : type(OperatorToken),
    op(_op)
{}

Lexem::Lexem(const String& _identifier)
  : type(IdentifierToken),
    op(nullptr),
    identifier(_identifier)
{}

Lexem::Lexem(const Variant& _literal)
  : type(LiteralToken),
    op(nullptr),
    literal(_literal)
{}

Lexem::Lexem(Type _type)
  : type(_type),
    op(nullptr)
{}

String Lexem::typeString() const
{
	Map<int, String> types;
	types[NoToken] = "(none)";
	types[OperatorToken] = "Operator";
	types[LeftParToken] = "LeftPar";
	types[RightParToken] = "RightPar";
	types[LeftBracketToken] = "LeftBracket";
	types[RightBracketToken] = "RightBracket";
	types[LeftBraceToken] = "LeftBrace";
	types[RightBraceToken] = "RightBrace";
	types[PeriodToken] = "Period";
	types[CommaToken] = "Comma";
	types[ColonToken] = "Colon";
	types[PipeToken] = "Pipe";
	types[IdentifierToken] = "Identifier";
	types[LiteralToken] = "Literal";
	return types[type];
}

void Lexem::dump() const
{
	std::cout << "[" << typeString() << "]";
	if (type == IdentifierToken)
		std::cout << " " << identifier;
	else if (type == LiteralToken)
		std::cout << " " << literal.typeString() << " = " << literal.toString();
	else if (type == OperatorToken)
		std::cout << " " << op->token() << " (" << op->name() << ")";
	std::cout << std::endl;
}
