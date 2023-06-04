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

#ifndef MEDIATOR_GRID_H
#define MEDIATOR_GRID_H

#include <string>

// Vector for map tiles. Call with grid[y coord][x coord]
#define grid_row std::vector<std::unique_ptr<gridObj>>
#define grid std::vector<grid_row>

// Abstract interface for grid tiles
class gridObj
{
protected:
    // Bool indicating if unit can stop on this tile
    bool isTraversable;
public:
    gridObj(bool traversible);
    virtual ~gridObj() = default;

    virtual std::string print() = 0;
    
    // Set traversal status
    virtual void setTrav(bool newTrav) = 0;

    // Check if unit can stop on this node
    bool checkTrav();
};

// Empty space tile
class emptySpace : public gridObj
{
public:
    emptySpace();
    ~emptySpace();

    void setTrav(bool newTrav);

    std::string print();
};

// Resource tile
class resource : public gridObj
{
protected:
    // Static count of resource tiles
    static std::size_t resourceCount;
public:
    resource();
    ~resource();

    std::string print();

    void setTrav(bool newTrav);

    // Get current resource node count
    static std::size_t getResourceCount();
};

// Barrier class
class barrier : public gridObj
{
public:
    barrier();
    ~barrier();

    void setTrav(bool newTrav);

    std::string print();
};

#endif