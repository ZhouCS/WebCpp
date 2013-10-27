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
 * @file Types/String.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#ifndef _TYPES_STRING_H_
#define _TYPES_STRING_H_

#include <string>

class StringList;
class Regex;
class ByteArray;
class AbstractDbConnection;

template <typename, typename> class Map;

/**
 * @class String Types/String.h <String>
 * @brief A string
 */
class String : private std::string
{
public:
	using std::string::compare;
	using std::string::operator+=;
	using std::string::begin;
	using std::string::end;
	friend std::istream& operator>>(std::istream&, String&);

	/**
	 * @brief Constructs an empty string
	 */
	String();

	/**
	 * @brief Constructs a string from std::string
	 * @param str The std::string
	 */
	String(const std::string& str);

	/**
	 * @brief Constructs a string from a C string
	 * @param str The C string as const char*
	 */
	String(const char* str);

	/**
	 * @brief Constructs a string from a byte array
	 * @param ba The byte array
	 */
	String(const ByteArray& ba);

	/**
	 * @brief Constructs a string from a single character
	 * @param ch The character to constructs the string from
	 */
	String(char ch);

	/**
	 * @brief Constructs a string from an integer
	 * @param n The integer to constructs the string from
	 */
	String(int n);

	String(unsigned int n);

	String(long unsigned int n);

	String(double n);


	/**
	 * @brief Get the string length
	 * @return The string length
	 * @note This function is Unicode-safe
	 *
	 * This method returns the real number of characters in the string, including
	 * multi-bytes characters.
	 *
	 * @code
	 * String str1 = "Moo foo";
	 * String str2 = "Poupé";
	 * String str3 = "Cœur";
	 *
	 * // str1.length() = 7
	 * // str2.length() = 5
	 * // str3.length() = 4
	 * @endcode
	 *
	 * @sa size()
	 */
	int length() const;

	/**
	 * @brief Get the string size
	 * @return The string size
	 * @warning This method doesn't return the string length, it returns the
	 *          string size in memory
	 *
	 * This method returns the number of bytes used by the string in memory, and
	 * not the number of characters in it.
	 *
	 * @code
	 * String str1 = "Moo foo";
	 * String str2 = "Poupé";
	 * String str3 = "Cœur";
	 *
	 * // str1.size() = 7
	 * // str2.size() = 6
	 * // str3.size() = 5
	 * @endcode
	 *
	 * @sa length()
	 */
	int size() const;

	/**
	 * @brief Reserve @p size bytes to the string
	 * @param size The size in bytes to reserve
	 */
	void reserve(int size);


	/**
	 * @brief Get the char at index @p index
	 * @param index The char index
	 * @return The char at index @p index
	 */
	char charAt(int index) const;


	/**
	 * @brief Tests if the string contains a string snippet
	 * @param str The string snippet
	 * @return true if the string contains @p str, otherwise false
	 *
	 * @code
	 * String str = "The quick brown fox jumps over the lazy dog";
	 * // str.contains("quick") = true
	 * // str.contains("Dog") = false (case sensitive)
	 * @endcode
	 */
	bool contains(const String& str) const;

	/**
	 * @brief Tests if the string is contained in the given string list
	 * @param list The string list
	 * @return true if the strin is containted in @p list, otherwise false
	 */
	bool in(const StringList& list) const;

	/**
	 * @brief Determines if the string starts with the given string
	 * @param str The given string
	 * @return true if the string starts with @p str, otherwise false
	 */
	bool startsWith(const String& str) const;

	/**
	 * @brief Determines if the string ends with the given string
	 * @param str The given string
	 * @return true if the string ends with @p str, otherwise false
	 */
	bool endsWith(const String& str) const;


	/**
	 * @brief Get the index of a string snippet
	 * @param str The string snippet to search
	 * @param from The index from which the search will start
	 * @return Index of the snippet in the string from @p from, -1 if not found
	 */
	int indexOf(const String& str, int from = 0) const;

	int reversedIndexOf(const String& str, int from = 0) const;

	/**
	 * @brief Counts the number of @p str occurences in the string
	 * @param str The string
	 * @return The number of @p str occurences in the string
	 */
	int count(const String& str) const;

	/**
	 * @brief Tests if the string matches a regular expression
	 * @param regex The regular expression
	 * @return true if the regular expression matches the string, otherwise false
	 */
	bool match(Regex regex) const;

	/**
	 * @overload match
	 * @brief Tests if the string matches a regular expression
	 * @param pattern The regular expression pattern
	 * @return true if the regular expression matches the string, otherwise false
	 */
	bool match(const String& pattern) const;

