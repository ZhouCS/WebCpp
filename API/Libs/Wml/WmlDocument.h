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
 * @file Libs/Wml/WmlDocument.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-03-24
 */

#ifndef _WPP_LIBS_WML_WMLDOCUMENT_H_
#define	_WPP_LIBS_WML_WMLDOCUMENT_H_

#include <yaml.h>

class Path;

/**
 * @class WmlDocument Libs/Wml/WmlDocument.h <WmlDocument>
 * @brief A WML document (YAML with tabs)
 */
class WmlDocument
{
public:
	WmlDocument(const Path& filePath);

	~WmlDocument();

private:
	yaml_parser_t _parser;
};

#endif // !_WPP_LIBS_WML_WMLDOCUMENT_H_
