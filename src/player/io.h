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

#ifndef PLAYER_IO_H
#define PLAYER_IO_H

// Functions responsible for parsin input and output files

#include "defaults.h"

#include "units/misc.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Parse map from file, output parsed map and X,Y size
bool get_map(const std::string &map_path, grid &map, int &X, int &Y);
// Parse status from file, output rosters of own and enemy units
bool get_status(const std::string &status_path, grid &map, long &gold, listUnits &myTeam, listUnits &enemy);

#endif