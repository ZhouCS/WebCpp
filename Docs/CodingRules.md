# Coding rules #

The following coding rules apply to all written code for the WebCpp project
and its components. These refer to the C++ language and must be respected
wherever you write C++ code for WebCpp. Non-respect of these rules will result
in commit rejections.

That document aims to harmonize the source code and to prevent some issues
especially regarding the DCVS usage. We do not pretend this coding convention is
the most effective and elegant way of dealing with C++. The only goal of
imposing you these rules is to make the whole project's sources homogeneous.

If you have any remarks, questions or suggestions about this coding style, feel
free to email us at <kevin@lesenechal.org>, we will enjoy discussing about this
around a beer (if physically possible).

## Table of contents ##

<ol start="0">
	<li><a href="#general">General</li>
	<li><a href="#indentation">Indentation</li>
	<li><a href="#alignment">Alignment</li>
	<li><a href="#naming">Naming</li>
	<li><a href="#preprocessor">Preprocessor</a></li>
	<li><a href="#classes-and-objects">Classes and objects</li>
	<li><a href="#header-files">Header files</li>
	<li><a href="#miscellaneous">Miscellaneous</li>
	<li><a href="#comments-and-documentation">Comments and documentation</li>
</ol>


## <a id="general" />0. General ##

We are coding in C++, avoid C-style stuff like `printf`, `malloc`, the `NULL`
macro, etc.

Do not _import_ all names from `std` namespace using the directive
`using namespace std;`.

File names are CamelCased with no underscores. All header files are placed in
the `Headers` directory and the sources in `Sources`. Use directories to
organize your files.

A line of code must never be longer than **80 columns** including comments. One
character beyond and your commit is automatically rejected.

Please make use of the C++11 standard. If don't know the new features this
standard brings, learn them. We'll refuse your code if it isn't C++11-style. For
example, always use `nullptr`, initializer lists, range for-loops, etc.

Make sure you always compile with the flags `-pedantic`, `-Wall` and `-Wextra`;
to ensure you get all the warnings.

Do not commit or merge code on branch `dev` with warnings.

Only encode your sources files in **UTF-8** without BOM with **UNIX newlines**
(`LF`) and never Windows ones (`CRLF`) nor Mac's (`CR`).


## <a id="indentation" />1. Indentation ##

Use the **Allman indentation style**, like:

	int main()
	{
		if (5 > 42)
		{
			foo();
			bar(21);
		}
		else
			lorem();
	}

Always use **tabs** for indentation, **never** spaces. Configure your editor
properly so that it never indents using spaces. You are free to choose the width
of the indentation as you like it.

Omit the braces for blocks with only one instruction **and no sub-blocks**.

	// Correct:
	if (true)
		foo();
	else
	{
		while (str[i] != '\0')
			i++;
	}

	// Wrong:
	if (true)
	{ // Nop
		foo();
	} // Nop
	else
		while (str[i] != '\0') // Nop
			i++;

Do not indent a namespace content and put the brace on the same line of the
namespace definition:

	namespace Foo {
	namespace Bar {

	class Lorem
	{
		// ...
	};

	} // ns Bar
	} // ns Foo

End the namespace by reminding which one you close using the `ns MyNS` syntax.

Do not let any white character (space or tab) at the end of a line. Configure
your editor so that it automatically clears them. Example:

	int main()
	{
	———→int i = 42;
	———→ // Wrong, remove this tab
	———→return i;
	}


## <a id="alignment" />2. Alignment ##

Use alignment to split a long instruction on multiple lines. Do not put any
trailing backslash at the end of the line.

Always align with **spaces**, never tabs! Spaces have a fixed width, not tabs;
alignment requires a fixed width.

Example:

	if (true)
	{
	———→int foo = bar
	———→••••••••••+ lorem
	———→••••••••••+ ipsum;
	}

Tabs are represented by `———→` and spaces by `•`. Pay attention on how tabs and
spaces are used together. Tabs represent a level of indentation within blocks
and spaces are used for alignment. If you are wondering which one of them you
should use, ask yourself "Will the code be correct if I double the tabs width?".

The operator is at the begining of the next line and not at the end of the
previous one.

With parentheses, make sure the operator is just under the opening parenthesis,
one column to the right.

Example:

	int foo = bar * (lorem
	•••••••••••••••••+ ipsum);

