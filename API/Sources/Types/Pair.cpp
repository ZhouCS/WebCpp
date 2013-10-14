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
 * @file Types/Pair.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-12-07
 */

template<typename F, typename S> Pair<F, S>::Pair() : std::pair<F, S>()
{ }

template<typename F, typename S> Pair<F, S>::Pair(const std::pair<F, S>& pair)
  : std::pair<F, S>(pair)
{ }

template<typename F, typename S> Pair<F, S>::Pair(const F& first,
                                                  const S& second)
  : std::pair<F, S>(first, second)
{ }

template<typename F, typename S> F Pair<F, S>::first() const
{ return std::pair<F, S>::first; }

template<typename F, typename S> S Pair<F, S>::second() const
{ return std::pair<F, S>::second; }
