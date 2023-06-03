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

int emptySpace::resourceCount = 0;

bool gridObj::checkTrav()
{
    return isTraversable;
}

int emptySpace::checkVal()
{
    return value;
}

void emptySpace::addUnit(std::unique_ptr<Unit> &newUnitPtr)
{
    units.push_back(std::move(newUnitPtr));
}

void emptySpace::setTrav(bool newTrav)
{
    isTraversable = newTrav;
}

void emptySpace::setAttack(bool newAtt)
{
    attackAdvantage = newAtt;
}

void emptySpace::removeUnit(std::size_t pos)
{
    if (pos < units.size())
    {
        if (pos != units.size() - 1)
        {
            units[pos] = std::move(units.back());
        }
        units.pop_back();
    }
}

void emptySpace::setResource(bool newRes)
{
    resource = newRes;
}

void emptySpace::setVal(int newVal)
{
    value = newVal;
}

int emptySpace::getResourceCount()
{
    return emptySpace::resourceCount;
}

std::string emptySpace::print()
{
    if (resource)
    {
        if (units.size() == 0)
        {
            return std::string("r");
        }
        else
        {
            return std::string("r(units)");
        }
    }
    else
    {
        if (units.size() == 0)
        {
            return std::string("e");
        }
        else
        {
            return std::string("e(units)");
        }
    }
}

std::string barrier::print()
{
    return std::string("b");
}

gridObj::gridObj(bool traversible):
    isTraversable(traversible)
{}

gridObj::~gridObj(){}

emptySpace::emptySpace():
    gridObj(true), attackAdvantage(false), resource(false), value(1)
{
    if (resource)
    {
        emptySpace::resourceCount++;
    }
}

emptySpace::~emptySpace()
{
    if (resource)
    {
        emptySpace::resourceCount--;
    }
}

barrier::barrier():
    gridObj(false)
{}

barrier::~barrier(){}