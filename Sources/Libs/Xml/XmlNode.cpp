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
 * @file Libs/Xml/XmlNode.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-22
 */

#include "Libs/Xml/XmlNode.h"
#include "Types/List.h"

XmlNode::XmlNode(const pugi::xml_node& node)
{
	_node = node;
	_hasChildIterator = false;
}

XmlNode::XmlNode()
{ }


XmlNode XmlNode::firstChild() const
{ return _node.first_child(); }

XmlNode XmlNode::child(const String& nodeName) const
{ return _node.child(nodeName); }

List<XmlNode> XmlNode::childNodes() const
{
	List<XmlNode> list;
	for (pugi::xml_node node = _node.first_child();
	     node; node = node.next_sibling())
		list.append(node);
	return list;
}

std::vector<XmlNode>::iterator XmlNode::begin()
{
	_childIteratorList = childNodes();
	return _childIteratorList.begin();
}

std::vector<XmlNode>::iterator XmlNode::end()
{ return _childIteratorList.end(); }

String XmlNode::attribute(const String& attrName) const
{ return _node.attribute(attrName).value(); }

String XmlNode::text() const
{ return _node.first_child().value(); }

//----------------------------------------------------------------------------//

void XmlNode::setNode(const pugi::xml_node& node)
{ _node = node; }
