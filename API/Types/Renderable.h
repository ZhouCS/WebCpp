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
 * @file Types/Renderable.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-24
 */

#ifndef _TYPES_RENDERABLE_H_
#define _TYPES_RENDERABLE_H_

#include "Types/Variant.h"
#include "Types/StringList.h"

#include <string>

class String;
template<typename T> class List;
template<typename Key, typename Value> class Map;

/**
 * @class Renderable Types/Renderable.h <Renderable>
 * @brief A data type which can be rendered into a template view
 */
class Renderable : public Variant
{
public:
	enum class Type{None, String, Int, LongUInt, Float, Bool, List, Map};
	
	Renderable();
	
	virtual ~Renderable();
	
	/**
	 * @brief Constructs a renderable data type
	 * @param typeId The data type ID
	 */
	Renderable(const String& val);
	
	Renderable(const char* val);
	
	Renderable(int val);
	
	Renderable(long unsigned int val);
	
	Renderable(float val);
	
	Renderable(bool val);
	
	Renderable(const List<Renderable>& list);
	
	Renderable(const StringList& list);
	
	Renderable(const Map<String, Renderable>& map);
	
	/**
	 * @brief Implements how to copy the data
	 * @return A dynamicaly allocated pointer to a copy of the data
	 */
	virtual Variant* copy() const;
	
	/**
	 * @brief Implements how to render the data into the template view
	 * @return The rendered data as string
	 */
	virtual String render() const;
	
	Type type() const;
	
	//void* val() const;
	template<typename T> T value() const
	{ return *static_cast<T*>(_val); }
	
	template<typename T> T* valuePtr() const
	{ return static_cast<T*>(_val); }
	
	String toString() const;
	
	bool toBool() const;
	
	int toInt() const;
	
	/**
	 * @brief Implements how to dump the data for debugging as HTML string
	 * @return The dumped data as HTML string
	 */
	virtual String htmlDump() const;
	
	bool operator>(const Renderable& right) const;
	bool operator>=(const Renderable& right) const;
	bool operator<(const Renderable& right) const;
	bool operator<=(const Renderable& right) const;
	
	bool operator==(const Renderable& right) const;

private:
	Type _type;
	
	void* _val;
};

#endif // !_TYPES_RENDERABLE_H_
