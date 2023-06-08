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

#include "misc.fwd.h"

#include "actions.h"
#include "units.h"

#include <queue>

struct listUnits
{
    std::map<int, std::vector<std::vector<int>>> id2moveattackV;
    std::map<int, std::vector<std::vector<int>>> id2slowMoveV;
    std::map<int, std::vector<std::vector<int>>> id2attackV;
    std::map<int, std::vector<std::vector<int>>> id2moveV;
    std::map<int, std::unique_ptr<Unit>> units;
    std::map<int, std::map<char, int>> id2dmg;
    std::map<int, int> id2arange;
    std::map<int, char> id2type;
    std::map<int, int> id2speed;

    std::list<int> hitList;

    int qWorker = 0, qCatapult = 0, qRam = 0, qPikeman = 0, qArcher = 0;
    int qSwordsman = 0, qKnight = 0, qAll = 0;

    Base base;

    bool addBase(int ident, int end, int px, int py, char q);

    bool addUnit(char type, int ident, int end, int px, int py);

    bool addWorker(int ident, int end, int px, int py);
    bool addCatapult(int ident, int end, int px, int py);
    bool addRam(int ident, int end, int px, int py);
    bool addPikeman(int ident, int end, int px, int py);
    bool addArcher(int ident, int end, int px, int py);
    bool addSwordsman(int ident, int end, int px, int py);
    bool addKnight(int ident, int end, int px, int py);
    bool is_unique(int id);
};

int Dist(int xFirst, int yFirst, int xSecond, int ySecond);

#endif