	/**
	 * @brief Extracts a sub string
	 * @param start The starting index
	 * @param n The length of the substring, if -1, all the rest of the string is
	 *          taken
	 * @return A substring of @p n characters starting from @p start.
	 * @warning This method is not Unicode-safe
	 *
	 * This method returns a sub part of the string from index @p start to a
	 * length of @p n. If @p n is negative, all the rest of the string is returned
	 * from @p start.
	 *
	 * @code
	 * String str = "Lorem ipsum dolor sit amet";
	 * // str.substr(4, 6) = "m ipsu";
	 * // str.substr(12, 5) = "dolor";
	 * // str.substr(18) = "sit amet";
	 * @endcode
	 */
	String substr(int start, int n = -1) const;

	/**
	 * @brief Get @p n characters from the left
	 * @param n The number of characters to get from the left
	 * @return The @p n characters from the left
	 */
	String left(int n) const;

	/**
	 * @brief Get @p n characters from the right
	 * @param n The number of characters to get from the right
	 * @return The @p n characters from the right
	 */
	String right(int n) const;

	/**
	 * @brief Get a substring between two indexes (included)
	 * @param start The starting index
	 * @param end The ending index (included)
	 * @return A substring between indexes @p start and @p end included.
	 */
	String mid(int start, int end) const;

	/**
	 * @brief Get a substring between two indexes (excluded)
	 * @param start The starting index
	 * @param end The ending index (excluded)
	 * @return A substring between indexes @p start and @p end excluded.
	 */
	String midExcluded(int start, int end) const;


	/**
	 * @brief Removes @p n characters from the left
	 * @param n The number of characters to remove from the left
	 * @return A string with @p n characters removed from the left
	 */
	String removeLeft(int n) const;

	/**
	 * @brief Removes @p n characters from the right
	 * @param n The number of characters to remove from the right
	 * @return A string with @p n characters removed from the right
	 */
	String removeRight(int n) const;

	/**
	 * @brief Get the part of the string before a token
	 * @param token The token
	 * @return The part of the string before the token
	 */
	String tokenLeft(const String& token) const;

	/**
	 * @brief Get the part of the string after a token
	 * @param token The token
	 * @return The part of the string after the token
	 */
	String tokenRight(const String& token) const;


	/**
	 * @brief Get a section of a string
	 * @param delimiter The delimiter to split the string
	 * @param start The index of the start
	 * @param end The index of the end
	 * @return A section of the string splitten by the delimiter @p delimiter with
	 *         the parts from @p start to @p end
	 *
	 * This method will split the string with the given delimiter @p delimiter and
	 * return the joined parts from @p start to @p end.
	 *
	 * @code
	 * String myStr = "apple;banana;orange;tomato;kiwi;pear";
	 * String substring = myStr.section(";", 1, 3);
	 * // substring = "banana;orange;tomato"
	 * @endcode
	 *
	 * If @p start or @p end is negative, the parts are indexed backward from the
	 * end. -1 is the last part, -2 the penultimate, etc.
	 *
	 * @code
	 * String myStr = "apple;banana;orange;tomato;kiwi;pear";
	 * String substring = myStr.section(";", 2, -2);
	 * // substring = "orange;tomato;kiwi"
	 * @endcode
	 *
	 * If the delimiter is not found, the entire string is returned.
	 */
	String section(const String& delimiter, int start, int end = -1) const;

	/**
	 * @brief Split the string with the given delimiter
	 * @param delimiter The delimiter to split the string
	 * @return The splitten string as StringList
	 *
	 * @code
	 * String str = "apple;banana;orange;tomato;kiwi";
	 * std::cout << str.split(";").dump() << std::endl;
	 *
	 * // Displays:
	 * // String list (5 items) ["apple", "banana", "orange", "tomato", "kiwi"]
	 * @endcode
	 */
	StringList split(const String& delimiter) const;


	/**
	 * @brief Replaces text from @p start to @p end with @p str
	 * @param start The starting index
	 * @param end The ending index
	 * @param dest The text to replace to
	 * @return The string where text from @p start to @p end is replaced by @p str
	 */
	String replace(int start, int end, const String& dest) const;

	/**
	 * @brief Replace a snippet of text by an other
	 * @param source The text to replace
	 * @param dest The text to replace to
	 * @return A copy of the string with @p source replaced by @p dest
	 */
	String replace(const String& source, const String& dest) const;

