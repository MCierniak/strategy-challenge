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

#ifndef PLAYER_UNITS_PIKEMAN_H
#define PLAYER_UNITS_PIKEMAN_H

#include "unit.h"

// Vector
#define listP std::vector<Pikeman>

// Build cost logic
#define CAN_GET_PIKEMAN(x) (x >= 200)

// Damage
#define PIKEMAN2KNIGHT 35
#define PIKEMAN2SWORDSMAN 15
#define PIKEMAN2ARCHER 15
#define PIKEMAN2PIKEMAN 15
#define PIKEMAN2CATAPULT 15
#define PIKEMAN2RAM 10
#define PIKEMAN2WORKER 15
#define PIKEMAN2BASE 10

// Speed
#define SPEED_PIKEMAN 2

// Attack Range
#define ATTACK_PIKEMAN 2

class Pikeman : public Unit
{
public:
    Pikeman(int ident, int end, std::size_t px, std::size_t py);
    ~Pikeman();
};

#endif