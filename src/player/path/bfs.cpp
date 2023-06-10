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

#include "bfs.h"

bool bfs_find_path(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    if (sY < 0 || sY >= int(map.size())) return false; // out of bounds guard
    if (sX < 0 || sX >= int(map[0].size())) return false;
    if (tY < 0 || tY >= int(map.size())) return false;
    if (tX < 0 || tX >= int(map[0].size())) return false;
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false)); // array of visited nodes
    std::queue<std::vector<int>> gridQ; // grid queue

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths; // output path

    gridQ.push(std::vector<int>{sY, sX}); // push current position to queue
    visited[sY][sX] = true; // mark as visited

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.front(); // get front of the queue
        gridQ.pop(); // remove front element

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1]; // iterate over connected nodes

            if (newYi < 0 || newYi >= int(map.size())) continue; // out of bounds, traversability and visited flag check
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;
            if (visited[newYi][newXi]) continue;

            visited[newYi][newXi] = true; // mark as visited
            gridQ.push(std::vector<int>{newYi, newXi}); // push connected nodes to queue 

            paths[std::vector<int>{newYi, newXi}] = current; // connect new node with previous

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