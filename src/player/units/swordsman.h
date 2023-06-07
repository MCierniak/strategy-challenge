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

#ifndef PLAYER_UNITS_SWORDSMAN_H
#define PLAYER_UNITS_SWORDSMAN_H

#include "unit.h"

// Vector for units
#define listS std::vector<Swordsman>

// Build cost logic
#define CAN_GET_SWORDSMAN(x) (x >= 250)

// Damage
#define SWORDSMAN2KNIGHT 30
#define SWORDSMAN2SWORDSMAN 30
#define SWORDSMAN2ARCHER 30
#define SWORDSMAN2PIKEMAN 20
#define SWORDSMAN2CATAPULT 20
#define SWORDSMAN2RAM 30
#define SWORDSMAN2WORKER 30
#define SWORDSMAN2BASE 30

// Speed
#define SPEED_SWORDSMAN 2

// Attack Range
#define ATTACK_SWORDSMAN 1

class Swordsman : public Unit
{
public:
    Swordsman(int ident, int end, std::size_t px, std::size_t py);
    ~Swordsman();
};

#endif