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
 * @file Libs/Xml/XmlNode.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-22
 */

#ifndef _WPP_LIBS_XML_XMLNODE_H_
#define	_WPP_LIBS_XML_XMLNODE_H_

#include <pugixml.hpp>

#include <vector>

#include "Types/List.h"

template<typename T> class List;
class String;

/**
 * @class XmlNode Libs/Xml/XmlNode.h <XmlNode>
 * @brief An XML node
 */
class XmlNode
{
public:
	/**
	 * @brief Constructs an XML node
	 * @param node The Pugixml node
	 */
	XmlNode(const pugi::xml_node& node);

	/**
	 * @brief Get the node's first child
	 */
	XmlNode firstChild() const;

	/**
	 * @brief Get the first child named @p nodeName
	 * @param nodeName The node name
	 * @return The first child named @p nodeName
	 */
	XmlNode child(const String& nodeName) const;

	/**
	 * @brief Get the childs list
	 */
	List<XmlNode> childNodes() const;

	/**
	 * @brief The starting iterator for node's childs
	 */
	std::vector<XmlNode>::iterator begin();

	/**
	 * @brief The ending iterator for node's childs
	 */
	std::vector<XmlNode>::iterator end();

	/**
	 * @brief Get an attribute value
	 * @param attrName The attribute name
	 * @return The value of attribute @p attrName
	 */
	String attribute(const String& attrName) const;

	/**
	 * @brief Get the node text content
	 */
	String text() const;

protected:
	XmlNode();

	void setNode(const pugi::xml_node& node);

private:
	/**
	 * @brief The Pugixml node
	 */
	pugi::xml_node _node;

	bool _hasChildIterator;

	List<XmlNode> _childIteratorList;
};

#endif // !_WPP_LIBS_XML_XMLNODE_H_
