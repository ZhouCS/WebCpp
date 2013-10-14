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
 * @file Libs/Wml/WmlDocument.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-03-24
 */

#include "Libs/Wml/WmlDocument.h"
#include "Libs/IO/File.h"

#include "Types/ByteArray.h"

WmlDocument::WmlDocument(const Path& filePath)
{
	String src = File::getContent(filePath);
	src = src.replace("\t", "    ");

	yaml_parser_initialize(&_parser);
	yaml_parser_set_input_string(&_parser,
	                             reinterpret_cast<const unsigned char*>(
	                               src.toCString()), src.size());
}

WmlDocument::~WmlDocument()
{
	yaml_parser_delete(&_parser);
}
