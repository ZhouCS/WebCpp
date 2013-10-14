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
 * @file Main.cpp
 * @author Kévin Lesénéchal <kevin@lesenechal.org>
 * @date 2011-11-19
 */

#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "System.h"
#include "Types/StringList.h"

/**
 * @brief The WebCpp main function
 * @param argc The arguments count
 * @param argv The arguments list
 * @return 0 on success, 1 on failure
 */
int main(int argc, const char** argv)
{
#ifndef BIG_SECURITY_HOLE
	if (geteuid() == 0)
	{
		std::cerr << "This program mustn't be run as root "
		          << "for obvious security reasons." << std::endl
		          << "If you still want to do so, recompile WebCpp "
		          << "with \"BIG_SECURITY_HOLE\" macro defined." << std::endl;
		return 1;
	}
#endif

	StringList args;
	for (int i = 0; i < argc; i++)
		args.append(argv[i]);

	int retCode = System::get()->run(args);
	delete System::get();
	pthread_exit(nullptr); // Workaround to a Valgrind's bug
	return retCode;
}
