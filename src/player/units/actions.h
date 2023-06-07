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

#ifndef PLAYER_UNITS_ACTIONS_H
#define PLAYER_UNITS_ACTIONS_H

#include "misc.h"

bool worker_attack(std::string &payload, Worker &unit, const grid &map, listUnits &enemies);

//Decision making functions
bool action(std::string &payload, const Base &unit, long gold, const listUnits &allies, const listUnits &enemies);
bool action(std::string &payload, Worker &unit, const grid &map, listUnits &enemies);
bool action(std::string &payload, Catapult &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Ram &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Pikeman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Archer &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Swordsman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Knight &unit, const grid &map, const listUnits &enemies);

#endif