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

#ifndef PLAYER_UNITS_RAM_H
#define PLAYER_UNITS_RAM_H

#include "unit.h"

// Vector
#define listR std::vector<Ram>

// Build cost logic
#define CAN_GET_RAM(x) (x >= 500)

// Damage
#define RAM2KNIGHT 10
#define RAM2SWORDSMAN 10
#define RAM2ARCHER 10
#define RAM2PIKEMAN 10
#define RAM2CATAPULT 10
#define RAM2RAM 10
#define RAM2WORKER 10
#define RAM2BASE 50

// Speed
#define SPEED_RAM 2

// Attack range
#define ATTACK_RAM 1

class Ram : public Unit
{
public:
    Ram(int ident, int end, std::size_t px, std::size_t py);
    ~Ram();
};

#endif