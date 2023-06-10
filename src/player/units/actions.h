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

// Unit action logic. The main action_unit() functon calls the unit's find_target and determines what to do with it.

#include "../defaults.h"

#include "../path/bfs.h"
#include "misc.h"

// Macros for coordinate sorting
#define coord std::pair<int, int>
#define evade_queue_item std::pair<int, coord>
#define evade_queue std::priority_queue<evade_queue_item, std::vector<evade_queue_item>, std::greater<evade_queue_item>>

// Performs attack. Returns true if payload received a useful command.
bool attack(std::string &payload, int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Find nearest position outside of enemy range. Only used by workers. Returns true if payload received a useful command.
bool evade(std::string &payload, int sId, const grid &map, listUnits &allies);
// Defensive action - if unit wants to move within range of an enemy, this function will redirect to the nearest safe grid. Also ensures units will try to evade deadly damage.
bool cover(int sId, const grid &map, listUnits &allies, int &stepX, int &stepY);

// Main decision making functions
bool action_base(std::string &payload, long gold, const listUnits &allies, const listUnits &enemies);
bool action_unit(std::string &payload, int unitId, const grid &map, listUnits &allies, listUnits &enemies);

#endif