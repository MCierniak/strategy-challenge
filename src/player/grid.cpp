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

int resource::unusedResourceCount = 0;
std::list<std::vector<int>> resource::resNodeList = std::list<std::vector<int>>();

gridObj::gridObj(bool traversible, bool resource):
    isTraversable(traversible), isResource(resource)
{
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
    gridObj(true, true)
{
    resource::resNodeList.push_back(std::vector<int>{py, px});
    resource::unusedResourceCount += 1;
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
    this->dmg[key] += val;
}

void gridObj::addEnemyId(int id)
{
    this->enemyIds.push_back(id);
    this->isTraversable = false;
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

int resource::getUnusedResourceCount()
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

int gridObj::getWorkerId(int i)
{
    return this->workerIds[i];
}

std::vector<int>& resource::getWorkerId()
{
    return this->workerIds;
}

int resource::getWorkerId(int i)
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

emptySpace::~emptySpace(){}

resource::~resource(){}

barrier::~barrier(){}