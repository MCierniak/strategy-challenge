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

#include "ram.h"
#include "base.h"
#include "worker.h"
#include "archer.h"
#include "knight.h"
#include "pikeman.h"
#include "catapult.h"
#include "swordsman.h"

struct listUnits
{
    listW workers;
    listC catapults;
    listR rams;
    listP pikemen;
    listA archers;
    listS swordsmen;
    listK knights;
    listB bases;

    int unitCount = 0;

    std::unordered_map<int, char> id2type;
    std::unordered_map<int, int> id2hp;
    std::unordered_map<int, int> id2ind;

    bool addUnit(Worker &unit);
    bool addUnit(Catapult &unit);
    bool addUnit(Ram &unit);
    bool addUnit(Pikeman &unit);
    bool addUnit(Archer &unit);
    bool addUnit(Swordsman &unit);
    bool addUnit(Knight &unit);
    bool addUnit(Base &unit);

    bool is_unique(int id);
};

int Dist(Unit *first, Unit *second);
int Dist(Unit *first, int xSecond, int ySecond);
int Dist(int xFirst, int yFirst, int xSecond, int ySecond);

#endif