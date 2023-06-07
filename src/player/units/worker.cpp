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

#include "worker.h"

Worker::Worker(int ident, int end, std::size_t px, std::size_t py):
    Unit(ident, end, px, py)
{}

bool Worker::find_target(const grid &map)
{
    // If already on empty resource node, stay there
    // The third condition ensures that at least one worker will stay
    // on the node regardless
    if (
        map[this->posy][this->posx]->checkResource() && 
        (
            map[this->posy][this->posx]->getWorkerId().size() == 1 || 
            map[this->posy][this->posx]->getWorkerId()[0] == this->id
        )
    )
    {
        this->trgtY = this->posy;
        this->trgtX = this->posx;
        return true;
    }
    // If not, find nearest empty resource node
    for (auto &&el : resource::resNodeList)
    {
        if (map[el[0]][el[1]]->checkTrav() && map[el[0]][el[1]]->getWorkerId().size() == 0)
        {
            this->trgtY = el[0];
            this->trgtX = el[1];
            return true;
        }
    }
    // If none and unit already on resource node, stay there
    if (map[this->posy][this->posx]->checkResource())
    {
        this->trgtY = this->posy;
        this->trgtX = this->posx;
        return true;
    }
    // If not, find nearest resource node without enemies
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

Worker::~Worker(){}