	/**
	 * @brief Replace a snippet of text by an other using a regular expression
	 * @param regex The regular expression
	 * @param dest The pattern to replace to
	 * @return The string with regular expression replacement
	 *
	 * This method captures and replace texts from the string with the regular
	 * expression @p regex and the pattern @p dest with \\n the (n+1)th captured
	 * text.
	 *
	 * @code
	 * String str = String("www.webcpp.org")
	 *              .replace(Regex("^(.+)\\.(.+)\\.(.+)$"),
	 *                             "'\\0' in '\\1' in '\\2'");
	 * // str = "'www' in 'webcpp' in 'org'";
	 * @endcode
	 */
	String replace(Regex regex, const String& dest) const;


	/**
	 * @brief Inserts @p str at @p pos
	 * @param pos The position at which to insert the string
	 * @param str The string to insert
	 */
	String insert(int pos, const String& str) const;


	/**
	 * @brief Extracts variables from a query string
	 * @return The mapped variables from the query string
	 */
	Map<String, String> parseQueryString() const;

	/**
	 * @brief Returns a secured copy of the string
	 * @return The secured copy of the string
	 *
	 * This method must be used on all user inputs. This will check and remove
	 * invalid UTF-8 sequences and non-printable characters (BEL, BS, VT, ...).
	 * CRLF new lines are also replaced by LF.
	 */
	String secure() const;

	/**
	 * @brief Escape an HTML string
	 * @return The escaped HTML string
	 */
	String htmlEscape() const;

	String urlEscape() const;

	/**
	 * @brief Unescape an URL string
	 * @return The unescpaed URL string
	 *
	 * This method returns a copy of the URL-encoded string to basic string. \%**
	 * is replace by character char(0x**)
	 *
	 * @code
	 * String str = "Poup%C3%A9%20%3Cp%3EMoo%3C/p%3E%20!";
	 * // str.urlUnescape() = "Poupé <p>Moo</p> !";
	 * @endcode
	 */
	String urlUnescape() const;

	/**
	 * @brief Escape a string for an SQL request
	 * @param dbConnection The database connection
	 * @return The escaped string
	 */
	String sqlEscape(AbstractDbConnection* dbConnection = 0) const;


	/**
	 * @brief Return a trimmed copy if the string
	 */
	String trim() const;


	/**
	 * @brief Format the string with the given arguments
	 * @param args The arguments list
	 * @return The formatted string
	 *
	 * This method return a formatted copy of the string, with %x the argument
	 * index x starting from 1.
	 *
	 * @code
	 * String str = "Hello %1, you are %2 years old.";
	 * str.format({"John", "23"}); // returns "Hello John, you are 23 years old."
	 * @endcode
	 */
	String format(const StringList& args) const;

	/**
	 * @overload String format(const StringList& args) const
	 * @brief Format the string with 1 string
	 * @param arg1 Argument no 1
	 */
	String format(const String& arg1) const;

	/**
	 * @overload String format(const StringList& args) const
	 * @brief Format the string with 2 strings
	 * @param arg1 Argument no 1
	 * @param arg2 Argument no 2
	 */
	String format(const String& arg1, const String& arg2) const;

	/**
	 * @overload String format(const StringList& args) const
	 * @brief Format the string with 3 strings
	 * @param arg1 Argument no 1
	 * @param arg2 Argument no 2
	 * @param arg3 Argument no 3
	 */
	String format(const String& arg1,
	              const String& arg2,
	              const String& arg3) const;


	/**
	 * @brief Convert the string into integer
	 * @param base The number base represented by the string
	 * @return The integer value
	 * @warning This method doesn't support conversion failure yet
	 *
	 * This metod tries to convert the string to an integer with the given base
	 * @p base.
	 *
	 * @code
	 * String str1 = "42";
	 * String str2 = "b0";
	 * String str3 = "11010110";
	 *
	 * // str1.toInt() = 42
	 * // str1.toInt(16) = 66
	 * // str1.toInt(8) = 34
	 *
	 * // str2.toInt(16) = 176
	 *
	 * // str3.toInt(2) = 214
	 * // str3.toInt() = 11010110
	 * @endcode
	 */
	int toInt(int base = 10) const;

	/**
	 * @brief Converts the string into 64 bits unsigned integer
	 * @param base The number base represented by the string
	 * @return The uint64 value
	 */
	uint64_t toUInt64(int base = 10) const;

	/**
	 * @brief Converts the string into float
	 * @return The float value
	 */
	float toFloat() const;

