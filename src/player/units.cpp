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

Base::Base(int ident, int end, int px, int py, char q):
    Unit(ident, end, 0, 0, px, py), queue(q)
{}

Worker::Worker(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Catapult::Catapult(int ident, int end, int px, int py):
    Unit(ident, end, 2, 7, px, py)
{}

Ram::Ram(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Pikeman::Pikeman(int ident, int end, int px, int py):
    Unit(ident, end, 2, 2, px, py)
{}

Archer::Archer(int ident, int end, int px, int py):
    Unit(ident, end, 2, 5, px, py)
{}

Swordsman::Swordsman(int ident, int end, int px, int py):
    Unit(ident, end, 2, 1, px, py)
{}

Knight::Knight(int ident, int end, int px, int py):
    Unit(ident, end, 5, 1, px, py)
{
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