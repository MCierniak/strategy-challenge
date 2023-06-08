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
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
    std::queue<std::vector<int>> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    gridQ.push(std::vector<int>{sY, sX});
    visited[sY][sX] = true;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.front();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;
            if (visited[newYi][newXi]) continue;

            visited[newYi][newXi] = true;
            gridQ.push(std::vector<int>{newYi, newXi});

            paths[std::vector<int>{newYi, newXi}] = current;

            if (newYi == tY && newXi == tX)
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