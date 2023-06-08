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

#ifndef PLAYER_PATH_BFS_H
#define PLAYER_PATH_BFS_H

#include "../grid.h"

// Bredth-first search algorithm for map traversal. Returns false if there is no traversable path between s and t.
bool bfs_find_path(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);

#endif