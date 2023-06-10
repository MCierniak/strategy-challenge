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

// Initialize static variables
int resource::unusedResourceCount = 0;
std::list<std::vector<int>> resource::resNodeList = std::list<std::vector<int>>();

gridObj::gridObj(bool traversible, bool resource):
    isTraversable(traversible), isResource(resource)
{
    // Set initial dmg count to 1 (0 could potentially cause problems with dijkstra's path finding algo)
    dmg['W'] = 1;
    dmg['S'] = 1;
    dmg['K'] = 1;
    dmg['P'] = 1;
    dmg['C'] = 1;
    dmg['R'] = 1;
    dmg['A'] = 1;
}

emptySpace::emptySpace():
    gridObj(true, false)
{}

resource::resource(int px, int py):
    gridObj(true, true), posx(px), posy(py)
{
    // Increment static unusedResourceCount, save node position in resNodeList
    resource::resNodeList.push_back(std::vector<int>{posy, posx});
    unusedResourceCount += 1;
}

barrier::barrier():
    gridObj(false, false)
{}

bool gridObj::checkTrav()
{
    return this->isTraversable;
}

bool gridObj::checkResource()
{
    return this->isResource;
}

void gridObj::addDmg(char key, int val)
{
    // Increment potential damage indicator
    this->dmg[key] += val;
}

void gridObj::addEnemyId(int id)
{
    for (auto &&el : this->enemyIds) if (el == id) return; // check id uniqness
    this->enemyIds.push_back(id); // add enemy id to enemyIds vector
    this->isTraversable = false; // set traversible flag to false
}

int gridObj::checkEnemyNr()
{
    return this->enemyIds.size();
}

int gridObj::checkDmg(char key)
{
    return this->dmg[key];
}

std::vector<int>& gridObj::getEnemyId()
{
    return this->enemyIds;
}

int gridObj::getEnemyId(int i)
{
    return this->enemyIds[i];
}

void resource::addEnemyId(int id)
{
    for (auto &&el : this->enemyIds) if (el == id) return; // check id uniqness
    this->enemyIds.push_back(id); // add enemy id to enemyIds vector
    this->isTraversable = false; // set traversible flag to false
    if (this->enemyIds.size() == 1) unusedResourceCount -= 1; // reduce unusedResourceCount, workers should not try to use resource nodes occupied by enemies
}

void gridObj::addWorkerId(int id)
{
    for (auto &&el : this->workerIds) if (el == id) return; // check id uniqness
    this->workerIds.push_back(id); // add worker id to workerIds vector
}

void gridObj::removeWorkerId(int id)
{
    this->workerIds.erase(std::remove(this->workerIds.begin(), this->workerIds.end(), id), this->workerIds.end());
}

void resource::addWorkerId(int id)
{
    for (auto &&el : this->workerIds) if (el == id) return; // check id uniqness
    this->workerIds.push_back(id); // add worker id to workerIds vector
    if (this->isTraversable && this->workerIds.size() == 1) unusedResourceCount -= 1; // reduce unusedResourceCount, workers should try to disperse rather than converge to one node
}

void resource::removeWorkerId(int id)
{
    this->workerIds.erase(std::remove(this->workerIds.begin(), this->workerIds.end(), id), this->workerIds.end());
    if (this->workerIds.size() == 0) unusedResourceCount += 1; // if no more workers on resource node, increment unusedResourceCount
}

std::vector<int>& gridObj::getWorkerId()
{
    return this->workerIds;
}

int gridObj::getWorkerId(int i)
{
    return this->workerIds[i];
}

int resource::getUnusedResourceCount()
{
    return resource::unusedResourceCount;
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

emptySpace::~emptySpace(){}

resource::~resource(){
    if (this->workerIds.size() == 0 && this->enemyIds.size() == 0 && this->isTraversable) unusedResourceCount -= 1; // if resource was unused, decrement unusedResourceCount on destruction
    resNodeList.remove(std::vector<int>{posy, posx}); // remove coords from resNodeList
}

barrier::~barrier(){}