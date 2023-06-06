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

#include "grid.h"

std::size_t resource::unusedResourceCount = 0;
std::list<std::vector<std::size_t>> resource::resNodeList = std::list<std::vector<std::size_t>>();

bool gridObj::checkTrav()
{
    return this->isTraversable;
}

bool gridObj::checkResource()
{
    return this->isResource;
}

void gridObj::addDmg2Knight(int dmg)
{
    this->dmg2Knight += dmg;
}

void gridObj::addDmg2Swordsman(int dmg)
{
    this->dmg2Swordsman += dmg;
}

void gridObj::addDmg2Archer(int dmg)
{
    this->dmg2Archer += dmg;
}

void gridObj::addDmg2Pikeman(int dmg)
{
    this->dmg2Pikeman += dmg;
}

void gridObj::addDmg2Catapult(int dmg)
{
    this->dmg2Catapult += dmg;
}

void gridObj::addDmg2Ram(int dmg)
{
    this->dmg2Ram += dmg;
}

void gridObj::addDmg2Worker(int dmg)
{
    this->dmg2Worker += dmg;
}

void gridObj::addEnemyId(int id)
{
    this->enemyIds.push_back(id);
    this->isTraversable = false;
}

std::size_t gridObj::checkEnemyNr()
{
    return this->enemyIds.size();
}

int gridObj::checkDmgKnight()
{
    return this->dmg2Knight;
}

int gridObj::checkDmgSwordsman()
{
    return this->dmg2Swordsman;
}

int gridObj::checkDmgArcher()
{
    return this->dmg2Archer;
}

int gridObj::checkDmgPikeman()
{
    return this->dmg2Pikeman;
}

int gridObj::checkDmgCatapult()
{
    return this->dmg2Catapult;
}

int gridObj::checkDmgRam()
{
    return this->dmg2Ram;
}

int gridObj::checkDmgWorker()
{
    return this->dmg2Worker;
}

std::vector<int>& gridObj::getEnemyId()
{
    return this->enemyIds;
}

int gridObj::getEnemyId(std::size_t i)
{
    return this->enemyIds[i];
}

std::size_t resource::getUnusedResourceCount()
{
    return resource::unusedResourceCount;
}

void resource::addEnemyId(int id)
{
    this->enemyIds.push_back(id);
    this->isTraversable = false;
    unusedResourceCount -= 1;
}

void gridObj::addWorkerId(int id)
{
    this->workerIds.push_back(id);
}

void resource::addWorkerId(int id)
{
    this->workerIds.push_back(id);
    unusedResourceCount -= 1;
}

std::vector<int>& gridObj::getWorkerId()
{
    return this->workerIds;
}

int gridObj::getWorkerId(std::size_t i)
{
    return this->workerIds[i];
}

std::vector<int>& resource::getWorkerId()
{
    return this->workerIds;
}

int resource::getWorkerId(std::size_t i)
{
    return this->workerIds[i];
}

std::string emptySpace::print()
{
    if (this->isTraversable) return std::string("e");
    else return std::string("e(x)");
}

std::string resource::print()
{
    if (this->isTraversable) return std::string("r");
    else return std::string("r(x)");
}

std::string barrier::print()
{
    return std::string("b(x)");
}

gridObj::gridObj(bool traversible, bool resource, std::size_t px, std::size_t py):
    isTraversable(traversible), isResource(resource), posx(px), posy(py)
{}

emptySpace::emptySpace(std::size_t px, std::size_t py):
    gridObj(true, false, px, py)
{}

resource::resource(std::size_t px, std::size_t py):
    gridObj(true, true, px, py)
{
    resource::resNodeList.push_back(std::vector<size_t>{py, px});
    resource::unusedResourceCount += 1;
}

barrier::barrier(std::size_t px, std::size_t py):
    gridObj(false, false, px, py)
{}

emptySpace::~emptySpace(){}

resource::~resource(){}

barrier::~barrier(){}

struct my_comparator
{
    // queue elements are vectors so we need to compare those
    bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
    {
        return a[2] > b[2];
    }
};

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

bool dijkstra_find_path_knight(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgKnight();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_swordsman(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgSwordsman();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_archer(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgArcher();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_pikeman(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgPikeman();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_ram(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgRam();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_catapult(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgCatapult();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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

bool dijkstra_find_path_worker(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed)
{
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), 100000000));
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;

    std::unordered_map<std::vector<int>, std::vector<int>, VectorHasher> paths;

    // Current Y, current X, weight
    gridQ.push(std::vector<int>{sY, sX, 0});
    weight[sY][sX] = 0;

    while(!gridQ.empty())
    {
        std::vector<int> current = gridQ.top();
        gridQ.pop();

        for (auto &&mod : speed)
        {
            int newYi = current[0] + mod[0], newXi = current[1] + mod[1];

            if (newYi < 0 || newYi >= int(map.size())) continue;
            if (newXi < 0 || newXi >= int(map[newYi].size())) continue;
            if (!map[newYi][newXi]->checkTrav()) continue;

            int newWeight = current[2] + map[newYi][newXi]->checkDmgWorker();

            if (weight[newYi][newXi] < newWeight) continue;
            
            weight[newYi][newXi] = newWeight;
            
            gridQ.push(std::vector<int>{newYi, newXi, newWeight});

            paths[std::vector<int>{newYi, newXi}] = std::vector<int>{current[0], current[1]};

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