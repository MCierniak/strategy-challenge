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

#include "../path/dijkstra.h"
#include "misc.h"

#define coord std::pair<int, int>
#define evade_queue_item std::pair<int, coord>
#define evade_queue std::priority_queue<evade_queue_item, std::vector<evade_queue_item>, std::greater<evade_queue_item>>

bool find_target_worker(int sId, const grid &map, listUnits &allies);
bool find_target_ram(int sId, const grid &map, listUnits &allies, const listUnits &enemies);
bool find_target_knight(int sId, const grid &map, listUnits &allies, const listUnits &enemies);
bool find_target_pikeman(int sId, const grid &map, listUnits &allies, const listUnits &enemies);
bool find_target_archer(int sId, const grid &map, listUnits &allies, const listUnits &enemies);
bool find_target_catapult(int sId, const grid &map, listUnits &allies, const listUnits &enemies);
bool find_target_swordsman(int sId, const grid &map, listUnits &allies, const listUnits &enemies);

bool attack(std::string &payload, int sId, const grid &map, listUnits &allies, listUnits &enemies);
bool evade(std::string &payload, int sId, const grid &map, listUnits &allies);

//Decision making functions
bool action_base(std::string &payload, long gold, const listUnits &allies, const listUnits &enemies);
bool action_unit(std::string &payload, int unitId, const grid &map, listUnits &allies, listUnits &enemies);

bool action(std::string &payload, Catapult &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Ram &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Pikeman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Archer &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Swordsman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, Knight &unit, const grid &map, const listUnits &enemies);

#endif