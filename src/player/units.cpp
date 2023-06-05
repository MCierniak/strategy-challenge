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

Unit::Unit(int ident, int end, std::size_t px, std::size_t py):
    id(ident), endurance(end), posx(px), posy(py)
{}

Base::Base():
    Unit(0, 0, 0, 0), queue('0'), init(false)
{}

Base::Base(int ident, int end, std::size_t px, std::size_t py, char q):
    Unit(ident, end, px, py), queue(q), init(true)
{}

bool Base::isInit()
{
    return init;
}

Worker::Worker(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Catapult::Catapult(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Ram::Ram(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Pikeman::Pikeman(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Archer::Archer(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Swordsman::Swordsman(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

Knight::Knight(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
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

bool action(std::string &payload, const Base &unit, long gold, const grid &map, const listUnits &allies, const listUnits &enemies)
{
    (void)map;

    std::ostringstream ss;

    if (unit.queue == '0')
    {
        // Only in turn 1 can both players have exactly 1 unit simultaneously.
        bool firstTurn = (allies.unitCount == 1 && enemies.unitCount == 1);

        // Second queue, once the first turn choice is completed.
        bool secondQueue = (allies.unitCount == 2 && allies.workers.size() == 1);

        // Pikemen are a cheap hard counter to knights.
        bool needPikemen = (allies.pikemen.size() < enemies.knights.size());

        // There should be at least 1 worker per each resource node.
        // But not more than swordsmen. Otherwise the base would only produce workers.
        // Additionally, there should never be no workers.
        bool noWorkers = (allies.workers.size() == 0);
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

        // First turn. Build a worker.
        if (firstTurn && CAN_GET_WORKER(gold))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // Once the worker is ready, build a swordsman
        else if (!firstTurn && secondQueue && CAN_GET_SWORDSMAN(gold))
        {
            ss << unit.id << " B S\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (!firstTurn && !secondQueue && !noWorkers && CAN_GET_CATAPULT(gold))
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and there are reasons, build knights.
        else if (!firstTurn && !secondQueue && !noWorkers && CAN_GET_KNIGHT(gold) && needKnights)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and there are reasons, build pikemen.
        else if (!firstTurn && !secondQueue && !noWorkers && CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If none of the above apply and you lack workers, built them now.
        else if (!firstTurn && !secondQueue && CAN_GET_WORKER(gold) && (needWorkers || noWorkers))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen. Ignore rams and archers.
        else if (!firstTurn && !secondQueue && !noWorkers && CAN_GET_SWORDSMAN(gold))
        {
            ss << unit.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

std::size_t Dist(Unit *first, Unit *second)
{
    return std::abs(int(first->posx) - int(second->posx)) + std::abs(int(first->posy) - int(second->posy));
}

std::size_t Dist(Unit *first, std::size_t xSecond, std::size_t ySecond)
{
    return std::abs(int(first->posx) - int(xSecond)) + std::abs(int(first->posy) - int(ySecond));
}