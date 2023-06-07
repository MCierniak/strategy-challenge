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

#ifndef PLAYER_UNITS_KNIGHT_H
#define PLAYER_UNITS_KNIGHT_H

#include "unit.h"

// Vector for units
#define listK std::vector<Knight>

// Build cost logic
#define CAN_GET_KNIGHT(x) (x >= 400)

// Damage
#define KNIGHT2KNIGHT 35
#define KNIGHT2SWORDSMAN 35
#define KNIGHT2ARCHER 35
#define KNIGHT2PIKEMAN 35
#define KNIGHT2CATAPULT 35
#define KNIGHT2RAM 50
#define KNIGHT2WORKER 35
#define KNIGHT2BASE 35

// Speed
#define SPEED_KNIGHT 5

// Attack Range
#define ATTACK_KNIGHT 1

class Knight : public Unit
{
public:
    Knight(int ident, int end, std::size_t px, std::size_t py);
    ~Knight();
};

#endif