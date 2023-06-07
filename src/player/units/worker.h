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

#ifndef PLAYER_UNITS_WORKER_H
#define PLAYER_UNITS_WORKER_H

#include "unit.h"

// Vector
#define listW std::vector<Worker>

// Build cost logic
#define CAN_GET_WORKER(x) (x >= 100)

// Damage
#define WORKER2KNIGHT 5
#define WORKER2SWORDSMAN 5
#define WORKER2ARCHER 5
#define WORKER2PIKEMAN 5
#define WORKER2CATAPULT 5
#define WORKER2RAM 5
#define WORKER2WORKER 5
#define WORKER2BASE 1

// Speed
#define SPEED_WORKER 2

// Attack Range
#define ATTACK_WORKER 1

class Worker : public Unit
{
public:
    Worker(int ident, int end, std::size_t px, std::size_t py);
    ~Worker();

    bool find_target(const grid &map);
};

#endif