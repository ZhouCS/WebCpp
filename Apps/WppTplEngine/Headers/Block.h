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
 * @file Block.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2013-05-20
 */

#ifndef _WPP_BLOCK_H_
#define _WPP_BLOCK_H_

#include <String>
#include <Map>
#include <MultiMap>
#include <Stack>

class Template;
class Expr;
class CompiledTpl;

class Block
{
public:
	struct Value
	{
		Block* block;
		Expr*  expr;
		Value(Block* block) : block(block), expr(nullptr){}
		Value(Expr* expr) : block(nullptr), expr(expr){}
	};

	enum ArgumentPolicy {NoArgument, OptionalArgument, RequiredArgument};
	enum HasBodyBool {HasBody = true, HasNoBody = false};

public:
	Block(const String& name, ArgumentPolicy argPolicy, HasBodyBool hasBody);
	Block(Block* parent, const String& name);
	Block(CompiledTpl* tpl,
	      const String& src,
	      Block* parent = nullptr,
	      const String& name = String());
	virtual ~Block();

	virtual String render(Template* tpl, int from = 0, int end = -1);

	String       name() const;
	Block*       parent() const;
	CompiledTpl* tpl() const;
	MultiMap<int, Value>& vals();
	MultiMap<int, Expr*>  exprs() const;
	MultiMap<int, Block*> blocks() const;
	Variant      var(Template* tpl, const String& name) const;
	String       staticContent() const;

public:
	static void registerBlock(Block* block);
	static void registerBuiltins();
	static void deleteBlocks();

protected:
	virtual Block* newInstance(Block* parent) const;
	virtual void   setArgument(const String& arg);
	virtual void   compiledEvent();

private:
	bool isEscaped(int* i);
	int  exprLength(bool blockArg, int i);
	void parseBlock(int* i, Stack<Block*>* blocks);
	void closeBlock(int* i, Stack<Block*>* blocks);
	int  blockSourceIndex(int leftPos, int right, bool wantLeft);
	void skipString(int* i);
	void skipWhitespaces(int* i);
	void callCompiledEvent(Block* block);

protected:
	ArgumentPolicy _argPolicy;
	bool           _hasBody;

	CompiledTpl*         _tpl;
	Block*               _parent;
	String               _name;
	String               _src;
	MultiMap<int, Value> _vals;
	Map<String, Variant> _vars;

private:
	int _innerStart;
	int _outerStart;
	int _innerEnd;
	int _outerEnd;

private:
	static Map<String, Block*> _blocks;
};

#endif // !_WPP_BLOCK_H_
