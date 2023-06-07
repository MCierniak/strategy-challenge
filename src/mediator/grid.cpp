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
    return this->isTraversable;
}

bool gridObj::checkResource()
{
    return this->isResource;
}

void emptySpace::setTrav(bool newTrav)
{
    this->isTraversable = newTrav;
}

void resource::setTrav(bool newTrav)
{
    this->isTraversable = newTrav;
}

void barrier::setTrav(bool newTrav)
{
    (void)newTrav;
    this->isTraversable = false;
}

std::size_t resource::getResourceCount()
{
    return resource::resourceCount;
}

std::string emptySpace::print()
{
    return std::string("e");
}

std::string resource::print()
{
    return std::string("r");
}

std::string barrier::print()
{
    return std::string("b");
}

gridObj::gridObj(bool traversible, bool resource):
    isTraversable(traversible), isResource(resource)
{}

emptySpace::emptySpace():
    gridObj(true, false)
{}

resource::resource():
    gridObj(true, true)
{
    resource::resourceCount++;
}

barrier::barrier():
    gridObj(false, false)
{}

emptySpace::~emptySpace(){}

resource::~resource()
{
    resource::resourceCount--;
}

barrier::~barrier(){}