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

#include "units.h"

Unit::Unit(int ident, int end, int sp, int aR, int px, int py):
    id(ident), endurance(end), speed(sp), attackRange(aR), posx(px), posy(py)
{}

Base::Base():
    Unit(0, 0, 0, 0, 0, 0), init(false), queue('0')
{}

Base::Base(int ident, int end, int px, int py, char q):
    Unit(ident, end, 0, 0, px, py), init(true), queue(q)
{}

Base::Base(int ident, int end, int px, int py, char q, int qT):
    Unit(ident, end, 0, 0, px, py), init(true), queue(q), qTime(qT)
{}

bool Base::isInit()
{
    return init;
}

Worker::Worker(int ident, int px, int py):
    Unit(ident, 20, 2, 1, px, py)
{}

Worker::Worker(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Catapult::Catapult(int ident, int px, int py):
    Unit(ident, 50, 2, 7, px, py)
{}

Catapult::Catapult(int ident, int end, int px, int py):
    Unit(ident, end, 2, 7, px, py)
{}

Ram::Ram(int ident, int px, int py):
    Unit(ident, 90, 2, 1, px, py)
{}

Ram::Ram(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Pikeman::Pikeman(int ident, int px, int py):
    Unit(ident, 50, 2, 2, px, py)
{}

Pikeman::Pikeman(int ident, int end, int px, int py):
    Unit(ident, end, 2, 2, px, py)
{}

Archer::Archer(int ident, int px, int py):
    Unit(ident, 40, 2, 5, px, py)
{}

Archer::Archer(int ident, int end, int px, int py):
    Unit(ident, end, 2, 5, px, py)
{}

Swordsman::Swordsman(int ident, int px, int py):
    Unit(ident, 60, 2, 1, px, py)
{}

Swordsman::Swordsman(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Knight::Knight(int ident, int px, int py):
    Unit(ident, 70, 5, 1, px, py)
{}

Knight::Knight(int ident, int end, int px, int py):
    Unit(ident, end, 5, 1, px, py)
{}

bool listUnits::addUnit(Worker &unit)
{
    int id = unit.id;

    workers.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'W';
    id2index[id] = workers.size() - 1;
    
    return true;
}

bool listUnits::addUnit(Catapult &unit)
{
    int id = unit.id;

    catapults.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'C';
    id2index[id] = catapults.size() - 1;

    return true;
}

bool listUnits::addUnit(Ram &unit)
{
    int id = unit.id;

    rams.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'R';
    id2index[id] = rams.size() - 1;

    return true;
}

bool listUnits::addUnit(Pikeman &unit)
{
    int id = unit.id;

    pikemen.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'P';
    id2index[id] = pikemen.size() - 1;

    return true;
}

bool listUnits::addUnit(Archer &unit)
{
    int id = unit.id;

    archers.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'A';
    id2index[id] = archers.size() - 1;

    return true;
}

bool listUnits::addUnit(Swordsman &unit)
{
    int id = unit.id;

    swordsmen.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'S';
    id2index[id] = swordsmen.size() - 1;

    return true;
}

bool listUnits::addUnit(Knight &unit)
{
    int id = unit.id;

    knights.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'K';
    id2index[id] = knights.size() - 1;

    return true;
}

bool listUnits::addUnit(Base &unit)
{
    int id = unit.id;

    bases.push_back(unit);
    unitCount++;

    if(!is_unique(id)) return false;

    id2type[id] = 'B';
    id2index[id] = bases.size() - 1;

    return true;
}

bool listUnits::is_unique(int id)
{
    if(!(id2type.find(id) == id2type.end()))
    {
        std::cerr << "Error! Unit ids are not unique!" << std::endl;
        return false;
    }
    return true;
}

Unit::~Unit(){}

Base::~Base(){}

Worker::~Worker(){}

Catapult::~Catapult(){}

Ram::~Ram(){}

Pikeman::~Pikeman(){}

Archer::~Archer(){}

Swordsman::~Swordsman(){}

Knight::~Knight(){}