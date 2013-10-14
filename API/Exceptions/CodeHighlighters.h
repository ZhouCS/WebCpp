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
 * @file Exceptions/CodeHighlighters.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-05-26
 */

#ifndef _EXCEPTIONS_CODEHIGHLIGHTERS_H_
#define	_EXCEPTIONS_CODEHIGHLIGHTERS_H_

#include "Exceptions/Exception.h"

namespace Exceptions {

class NoSuchCodeHighlighter : public Exception
{
public:
	NoSuchCodeHighlighter(const String& id)
	  : Exception("NoSuchCodeHighlighter",
	              String("There is no code highlighter with ID “%1”").format(id))
	{}
};

}

#endif // !_EXCEPTIONS_CODEHIGHLIGHTERS_H_
