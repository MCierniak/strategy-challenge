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

#ifndef PLAYER_UNITS_UNIT_H
#define PLAYER_UNITS_UNIT_H

#include "../grid.h"
#include "../utils.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

// Abstract interface for units
class Unit
{
public:
    // Unit id
    const int id;
    // Unit HP
    int endurance;
    // Unit position
    std::size_t posx, posy;
    // Coordinates of the target
    std::size_t trgtX, trgtY;
    
    Unit(int ident, int end, std::size_t px, std::size_t py);
    virtual ~Unit() = 0;
};

#endif