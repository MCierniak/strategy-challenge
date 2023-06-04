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

int resource::resourceCount = 0;

bool gridObj::checkTrav()
{
    return isTraversable;
}

void emptySpace::setTrav(bool newTrav)
{
    isTraversable = newTrav;
}

void resource::setTrav(bool newTrav)
{
    isTraversable = newTrav;
}

void barrier::setTrav(bool newTrav)
{
    (void)newTrav;
    isTraversable = false;
}

int resource::getResourceCount()
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
    resource::resourceCount++;
}

barrier::barrier():
    gridObj(false)
{}

gridObj::~gridObj(){}

emptySpace::~emptySpace(){}

resource::~resource()
{
    resource::resourceCount--;
}

barrier::~barrier(){}