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

#ifndef GRID_H
#define GRID_H

#include "units.h"

#include <memory>
#include <vector>
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
    ~gridObj();

    virtual std::string print() = 0;
    
    // Check if unit can stop on this node
    bool checkTrav();
};

// Empty space tile and also resource tile class
class emptySpace : public gridObj
{
protected:
    // Logic flags for decision making
    bool attackAdvantage, resource;
    // Vector of units on the tile
    unitRoster units;
    // Tile value for decision making
    int value;

    // Static count of resource tiles
    static int resourceCount;
public:
    emptySpace();
    ~emptySpace();

    std::string print();

    // Check tile value
    int checkVal();

    // Add unit to tile
    void addUnit(std::unique_ptr<Unit> &newUnitPtr);
    // Remove unit from tile roster. O(1)
    void removeUnit(std::size_t pos);
    // Change tile status from empty to resource
    void setResource(bool newRes);
    // Set traversal status
    void setTrav(bool newTrav);
    // Set attack advantage status
    void setAttack(bool newAtt);
    // Set tile value
    void setVal(int newVal);

    // Get current resource node count
    static int getResourceCount();
};

// Blockade class
class barrier : public gridObj
{
public:
    barrier();
    ~barrier();

    std::string print();
};

#endif