Do the same for conditions:

	while (run)
	{
	———→if ((_src[_i] < '0' || _src[_i] > '9')
	———→••••&& (!isHex || ((_src[_i] < 'a' || _src[_i] > 'f')
	———→•••••••••••••••••••&& (_src[_i] < 'A' || _src[_i] > 'F'))))
	———→{
	———→———→// ...
	———→}
	}

Use your common sense to align when it adds visibility, for example:

	types[NoToken]••••••••••= "(none)";
	types[OperatorToken]••••= "Operator";
	types[LeftParToken]•••••= "LeftPar";
	types[RightParToken]••••= "RightPar";
	types[LeftBracketToken]•= "LeftBracket";
	// ...

But don't go too far and do not align between blocks of different indentation
levels because of the variable width of tabs used for indentation.

This is wrong:

	int•••••foo = 42;
	if (foo > 0)
	{
	———→int•bar = 21;
	———→// ...
	}

I aligned the `foo` variable with the `bar` one. That would be a great idea if
those variables were defined in the same block. Imagine the tabs are doubled in
width, it would not be aligned anymore.

Do not align if it implies to much spaces, for example:

	const MySuperObject*•obj = nullptr;
	int••••••••••••••••••myInt; // Too far from its type

Here is a last example with a function definition:

	void mySuperFunc(const String& name,
	•••••••••••••••••int••age, // Not aligned with "name": too far
	•••••••••••••••••bool•isMale) // But aligned with "isMale": they are close
	{
	———→// ...

When the function's parameters can't hold on a single line without breaking the
80 columns rule, split each parameter on its own line (I mean only **one**
parameter per line).

Align comments if they are not too distant from each other:

	foo = 21;••••••••// A comment
	bar = foo / 3.5;•// Another comment


## <a id="naming" />3. Naming ##

Correctly naming your identifiers is certainly the hardest part of these rules.
Your common sense is the most useful tool you may have. Don't hesitate to take
five minutes (yes, *five* minutes!) searching for a good name. Bad naming is the
root of all evil.

All identifiers must be written in US English (i.e. write "color" and not
"colour").

Almost all of the identifiers are *CamelCased*, some begin with a capital, some
others don't.

These identifiers **must** begin with a capital:

 * Classes name;
 * Files name;
 * Namespaces;
 * Enumerations name;
 * Enumeration *items* name;
 * Template parameters;
 * Custom types (typedef).

These **musn't** begin with a capital:

 * Functions name;
 * Methods name;
 * Variables name;
 * Attributes name.

Macros are named in all capitals and are underscored. But avoid macros when
possible.

Do not prefix variables name with its type (Hungarian notation), don't:

	int    iAge;
	String sName;
	bool   bIsMale;

Do not prefix classes names with anything like `C` or `I`.

Avoid long names but use abbreviations carefully. Especially when dealing with
public interfaces (classes, methods, namespaces, ...), avoid them; prefer longer
names for public interfaces. For implementation-specific names, you can use
abbreviations, but don't abuse: only use obvious abbreviations.


## <a id="preprocessor" />4. Preprocessor ##

Indent nested preprocessor directives using **two spaces** (not tabs) between
the `#` symbol and the directive name. Do not indent before the `#` symbol or
put any white character before it.

	#if __cplusplus > 199711L
	#••define CPP11 1
	#else
	#••define CPP11 0
	#endif

Do not indent the `#define` directive of headers' guard nor the directives
inside the guard's condition.

When using conditions directives to enable or disable source code, use a comment
line to remind which condition you close:

	#ifndef _DIR_SUBDIR_MYHEADER_H_
	#define _DIR_SUBDIR_MYHEADER_H_

	#if MY_MACRO >= 42

	// ...

	#endif // MY_MACRO >= 42

	#endif // !_DIR_SUBDIR_MYHEADER_H_

When including files, always include local headers first **then** libraries
headers. Use empty lines between `#include` directives to group them by
categories; use your own judgment to choose those categories, example:

	#include "MyClass.h"
	#include "Foo.h"
	#include "Bar.h"

	#include "Exceptions/MyEx1.h"
	#include "Exceptions/MyEx2.h"
	#include "Exceptions/MyEx3.h"

	#include <GLEngine/FragmentShader>
	#include <GLEngine/Program>

	#include <iostream>

## <a id="classes-and-objects" />5. Classes and objects ##

All attributes are prefixed with an underscore, like `_name`.

Getters are **not** prefixed with `get`: for an attribute `_name` the getter
would be `name()`, **not** `getName()`. But setters are prefixed with `set`; so,
for our example, the setter would be `setName()`.

All attributes must be protected or private, never public.

Abstract classes *should* be prefixed with `Abstract` (e.g. `AbstractCreature`).

Initialization lists are on a new line with each attribute on its own line. Pay
attention to the particular alignment (using only spaces):

	Foo::Foo()
	••:•Bar(),
	••••_a(42),
	••••_b("Hello")
	{
	———→ // ...

Always use initialization lists when possible rather than assignments in the
constructor's body.

Constructors with only one required parameter must be declared `explicit` if an
implicit conversion is not intended.

Do not indent the `public`, `protected` and `private` keywords.

Always respect this order of declaration:

 * Public constructors, then destructor, then public methods, then accessors;
 * Public static methods;
 * Protected constructors and methods;
 * Protected static methods;
 * Private constructors and methods;
 * Private static methods;
 * Protected attributes;
 * Protected static attributes;
 * Private attributes;
 * Private static attributes.

Always separate those categories by placing the visibility keyword even if it is
repeated:

	class Foo
	{
	public:
		Foo();
		explicit Foo(int a);

		virtual ~Foo();

		void doSomething();
		void executeSomeCode();

		String name() const;
		int    age() const;

	public:
		static void bar();

	protected:
		float lorem(const String& ipsum);

	private:
		String _name;
		int    _age;
		bool   _isMale;

	private:
		static Map<String, Foo> _myHash;
	};

For virtual methods, always specify the `virtual` keyword, do not rely on the
implicit inheritance of it. For virtual methods that override its parent, put
the `override` keyword on it.

## <a id="header-files" />6. Header files ##

Every header file must contain a macro guard named after the file's relative
path. The path (without the `Headers` directory) is written in all capitals with
slashes and points replaced by underscores. Put an underscore before and after
the macro name. And don't forget to prefix the guard with `WPP`. For example,
the header file `Headers/Foo/Bar.h` will have a macro guard named
`_WPP_FOO_BAR_H_`.


## <a id="miscellaneous" />7. Miscellaneous ##

Place the pointer marker `*` and the reference marker `&` on the type, not the
variable name; except when defining multiple variables at one time.

	int* ptr;   // Good
	Obj &ref;   // Bad
	int* a, b;  // Bad: confusing
	int *a, *b; // Good

For the sake of lisibility, always make a `typedef` of function pointers type:

	// Don't:
	void (*mySignal(Signal sig, void (*handler)(int)))(int);

	// Do:
	typedef void (*SignalHandler)(int);

	SignalHandler mySignal(Signal sig, SignalHandler handler);

Do not implicitly cast to bool, example:

	char* var = getenv("DISPLAY");
	if (var) // No
	// Do this:
	if (var != nullptr) // Yes

Always put a space before and after every binary operator. Don't put a space
between an unary operator and its operand excepted for the `sizeof` and `typeid`
operators. Avoid parentheses on the `sizeof` and `typeid` when unnecessary.

	int foo = 4 + -(8 / 6 % 2); // Yes
	foo = 7*9;         // No
	foo = sizeof(foo); // No
	foo = sizeof foo;  // Yes

Always put a space after the keywords `if`, `else if`, `while`, `for`, `return`
and `catch`.


## <a id="comments-and-documentation" />8. Comments and documentation ##

All comments are written in US English only.

The `//` token for line comments must have a space before and after it, excepted
at the begining of a line or with only spaces or tabs on the left. Example:

	int foo; // Defines a variable "foo" as int
	// I'm a comment! (no space before `//`)

Multiline comments *should* be like this:

	/* Lorem
	 * ispum
	 * dolor
	 */

You must document every class, function, method, function, macro and attribute.
Use the Doxygen syntax:

	/**
	 * @brief Very brief description, 80 columns max, no line breaks
	 * @param arg1 Argument 1
	 * @param arg2 Argument 2
	 * @return If the function doesn't return anything (void), omit this
	 *
	 * Detailed description on multiple lines if necessary.
	 */
	int foo(int arg1, int arg2);

Document only in header files and use the `@` sign for tags, never backslashes.

In every source file (including both headers and sources) you'll place the
copyright notice below starting from the very first line.

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

Don't forget to document your file (headers and sources):

	/**
	 * @file Relative/Path/To/File.cpp
	 * @author John Smith <jsmith@gmail.com>
	 * @date 1992-10-15
	 */

Placed just after the copyright notice (with a blank line between them).