	/**
	 * @brief Returns an upper case copy of the string
	 * @warning This method has performance issues
	 */
	String toUpper() const;

	/**
	 * @brief Returns an upper case copy of the string (only ASCII characters)
	 */
	String toAsciiUpper() const;

	/**
	 * @brief Returns a copy of the string with the first letter upper cased
	 * @warning This method is not unicode-safe
	 * @warning This method has performance issues
	 */
	String upperFirst() const;

	/**
	 * @brief Returns a copy of the string with the first letter upper cased (only
	 *        ASCII characters)
	 */
	String upperAsciiFirst() const;

	/**
	 * @brief Returns a lower case copy of the string
	 * @warning This method has performance issues
	 */
	String toLower() const;

	/**
	 * @brief Returns a lower case copy of the string (only ASCII characters)
	 */
	String toAsciiLower() const;


	String& operator=(const String& str);

	/**
	 * @brief Get the character at index @p index
	 */
	char operator[](int index) const;

	/**
	 * @brief Concatenate the string with a string
	 * @param str The string to concatenate to
	 * @return The concatenated string
	 */
	String operator+(const String& str) const;

	/**
	 * @brief Concatenate the string with a C string
	 * @param str The C string to concatenate to
	 * @return The concatenated string
	 */
	String operator+(const char* str) const;

	/**
	 * @brief Concatenate the string with an integer
	 * @param n The integer to concatenate to
	 * @return The concatenated string
	 */
	String operator+(int n) const;

	/**
	 * @brief Concatenate the string with a character
	 * @param ch The character to concatenate to
	 * @return The concatenated string
	 */
	String operator+(char ch) const;

	/**
	 * @brief Concatenate the string with a string
	 * @param str The string to concatenate to
	 * @return The concatenated string
	 */
	String operator+=(const String& str);

	/**
	 * @brief Concatenate the string with a character
	 * @param ch The character to concatenate to
	 * @return The concatenated string
	 */
	String operator+=(char ch);

	/**
	 * @brief Tests if the string is equal to another
	 * @param str The testing operand
	 * @return true if the two strings are equal, otherwise false
	 */
	bool operator==(const String& str) const;

	/**
	 * @brief Tests if the string is equal to another
	 * @param str The testing operand
	 * @return true if the two strings are equal, otherwise false
	 */
	bool operator==(const char* str) const;

	/**
	 * @brief Tests if the string is not equal to another
	 * @param str The testing operand
	 * @return true if the two strings are not equal, otherwise false
	 */
	bool operator!=(const String& str) const;

	/**
	 * @brief Tests if the string is not equal to another
	 * @param str The testing operand
	 * @return true if the two strings are not equal, otherwise false
	 */
	bool operator!=(const char* str) const;

	/**
	 * @brief Implicit conversion into const char*
	 */
	operator const char*() const;

	/**
	 * @brief Implicit conversion to int
	 */
	operator int() const;

	/**
	 * @brief Implicit conversion to float
	 */
	operator float() const;

	/**
	 * @brief Implicit conversion to bool
	 */
	operator bool() const;

	/**
	 * @brief Implicit conversion to std::string
	 */
	operator std::string() const;

	std::size_t hash() const;

	/**
	 * @brief Converts the string into C string
	 * @brief The C string
	 */
	const char* toCString() const;

	/**
	 * @brief Converts into std::string
	 * @return String converted to std::string
	 */
	std::string& toStdString();

	/**
	 * @brief Converts into std::string
	 * @return String converted to std::string
	 */
	std::string toStdString() const;

	/**
	 * @brief Converts into std::wstring
	 * @return String converted to std::wstring
	 */
	std::wstring toStdWString() const;

	/**
	 * @brief Determines if the string is empty
	 */
	bool isEmpty() const;

	/**
	 * @brief Determines if the string is null
	 */
	bool isNull() const;

public:
	static std::string stdWStringToStdString(const std::wstring& wstr);
	static String fromNumber(uint64_t n, int base = 10);
	static String fromUnicode(int pointCode);

private:
	bool _isNull;
};

std::ostream& operator<<(std::ostream& stream, const String& string);
std::istream& operator>>(std::istream& stream, String& string);
bool operator<(const String& l, const String& r);
bool operator>(const String& l, const String& r);
String operator+(const char* str1, const String& str2);

String operator%(const String& pattern, const StringList& args);
String operator%(const String& pattern, const String& arg1);

#include "Types/StringList.h"

#endif // !_TYPES_STRING_H_
