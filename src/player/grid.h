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

// Classes for map array

#include "defaults.h"

#include "utils.h"

#include <bits/stdc++.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <list>

// Vector for map tiles. Call with grid[y coord][x coord]
#define grid_row std::vector<std::unique_ptr<gridObj>>
#define grid std::vector<grid_row>

// Abstract interface for grid tiles
class gridObj
{
protected:
    // Ids of enemies on the tile
    std::vector<int> enemyIds;
    // Ids of own workers on the tile 
    std::vector<int> workerIds;
    // Bool indicating if unit can stop on this tile
    bool isTraversable, isResource;
    // Indicators for potential damage inflicted if
    // ending turn on this node
    std::map<char, int> dmg;
public:
    gridObj(bool traversible, bool resource);
    virtual ~gridObj() = default;

    virtual std::string print() = 0;

    // Add dmg to dmg map
    void addDmg(char key, int val);

    // Add enemy/worker ids
    virtual void addEnemyId(int id);
    virtual void addWorkerId(int id);
    // Remove worker id (used when worker moves)
    void removeWorkerId(int id);

    // Check if unit can stop on this node
    bool checkTrav();
    // Check if node contains resources
    bool checkResource();

    // Check number of enemies on node
    int checkEnemyNr();

    // Check potential damage
    int checkDmg(char key);

    // Get ids of enemies standing on the node
    std::vector<int>& getEnemyId();
    int getEnemyId(int i);

    // Get ids of workers standing on the node
    std::vector<int>& getWorkerId();
    int getWorkerId(int i);
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
    // Count unused resource nodes. Adding a worker or
    // enemy to this node decreases this value
    static int unusedResourceCount;
    int posx, posy;
public:
    // List of resource node coordinates.
    // Used to direct workers where to go
    static std::list<std::vector<int>> resNodeList;
    
    resource(int px, int py);
    ~resource();

    std::string print();

    // Safely access unusedResourceCount
    static int getUnusedResourceCount();

    void addEnemyId(int id);
    void addWorkerId(int id);

    void removeWorkerId(int id);
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