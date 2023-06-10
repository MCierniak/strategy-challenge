// Strategy Challenge Project
// Copyright (C) 2023 Mateusz Cierniak
//
// This file is part of Strategy Challenge Project.
//
// Strategy Challenge Project is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// Strategy Challenge Project is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Strategy Challenge Project. If not, see <http://www.gnu.org/licenses/>.

#ifndef PLAYER_DEFAULTS_H
#define PLAYER_DEFAULTS_H

// Uncomment for unit tests
// #define TESTING_TRUE

// Uncomment for verbosity
// #define VERBOSE_TRUE

// Time (in microseconds) needed for final cleanup
#define CLEANUP_TIME 10000

// Macros for wall time monitoring
#define DURATION(x) std::chrono::duration_cast<MICROSECONDS>(x).count()
#define CURRENT_TIME std::chrono::high_resolution_clock::now()
#define MICROSECONDS std::chrono::microseconds
#define SECONDS std::chrono::seconds

#endif