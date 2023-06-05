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

#ifndef PLAYER_GRID_H
#define PLAYER_GRID_H

#include <string>
#include <vector>

// Vector for map tiles. Call with grid[y coord][x coord]
#define grid_row std::vector<std::unique_ptr<gridObj>>
#define grid std::vector<grid_row>

// Abstract interface for grid tiles
class gridObj
{
protected:
    // Ids of enemies on the tile
    std::vector<int> enemyIds;
    // Bool indicating if unit can stop on this tile
    bool isTraversable;
    // Indicators for potential damage inflicted if
    // ending turn on this node
    int dmg2Knight = 0, dmg2Swordsman = 0, dmg2Archer = 0, dmg2Pikeman = 0;
    int dmg2Catapult = 0, dmg2Ram = 0, dmg2Worker = 0;
public:
    
    gridObj(bool traversible);
    virtual ~gridObj() = default;

    virtual std::string print() = 0;

    void addDmg2Knight(int dmg);
    void addDmg2Swordsman(int dmg);
    void addDmg2Archer(int dmg);
    void addDmg2Pikeman(int dmg);
    void addDmg2Catapult(int dmg);
    void addDmg2Ram(int dmg);
    void addDmg2Worker(int dmg);

    void addEnemyId(int id);

    // Check if unit can stop on this node
    bool checkTrav();

    std::size_t checkEnemyNr();

    int checkDmgKnight();
    int checkDmgSwordsman();
    int checkDmgArcher();
    int checkDmgPikeman();
    int checkDmgCatapult();
    int checkDmgRam();
    int checkDmgWorker();

    std::vector<int>& getEnemyId();
    int getEnemyId(std::size_t i);
};

// Empty space tile
class emptySpace : public gridObj
{
public:
    emptySpace();
    ~emptySpace();

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

    // Get current resource node count
    static std::size_t getResourceCount();
};

// Barrier class
class barrier : public gridObj
{
public:
    barrier();
    ~barrier();

    std::string print();
};

#endif