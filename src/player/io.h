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

#ifndef IO_H
#define IO_H

#include "units.h"
#include "grid.h"

#include <iostream>
#include <fstream>
#include <cstring>

// Parse map from file, output parsed map and X,Y size
grid get_map(char map_path[], int &X, int &Y);
// Parse status from file, output rosters of own and enemy units
bool get_status(char status_path[], unitRoster &myTeam, unitRoster &enemy, long &gold);

// get_map unit test
void test_get_map();

#endif