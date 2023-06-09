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

#ifndef PLAYER_PATH_DIJKSTRA_H
#define PLAYER_PATH_DIJKSTRA_H

#include "../defaults.h"

#include "../units/misc.h"

#include "../grid.h"

struct my_comparator
{
    bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
    {
        return a[2] > b[2];
    }
};

// Dijkstra's search algorithm for map traversal. Returns false if there is no traversable path between s and t.
// Slower than BFS.
bool dijkstra_find_path(int unitId, listUnits &units, const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY);

#endif