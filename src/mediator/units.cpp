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

bool Base::isInit()
{
    return init;
}

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

bool action(std::string &payload, const Base &unit, long gold, const grid &map, const listUnits &allies, const listUnits &enemies)
{
    (void)map;

    std::ostringstream ss;

    if (unit.queue == '0')
    {
        // Both players can have exactly 1 unit simultaneously only in turn 1.
        bool firstTurn = (
            allies.unitCount == 1 && enemies.unitCount == 1 && \
            allies.bases[0].queue == '0' && enemies.bases[0].queue == '0'
        );

        // Pikemen are a cheap hard counter to knights.
        bool needPikemen = (allies.pikemen.size() < enemies.knights.size());

        // There should be at least 1 worker per each resource node.
        // But not more than swordsmen. Otherwise the base would only produce workers.
        bool needWorkers = (
            allies.workers.size() <= allies.swordsmen.size() && \
            allies.workers.size() < resource::getResourceCount()
        );

        // Knights are very good against archers and rams.
        // They are also marginally better against catapults than other units.
        bool needKnights = (
            allies.knights.size() < enemies.catapults.size() || \
            allies.knights.size() < enemies.rams.size() || \
            allies.knights.size() < enemies.archers.size()
        );

        // First turn. Build a knight.
        if (firstTurn)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold > 800 build catapults. Always.
        else if (!firstTurn && CAN_GET_CATAPULT(gold))
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If gold > 400 and there are reasons, build knights.
        else if (!firstTurn && CAN_GET_KNIGHT(gold) && needKnights)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold > 200 and there are reasons, build pikemen.
        else if (!firstTurn && CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If none of the above apply and you lack workers, built them now.
        else if (!firstTurn && CAN_GET_WORKER(gold) && needWorkers)
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen. Ignore rams and archers.
        else if (!firstTurn && CAN_GET_SWORDSMAN(gold))
        {
            ss << unit.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}