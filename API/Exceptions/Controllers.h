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
 * @file Exceptions/Controllers.h
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-02-17
 */

#ifndef _EXCEPTIONS_CONTROLLERS_H_
#define	_EXCEPTIONS_CONTROLLERS_H_

#include "Exceptions/Exception.h"

#include "MVC/Controller.h"

namespace Exceptions {

EXCEPTION(NoSuchController,
          String("There is no controller named “%1”").format(wrongName),
          const String& wrongName)

EXCEPTION(NoSuchControllerAction,
          String("There is no action “%1” in controller “%2”")
          .format({wrongAction, controller->fullId()}),
          Controller* controller, const String& wrongAction)

}

#endif // !_EXCEPTIONS_CONTROLLERS_H_
