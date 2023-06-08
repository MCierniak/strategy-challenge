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

Unit::Unit(int ident, int end, int px, int py):
    id(ident), endurance(end), posx(px), posy(py)
{}

Base::Base():
    Unit(0, 0, 0, 0), queue('0'), init(false)
{}

Base::Base(int ident, int end, int px, int py, char q):
    Unit(ident, end, px, py), queue(q), init(true)
{}

Worker::Worker(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Swordsman::Swordsman(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Archer::Archer(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Pikeman::Pikeman(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Knight::Knight(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Ram::Ram(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Catapult::Catapult(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Unit::~Unit(){}

Base::~Base(){}

Worker::~Worker(){}

Swordsman::~Swordsman(){}

Archer::~Archer(){}

Pikeman::~Pikeman(){}

Knight::~Knight(){}

Ram::~Ram(){}

Catapult::~Catapult(){}

bool Base::isInit()
{
    return this->init;
}
