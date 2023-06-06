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

bool Worker::find_target(const grid &map)
{
    // If already on resource node, stay there
    if (map[this->posy][this->posx]->checkResource())
    {
        this->trgtY = this->posy;
        this->trgtX = this->posx;
        return true;
    }
    // Find nearest empty resource node
    for (auto &&el : resource::resNodeList)
    {
        if (map[el[0]][el[1]]->checkTrav() && map[el[0]][el[1]]->getWorkerId().size() == 0)
        {
            this->trgtY = el[0];
            this->trgtX = el[1];
            return true;
        }
    }
    // If none, find nearest resource node without enemies
    for (auto &&el : resource::resNodeList)
    {
        if (map[el[0]][el[1]]->checkTrav())
        {
            this->trgtY = el[0];
            this->trgtX = el[1];
            return true;
        }
    }
    // If all taken by the enemy, return false
    return false;
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

    this->workers.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'W';
    
    return true;
}

bool listUnits::addUnit(Catapult &unit)
{
    int id = unit.id;

    this->catapults.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'C';

    return true;
}

bool listUnits::addUnit(Ram &unit)
{
    int id = unit.id;

    this->rams.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'R';

    return true;
}

bool listUnits::addUnit(Pikeman &unit)
{
    int id = unit.id;

    this->pikemen.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'P';

    return true;
}

bool listUnits::addUnit(Archer &unit)
{
    int id = unit.id;

    this->archers.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'A';

    return true;
}

bool listUnits::addUnit(Swordsman &unit)
{
    int id = unit.id;

    this->swordsmen.push_back(unit);
    this->unitCount++;

    if(!this->is_unique(id)) return false;

    this->id2type[id] = 'S';

    return true;
}

bool listUnits::addUnit(Knight &unit)
{
    int id = unit.id;

    this->knights.push_back(unit);
    this->unitCount++;

    if(!is_unique(id)) return false;

    this->id2type[id] = 'K';

    return true;
}

bool listUnits::addUnit(Base &unit)
{
    int id = unit.id;

    this->bases.push_back(unit);
    this->unitCount++;

    if(!is_unique(id)) return false;

    this->id2type[id] = 'B';

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

Unit::~Unit(){}

Base::~Base(){}

Worker::~Worker(){}

Catapult::~Catapult(){}

Ram::~Ram(){}

Pikeman::~Pikeman(){}

Archer::~Archer(){}

Swordsman::~Swordsman(){}

Knight::~Knight(){}

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
            allies.workers.size() < resource::getUnusedResourceCount()
        );

        // Knights are very good against archers and rams.
        // They are also marginally better against catapults than other units.
        bool needKnights = (
            allies.knights.size() < enemies.catapults.size() || \
            allies.knights.size() < enemies.rams.size() || \
            allies.knights.size() < enemies.archers.size()
        );

        // If the enemy has no units, build rams.
        bool needRams = (enemies.unitCount == 1);

        // If the enemy has many workers, build archers.
        bool needArchers = (allies.archers.size() < enemies.workers.size());

        // First turn. Build an archer.
        if (firstTurn && CAN_GET_ARCHER(gold))
        {
            ss << unit.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Once the archer is ready, build a worker
        else if (secondQueue && CAN_GET_WORKER(gold))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        //If you have no workers, build them immediately!
        else if (noWorkers && CAN_GET_WORKER(gold))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (CAN_GET_CATAPULT(gold))
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If 800 > gold >= 500 and enemy has no units left, build rams.
        else if (!CAN_GET_CATAPULT(gold) && CAN_GET_RAM(gold) && needRams)
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and enemy has many catapults/rams/archers,
        // build knights.
        else if (CAN_GET_KNIGHT(gold) && needKnights)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and enemy has many knights, build pikemen
        else if (CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If you have few workers (but not 0), built them now.
        else if (CAN_GET_WORKER(gold) && needWorkers)
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If enemy has many workers, build archers.
        else if (CAN_GET_ARCHER(gold) && needArchers)
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen.
        else if (CAN_GET_SWORDSMAN(gold))
        {
            ss << unit.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

bool action(std::string &payload, Worker &unit, const grid &map)
{

    if(unit.find_target(map))
    {
        // Worker already on resource node, take no action
        if (unit.trgtX == unit.posx && unit.trgtY == unit.posy) return false;
        // Resource node in range, move to it
        else if (Dist(&unit, unit.trgtX, unit.trgtY) <= 2)
        {
            std::ostringstream ss;
            ss << unit.id << " M " << unit.trgtX << ' ' << unit.trgtY << '\n';
            payload = ss.str();
            return true;
        }
        // Resource node far away, determine shortest path and move
        // Use Dijkstra's algorithm
        else
        {
            int stepX, stepY;
            if(!dijkstra_find_path_worker(map, unit.posx, unit.posy, unit.trgtX, unit.trgtY, stepX, stepY, MOVE_2)) return false;
            std::ostringstream ss;
            ss << unit.id << " M " << stepX << ' ' << stepY << '\n';
            payload = ss.str();
            return true;
        }
    }
    else
    {
        // All resource nodes under enemy control, evade damage and wait
        std::list<std::size_t> move_x, move_y;

        move_x.push_front(unit.posx);
        move_y.push_front(unit.posy);
        int dmg = map[unit.posy][unit.posx]->checkDmgWorker();
        bool makeMove = false;

        // Not in range of enemies, do nothing
        if (dmg == 1) return false;

        for (auto &&mod : MOVE_1)
        {
            if (int(unit.posy) + mod[0] < 0 || int(unit.posy) + mod[0] >= int(map.size())) continue;
            if (int(unit.posx) + mod[1] < 0 || int(unit.posx) + mod[1] >= int(map[unit.posy + mod[0]].size())) continue;
            int moddmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
            // If target node out of range of any enemy, no point to iterate, just move to it
            if (moddmg == 1)
            {
                std::ostringstream ss;
                ss << unit.id << " M " << unit.posx + mod[1] << ' ' << unit.posy + mod[0] << '\n';
                payload = ss.str();
                return true;
            }
            else
            {
                if (dmg > map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker())
                {
                    dmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
                    move_x.push_front(unit.posy + mod[0]);
                    move_y.push_front(unit.posx + mod[1]);
                    makeMove = true;
                }
            }
        }
        for (auto &&mod : MOVE_2)
        {
            if (int(unit.posy) + mod[0] < 0 || int(unit.posy) + mod[0] >= int(map.size())) continue;
            if (int(unit.posx) + mod[1] < 0 || int(unit.posx) + mod[1] >= int(map[unit.posy + mod[0]].size())) continue;
            int moddmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
            // If target node out of range of any enemy, no point to iterate, just move to it
            if (moddmg == 1)
            {
                std::ostringstream ss;
                ss << unit.id << " M " << unit.posx + mod[1] << ' ' << unit.posy + mod[0] << '\n';
                payload = ss.str();
                return true;
            }
            else
            {
                if (dmg > moddmg)
                {
                    dmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
                    move_x.push_front(unit.posy + mod[0]);
                    move_y.push_front(unit.posx + mod[1]);
                    makeMove = true;
                }
            }
        }
        if (makeMove)
        {
            std::ostringstream ss;
            ss << unit.id << " M " << move_x.front() << ' ' << move_y.front() << '\n';
            payload = ss.str();
            return true;
        }
        else return false;
    }
}