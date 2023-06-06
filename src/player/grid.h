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
    int dmg2Knight = 1, dmg2Swordsman = 1, dmg2Archer = 1, dmg2Pikeman = 1;
    int dmg2Catapult = 1, dmg2Ram = 1, dmg2Worker = 1;
public:
    const std::size_t posx, posy;

    gridObj(bool traversible, bool resource, std::size_t px, std::size_t py);
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
    void addWorkerId(int id);

    // Check if unit can stop on this node
    bool checkTrav();
    bool checkResource();

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

    std::vector<int>& getWorkerId();
    int getWorkerId(std::size_t i);
};

// Empty space tile
class emptySpace : public gridObj
{
public:
    emptySpace(std::size_t px, std::size_t py);
    ~emptySpace();

    std::string print();
};

// Resource tile
class resource : public gridObj
{
protected:
    // Count unused resource nodes. Adding a worker or
    // enemy to this node decreases this value
    static std::size_t unusedResourceCount;
public:
    static std::list<std::vector<std::size_t>> resNodeList;
    
    resource(std::size_t px, std::size_t py);
    ~resource();

    std::string print();

    static std::size_t getUnusedResourceCount();

    void addEnemyId(int id);
    void addWorkerId(int id);

    std::vector<int>& getWorkerId();
    int getWorkerId(std::size_t i);
};

// Barrier class
class barrier : public gridObj
{
public:
    barrier(std::size_t px, std::size_t py);
    ~barrier();

    std::string print();
};

// Bredth-first search algorithm for map traversal. Returns false if there is no traversable path between s and t.
bool bfs_find_path(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);

// Dijkstra's search algorithm for map traversal. Returns false if there is no traversable path between s and t.
// Slower than BFS.
bool dijkstra_find_path_knight(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_swordsman(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_archer(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_pikeman(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_ram(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_catapult(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);
bool dijkstra_find_path_worker(const grid &map, int sX, int sY, int tX, int tY, int &resX, int &resY, const std::vector<std::vector<int>> &speed);

#endif