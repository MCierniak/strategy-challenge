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

std::size_t resource::resourceCount = 0;

bool gridObj::checkTrav()
{
    return isTraversable;
}

void gridObj::addDmg2Knight(int dmg)
{
    dmg2Knight += dmg;
}

void gridObj::addDmg2Swordsman(int dmg)
{
    dmg2Swordsman += dmg;
}

void gridObj::addDmg2Archer(int dmg)
{
    dmg2Archer += dmg;
}

void gridObj::addDmg2Pikeman(int dmg)
{
    dmg2Pikeman += dmg;
}

void gridObj::addDmg2Catapult(int dmg)
{
    dmg2Catapult += dmg;
}

void gridObj::addDmg2Ram(int dmg)
{
    dmg2Ram += dmg;
}

void gridObj::addDmg2Worker(int dmg)
{
    dmg2Worker += dmg;
}

void gridObj::addEnemyId(int id)
{
    enemyIds.push_back(id);
    isTraversable = false;
}

std::size_t gridObj::checkEnemyNr()
{
    return enemyIds.size();
}

int gridObj::checkDmgKnight()
{
    return dmg2Knight;
}

int gridObj::checkDmgSwordsman()
{
    return dmg2Swordsman;
}

int gridObj::checkDmgArcher()
{
    return dmg2Archer;
}

int gridObj::checkDmgPikeman()
{
    return dmg2Pikeman;
}

int gridObj::checkDmgCatapult()
{
    return dmg2Catapult;
}

int gridObj::checkDmgRam()
{
    return dmg2Ram;
}

int gridObj::checkDmgWorker()
{
    return dmg2Worker;
}

std::vector<int>& gridObj::getEnemyId()
{
    return enemyIds;
}

int gridObj::getEnemyId(std::size_t i)
{
    return enemyIds[i];
}

std::size_t resource::getResourceCount()
{
    return resource::resourceCount;
}

std::string emptySpace::print()
{
    if (isTraversable) return std::string("e");
    else return std::string("e(x)");
}

std::string resource::print()
{
    if (isTraversable) return std::string("r");
    else return std::string("r(x)");
}

std::string barrier::print()
{
    return std::string("b(x)");
}

gridObj::gridObj(bool traversible):
    isTraversable(traversible)
{}

emptySpace::emptySpace():
    gridObj(true)
{}

resource::resource():
    gridObj(true)
{
    resource::resourceCount += 1;
}

barrier::barrier():
    gridObj(false)
{}

emptySpace::~emptySpace(){}

resource::~resource()
{
    resource::resourceCount -= 1;
}

barrier::~barrier(){}