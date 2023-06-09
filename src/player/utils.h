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

#ifndef PLAYER_UTILS_H
#define PLAYER_UTILS_H

// Utility functions and constants

#include "defaults.h"

#include <vector>

// Coordinate permutation matrices for range 1-8.
// Used when scanning grid for enemies/movement.
// posy at index 0, posx at index 1
const std::vector<std::vector<int>> MOVE_1 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

const std::vector<std::vector<int>> MOVE_2 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}
};

const std::vector<std::vector<int>> MOVE_3 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3}
};

const std::vector<std::vector<int>> MOVE_4 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3},
    {1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {4, 0}, {-4, 0}, {0, 4}, {0, -4}
};

const std::vector<std::vector<int>> MOVE_5 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3},
    {1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {4, 0}, {-4, 0}, {0, 4}, {0, -4},
    {1, 4}, {1, -4}, {-1, 4}, {-1, -4}, {2, 3}, {2, -3}, {-2, 3}, {-2, -3},
    {3, 2}, {3, -2}, {-3, 2}, {-3, -2}, {4, 1}, {4, -1}, {-4, 1}, {-4, -1},
    {5, 0}, {-5, 0}, {0, 5}, {0, -5}
};

const std::vector<std::vector<int>> MOVE_6 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3},
    {1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {4, 0}, {-4, 0}, {0, 4}, {0, -4},
    {1, 4}, {1, -4}, {-1, 4}, {-1, -4}, {2, 3}, {2, -3}, {-2, 3}, {-2, -3},
    {3, 2}, {3, -2}, {-3, 2}, {-3, -2}, {4, 1}, {4, -1}, {-4, 1}, {-4, -1},
    {5, 0}, {-5, 0}, {0, 5}, {0, -5}, {1, 5}, {1, -5}, {-1, 5}, {-1, -5},
    {2, 4}, {2, -4}, {-2, 4}, {-2, -4}, {3, 3}, {3, -3}, {-3, 3}, {-3, -3},
    {4, 2}, {4, -2}, {-4, 2}, {-4, -2}, {5, 1}, {5, -1}, {-5, 1}, {-5, -1},
    {6, 0}, {-6, 0}, {0, 6}, {0, -6}
};

const std::vector<std::vector<int>> MOVE_7 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3},
    {1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {4, 0}, {-4, 0}, {0, 4}, {0, -4},
    {1, 4}, {1, -4}, {-1, 4}, {-1, -4}, {2, 3}, {2, -3}, {-2, 3}, {-2, -3},
    {3, 2}, {3, -2}, {-3, 2}, {-3, -2}, {4, 1}, {4, -1}, {-4, 1}, {-4, -1},
    {5, 0}, {-5, 0}, {0, 5}, {0, -5}, {1, 5}, {1, -5}, {-1, 5}, {-1, -5},
    {2, 4}, {2, -4}, {-2, 4}, {-2, -4}, {3, 3}, {3, -3}, {-3, 3}, {-3, -3},
    {4, 2}, {4, -2}, {-4, 2}, {-4, -2}, {5, 1}, {5, -1}, {-5, 1}, {-5, -1},
    {6, 0}, {-6, 0}, {0, 6}, {0, -6}, {1, 6}, {1, -6}, {-1, 6}, {-1, -6},
    {2, 5}, {2, -5}, {-2, 5}, {-2, -5}, {3, 4}, {3, -4}, {-3, 4}, {-3, -4},
    {4, 3}, {4, -3}, {-4, 3}, {-4, -3}, {5, 2}, {5, -2}, {-5, 2}, {-5, -2},
    {6, 1}, {6, -1}, {-6, 1}, {-6, -1}, {7, 0}, {-7, 0}, {0, 7}, {0, -7}
};

const std::vector<std::vector<int>> MOVE_8 = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {3, 0}, {-3, 0}, {0, 3}, {0, -3},
    {1, 3}, {1, -3}, {-1, 3}, {-1, -3}, {2, 2}, {2, -2}, {-2, 2}, {-2, -2},
    {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {4, 0}, {-4, 0}, {0, 4}, {0, -4},
    {1, 4}, {1, -4}, {-1, 4}, {-1, -4}, {2, 3}, {2, -3}, {-2, 3}, {-2, -3},
    {3, 2}, {3, -2}, {-3, 2}, {-3, -2}, {4, 1}, {4, -1}, {-4, 1}, {-4, -1},
    {5, 0}, {-5, 0}, {0, 5}, {0, -5}, {1, 5}, {1, -5}, {-1, 5}, {-1, -5},
    {2, 4}, {2, -4}, {-2, 4}, {-2, -4}, {3, 3}, {3, -3}, {-3, 3}, {-3, -3},
    {4, 2}, {4, -2}, {-4, 2}, {-4, -2}, {5, 1}, {5, -1}, {-5, 1}, {-5, -1},
    {6, 0}, {-6, 0}, {0, 6}, {0, -6}, {1, 6}, {1, -6}, {-1, 6}, {-1, -6},
    {2, 5}, {2, -5}, {-2, 5}, {-2, -5}, {3, 4}, {3, -4}, {-3, 4}, {-3, -4},
    {4, 3}, {4, -3}, {-4, 3}, {-4, -3}, {5, 2}, {5, -2}, {-5, 2}, {-5, -2},
    {6, 1}, {6, -1}, {-6, 1}, {-6, -1}, {7, 0}, {-7, 0}, {0, 7}, {0, -7},
    {1, 7}, {1, -7}, {-1, 7}, {-1, -7}, {2, 6}, {2, -6}, {-2, 6}, {-2, -6},
    {3, 5}, {3, -5}, {-3, 5}, {-3, -5}, {4, 4}, {4, -4}, {-4, 4}, {-4, -4},
    {5, 3}, {5, -3}, {-5, 3}, {-5, -3}, {6, 2}, {6, -2}, {-6, 2}, {-6, -2},
    {7, 1}, {7, -1}, {-7, 1}, {-7, -1}, {8, 0}, {-8, 0}, {0, 8}, {0, -8}
};

// Vector hasher for hash table with vector keys
struct VectorHasher {
    int operator()(const std::vector<int> &V) const;
};

#endif