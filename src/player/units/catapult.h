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

#ifndef PLAYER_UNITS_CATAPULT_H
#define PLAYER_UNITS_CATAPULT_H

#include "unit.h"

// Vector
#define listC std::vector<Catapult>

// Build cost logic
#define CAN_GET_CATAPULT(x) (x >= 800)

// Damage
#define CATAPULT2KNIGHT 40
#define CATAPULT2SWORDSMAN 40
#define CATAPULT2ARCHER 40
#define CATAPULT2PIKEMAN 40
#define CATAPULT2CATAPULT 40
#define CATAPULT2RAM 40
#define CATAPULT2WORKER 40
#define CATAPULT2BASE 50

// Speed
#define SPEED_CATAPULT 2

// Attack Range
#define ATTACK_CATAPULT 7

class Catapult : public Unit
{
public:
    Catapult(int ident, int end, std::size_t px, std::size_t py);
    ~Catapult();
};

#endif