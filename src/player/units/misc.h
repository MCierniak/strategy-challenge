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

#ifndef PLAYER_UNITS_MISC_H
#define PLAYER_UNITS_MISC_H

// Misc functions, target finders and listUnits struct

#include "misc.fwd.h"

#include "actions.h"
#include "units.h"

#include <queue>

// List of own/enemy units
struct listUnits
{
    // Translate id to permutation vector (utils.h) for movement+attack
    std::map<int, std::vector<std::vector<int>>> id2moveattackV;
    // Translate id to permutation vector (utils.h) for movement-1
    std::map<int, std::vector<std::vector<int>>> id2slowMoveV;
    // Translate id to permutation vector (utils.h) for attack range
    std::map<int, std::vector<std::vector<int>>> id2attackV;
    // Translate id to permutation vector (utils.h) for movement
    std::map<int, std::vector<std::vector<int>>> id2moveV;
    // Main list of units (excluding base)
    std::map<int, std::unique_ptr<Unit>> units;
    // Damage map for each unit (used to decrement enemy endurance after attack has been issued)
    std::map<int, std::map<char, int>> id2dmg;
    // Translate id to attack range
    std::map<int, int> id2arange;
    // Translate id to unit type
    std::map<int, char> id2type;
    // Translate id to unit speed
    std::map<int, int> id2speed;

    // Only for list of enemy units, the hitList is sorted by distance to own base, ascending
    std::list<int> hitList;

    // Total number of each unit type
    int qWorker = 0, qCatapult = 0, qRam = 0, qPikeman = 0, qArcher = 0;
    int qSwordsman = 0, qKnight = 0, qAll = 0;

    // The base
    Base base;

    // Method to add a base. Id uniqness is ensured
    bool addBase(int ident, int end, int px, int py, char q);

    // Method to add units other than base. Id uniqness is ensured
    bool addUnit(char type, int ident, int end, int px, int py);

    // Method to add workers. Id uniqness is ensured
    bool addWorker(int ident, int end, int px, int py);
    // Method to add catapults. Id uniqness is ensured
    bool addCatapult(int ident, int end, int px, int py);
    // Method to add ram. Id uniqness is ensured
    bool addRam(int ident, int end, int px, int py);
    // Method to add pikeman. Id uniqness is ensured
    bool addPikeman(int ident, int end, int px, int py);
    // Method to add archer. Id uniqness is ensured
    bool addArcher(int ident, int end, int px, int py);
    // Method to add swordsman. Id uniqness is ensured
    bool addSwordsman(int ident, int end, int px, int py);
    // Method to add knight. Id uniqness is ensured
    bool addKnight(int ident, int end, int px, int py);
    // Id uniqness test 
    bool is_unique(int id);
};

// Distance between First and Second
int Dist(int xFirst, int yFirst, int xSecond, int ySecond);

#endif