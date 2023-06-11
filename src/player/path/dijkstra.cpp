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

#include "dijkstra.h"

bool dijkstra_find_path(int unitId, listUnits &units, const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY)
{
    if (sY < 0 || sY >= int(map.size())) return false; // out of bounds guard
    if (sX < 0 || sX >= int(map[0].size())) return false;
    if (tY < 0 || tY >= int(map.size())) return false;
    if (tX < 0 || tX >= int(map[0].size())) return false;
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000)); // array of node weights
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ; // grid queue (priority to closest path)

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths; // output path

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0}); // push current position to queue
    weight[sY][sX] = 0; // set weight to 0

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top(); // get front of the queue
        gridQ.pop(); // remove front element

        for (auto &&mod : units.id2moveV[unitId])
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1]; // iterate over connected nodes

            if (newYi < 0 || newYi >= int(map.size())) continue; // out of bounds and traversability check
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmg(units.id2type[unitId]); // determine node priority using distance and enemy attack potential

            if (weight[newYi][newXi] < newWeight) continue; // if already visited via a shorter path, continue
            
            weight[newYi][newXi] = newWeight; // otherwise determine weight and push connected nodes to queue 
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]}; // connect new node with previous

            if (newYi == tY && newXi == tX) // if target was found, traverse paths backwards until current position is found, determine next step and return
            {
                std::vector<int> pCurr{tY, tX};
                while (!(pCurr[0] == sY && pCurr[1] == sX))
                {
                    resX = pCurr[1];
                    resY = pCurr[0];
                    pCurr = paths[pCurr];
                }
                return true;
            }
        }
    }
    // Return false if there is no unblocked path.
    return false;
}