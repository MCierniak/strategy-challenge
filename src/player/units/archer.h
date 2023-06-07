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

#ifndef PLAYER_UNITS_ARCHER_H
#define PLAYER_UNITS_ARCHER_H

#include "unit.h"

// Vector for units
#define listA std::vector<Archer>

// Build cost logic
#define CAN_GET_ARCHER(x) (x >= 250)

// Damage
#define ARCHER2KNIGHT 15
#define ARCHER2SWORDSMAN 15
#define ARCHER2ARCHER 15
#define ARCHER2PIKEMAN 15
#define ARCHER2CATAPULT 10
#define ARCHER2RAM 10
#define ARCHER2WORKER 15
#define ARCHER2BASE 15

// Speed
#define SPEED_ARCHER 2

// Attack Range
#define ATTACK_ARCHER 5

class Archer : public Unit
{
public:
    Archer(int ident, int end, std::size_t px, std::size_t py);
    ~Archer();
};

#endif