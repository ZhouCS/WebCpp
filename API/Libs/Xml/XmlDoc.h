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
 * @file Libs/Xml/XmlDoc.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-21
 */

#ifndef _WPP_LIBS_XML_XMLDOC_H_
#define	_WPP_LIBS_XML_XMLDOC_H_

#include "Libs/Xml/XmlNode.h"

#include <pugixml.hpp>

class Path;

/**
 * @class XmlDoc Libs/Xml/XmlDoc.h <XmlDoc>
 * @brief An XML document
 */
class XmlDoc : public XmlNode
{
public:
	XmlDoc(const Path& filePath);

private:
	pugi::xml_document _doc;
};

#endif // !_WPP_LIBS_XML_XMLDOC_H_
