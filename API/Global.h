/********************************************************************************
 * Copyright © 2011 Kévin Lesénéchal <kevin.lesenechal@bilbax.com>              *
 *                                                                              *
 * This file is part of WebCpp, see <http://www.webcpp.org/>.                   *
 *                                                                              *
 * * WebCpp is free software: you can redistribute it and/or modify it     **
 * it under the terms of the GNU Affero General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or            *
 * (at your option) any later version.                                          *
 *                                                                              *
 * This program is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 * GNU Affero General Public License for more details.                          *
 *                                                                              *
 * You should have received a copy of the GNU Affero General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 ********************************************************************************/

/**
 * \file Global.h
 * \author Kévin Lesénéchal
 * \date 2011-11-25
 * 
 * This file must be included everywhere, it loads the basic tools of the framework such as
 * String, List, Map, etc. It also defines global wide types, macros and functions.
 */

#ifndef _GLOBAL_H
#define _GLOBAL_H

//#error "Don't include that file"

//———————— Define global types ————————

#include <stdint.h>

typedef int8_t		int8;
typedef int16_t		int16;
typedef int32_t		int32;
typedef int64_t		int64;

typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

//—————————————————————————————————————

//———— General classes inclusions —————

#include "Types/Variant.h"
#include "Types/Renderable.h"

#include "Types/List.h"
#include "Types/String.h"
#include "Types/StringList.h"
#include "Types/Map.h"

#endif
