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
 * @file Requests/RequestProfile.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2012-07-15
 */

#include "Requests/RequestProfile.h"

uint8_t RequestProfile::_counter = 0;
Map<uint8_t, RequestProfile*> RequestProfile::_profiles;

RequestProfile::RequestProfile()
{
	_id = _counter++;
	if (_profiles.hasKey(_id))
		delete _profiles[_id];
	_profiles[_id] = this;
}

void RequestProfile::addChronoTime(RequestProfile::Chrono chrono, double time)
{
	if (!_chronos.hasKey((int)chrono))
		_chronos[(int)chrono] = 0;
	_chronos[(int)chrono] += time;
}

void RequestProfile::incrementCounter(Counter counter, int value)
{
	if (!_counters.hasKey((int)counter))
		_counters[(int)counter] = 0;
	_counters[(int)counter] += value;
}

//----------------------------------------------------------------------------//

double RequestProfile::chronoTime(RequestProfile::Chrono chrono) const
{
	if (!_chronos.hasKey((int)chrono))
		return 0.0;
	return _chronos[(int)chrono];
}

int RequestProfile::counter(Counter counter) const
{
	if (!_counters.hasKey((int)counter))
		return 0;
	return _counters[(int)counter];
}

RequestProfile* RequestProfile::profile(uint8_t id)
{ return _profiles.get(id, nullptr); }

void RequestProfile::deleteProfiles()
{
	for (Map<uint8_t, RequestProfile*>::Iterator i(_profiles); i.hasNext(); i++)
		delete i.value();
}

uint8_t RequestProfile::id() const
{ return _id; }
