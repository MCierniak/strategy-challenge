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

std::string emptySpace::print()
{
    return std::string("e");
}

int resource::getResourceCount()
{
    return resource::resourceCount;
}

void resource::setTrav(bool newTrav)
{
    isTraversable = newTrav;
}

std::string resource::print()
{
    return std::string("r");
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
    gridObj(true)
{}

emptySpace::~emptySpace(){}

resource::resource():
    gridObj(true)
{
    resource::resourceCount++;
}

resource::~resource()
{
    resource::resourceCount--;
}

barrier::barrier():
    gridObj(false)
{}

barrier::~barrier(){}