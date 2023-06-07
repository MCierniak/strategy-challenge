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

#include "misc.h"

bool listUnits::addUnit(Worker &unit)
{
    int id = unit.id;

    this->workers.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'W';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;
    
    return true;
}

bool listUnits::addUnit(Catapult &unit)
{
    int id = unit.id;

    this->catapults.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'C';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Ram &unit)
{
    int id = unit.id;

    this->rams.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'R';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Pikeman &unit)
{
    int id = unit.id;

    this->pikemen.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'P';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Archer &unit)
{
    int id = unit.id;

    this->archers.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'A';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Swordsman &unit)
{
    int id = unit.id;

    this->swordsmen.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'S';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Knight &unit)
{
    int id = unit.id;

    this->knights.push_back(unit);
    this->unitCount++;

    if(!is_unique(id)) return false;

    this->id2type[id] = 'K';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::addUnit(Base &unit)
{
    int id = unit.id;

    this->bases.push_back(unit);
    this->unitCount++;

    if(!is_unique(id)) return false;

    this->id2type[id] = 'B';
    this->id2hp[id] = unit.endurance;
    this->id2ind[id] = this->workers.size() - 1;

    return true;
}

bool listUnits::is_unique(int id)
{
    if(!(this->id2type.find(id) == this->id2type.end()))
    {
        std::cerr << "Error! Unit ids are not unique!" << std::endl;
        return false;
    }
    return true;
}

int Dist(Unit *first, Unit *second)
{
    return std::abs(int(first->posx) - int(second->posx)) + std::abs(int(first->posy) - int(second->posy));
}

int Dist(Unit *first, int xSecond, int ySecond)
{
    return std::abs(int(first->posx) - int(xSecond)) + std::abs(int(first->posy) - int(ySecond));
}

int Dist(int xFirst, int yFirst, int xSecond, int ySecond)
{
    return std::abs(int(xFirst) - int(xSecond)) + std::abs(int(yFirst) - int(ySecond));
}