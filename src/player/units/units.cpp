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

bool Base::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    (void)map;
    (void)allies;
    (void)enemies;
    return false;
}

bool Worker::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    (void)allies;
    (void)enemies;
    // If already on empty resource node, stay there
    // The third condition ensures that at most one worker will stay
    if (this->posy < 0 || this->posy >= int(map.size())) return false;
    if (this->posx < 0 || this->posx >= int(map[0].size())) return false;
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Worker) Looking for resource..." << std::endl;
    #endif
    if (
        map[this->posy][this->posx]->checkResource() && 
        (
            map[this->posy][this->posx]->getWorkerId().size() == 1 || 
            map[this->posy][this->posx]->getWorkerId()[0] == this->id
        )
    )
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Worker) Already on resource node. Staying in place." << std::endl;
        #endif
        this->trgtY = this->posy;
        this->trgtX = this->posx;
        return true;
    }
    // If not, find nearest empty resource node
    for (auto &&el : resource::resNodeList)
    {
        if (el[0] < 0 || el[0] >= int(map.size())) return false;
        if (el[1] < 0 || el[1] >= int(map[0].size())) return false;
        if (map[el[0]][el[1]]->checkTrav() && map[el[0]][el[1]]->getWorkerId().size() == 0)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Worker) Found empty resource node. Moving." << std::endl;
            #endif
            this->trgtY = el[0];
            this->trgtX = el[1];
            return true;
        }
    }
    // If none and unit already on resource node, stay there
    if (map[this->posy][this->posx]->checkResource())
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Worker) No empty resource nodes. Staying in place." << std::endl;
        #endif
        this->trgtY = this->posy;
        this->trgtX = this->posx;
        return true;
    }
    // If not, find nearest resource node without enemies
    for (auto &&el : resource::resNodeList)
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Worker) No empty resource nodes. Moving." << std::endl;
        #endif
        if (el[0] < 0 || el[0] >= int(map.size())) return false;
        if (el[1] < 0 || el[1] >= int(map[0].size())) return false;
        if (map[el[0]][el[1]]->checkTrav())
        {
            this->trgtY = el[0];
            this->trgtX = el[1];
            return true;
        }
    }
    // If all taken by the enemy, return false
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Worker) All resource nodes in enemy hands." << std::endl;
    #endif
    return false;
}

bool Swordsman::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_swordsman(this->id, map, allies, enemies);
}

bool Archer::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_archer(this->id, map, allies, enemies);
}

bool Pikeman::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_pikeman(this->id, map, allies, enemies);
}

bool Knight::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_knight(this->id, map, allies, enemies);
}

bool Ram::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_ram(this->id, map, allies, enemies);
}

bool Catapult::find_target(const grid &map, listUnits &allies, listUnits &enemies)
{
    return find_target_catapult(this->id, map, allies, enemies);
}