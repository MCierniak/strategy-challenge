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

#ifndef MEDIATOR_UNITS_H
#define MEDIATOR_UNITS_H

// Analog to player's units/units.h
// listUnits has additional remove methods to process dead units

#include "grid.h"

#include <bits/stdc++.h>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#define hitListType std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>

// Build cost logic
#define CAN_GET_WORKER(x) (x >= 100)
#define CAN_GET_CATAPULT(x) (x >= 800)
#define CAN_GET_RAM(x) (x >= 500)
#define CAN_GET_PIKEMAN(x) (x >= 200)
#define CAN_GET_ARCHER(x) (x >= 250)
#define CAN_GET_SWORDSMAN(x) (x >= 250)
#define CAN_GET_KNIGHT(x) (x >= 400)

// Damage
#define WORKER2KNIGHT 5
#define WORKER2SWORDSMAN 5
#define WORKER2ARCHER 5
#define WORKER2PIKEMAN 5
#define WORKER2CATAPULT 5
#define WORKER2RAM 5
#define WORKER2WORKER 5
#define WORKER2BASE 1

#define KNIGHT2KNIGHT 35
#define KNIGHT2SWORDSMAN 35
#define KNIGHT2ARCHER 35
#define KNIGHT2PIKEMAN 35
#define KNIGHT2CATAPULT 35
#define KNIGHT2RAM 50
#define KNIGHT2WORKER 35
#define KNIGHT2BASE 35

#define ARCHER2KNIGHT 15
#define ARCHER2SWORDSMAN 15
#define ARCHER2ARCHER 15
#define ARCHER2PIKEMAN 15
#define ARCHER2CATAPULT 10
#define ARCHER2RAM 10
#define ARCHER2WORKER 15
#define ARCHER2BASE 15

#define CATAPULT2KNIGHT 40
#define CATAPULT2SWORDSMAN 40
#define CATAPULT2ARCHER 40
#define CATAPULT2PIKEMAN 40
#define CATAPULT2CATAPULT 40
#define CATAPULT2RAM 40
#define CATAPULT2WORKER 40
#define CATAPULT2BASE 50

#define PIKEMAN2KNIGHT 35
#define PIKEMAN2SWORDSMAN 15
#define PIKEMAN2ARCHER 15
#define PIKEMAN2PIKEMAN 15
#define PIKEMAN2CATAPULT 15
#define PIKEMAN2RAM 10
#define PIKEMAN2WORKER 15
#define PIKEMAN2BASE 10

#define RAM2KNIGHT 10
#define RAM2SWORDSMAN 10
#define RAM2ARCHER 10
#define RAM2PIKEMAN 10
#define RAM2CATAPULT 10
#define RAM2RAM 10
#define RAM2WORKER 10
#define RAM2BASE 50

#define SWORDSMAN2KNIGHT 30
#define SWORDSMAN2SWORDSMAN 30
#define SWORDSMAN2ARCHER 30
#define SWORDSMAN2PIKEMAN 20
#define SWORDSMAN2CATAPULT 20
#define SWORDSMAN2RAM 30
#define SWORDSMAN2WORKER 30
#define SWORDSMAN2BASE 30

// Speed
#define SPEED_KNIGHT 5
#define SPEED_WORKER 2
#define SPEED_ARCHER 2
#define SPEED_CATAPULT 2
#define SPEED_PIKEMAN 2
#define SPEED_RAM 2
#define SPEED_SWORDSMAN 2

// Attack Range
#define ATTACK_KNIGHT 1
#define ATTACK_WORKER 1
#define ATTACK_ARCHER 5
#define ATTACK_CATAPULT 7
#define ATTACK_PIKEMAN 2
#define ATTACK_RAM 1
#define ATTACK_SWORDSMAN 1

// Build time
#define BUILD_TIME(x) (x == 'K' ? 5 : x == 'C' ? 6 : x == 'R' ? 4 : x == 'W' ? 2 : 3)
// Build cost
#define BUILD_COST(x) (x == 'K' ? 400 : x == 'C' ? 800 : x == 'R' ? 500 : x == 'W' ? 100 : x == 'P' ? 200 : 250)

// Abstract interface for units
class Unit
{
public:
    // Unit id and hp
    int id, endurance;
    // Unit position
    int posx, posy;
    
    Unit(int ident, int end, int px, int py);
    virtual ~Unit() = 0;
};

class Base : public Unit
{
public:
    // Current construction
    char queue;
    // Remaining construction time
    int qTime = 0;

    // Default constructor needed for listUnits struct initialziation
    Base();
    Base(int ident, int end, int px, int py, char q);
    Base(int ident, int end, int px, int py, char q, int qT);
    ~Base();
};

class Worker : public Unit
{
public:
    // Contructor for new units
    Worker(int ident, int px, int py);
    // Contructor for existing units
    Worker(int ident, int end, int px, int py);
    ~Worker();
};

class Catapult : public Unit
{
public:
    // Contructor for new units
    Catapult(int ident, int px, int py);
    // Contructor for existing units
    Catapult(int ident, int end, int px, int py);
    ~Catapult();
};

class Ram : public Unit
{
public:
    // Contructor for new units
    Ram(int ident, int px, int py);
    // Contructor for existing units
    Ram(int ident, int end, int px, int py);
    ~Ram();
};

class Pikeman : public Unit
{
public:
    // Contructor for new units
    Pikeman(int ident, int px, int py);
    // Contructor for existing units
    Pikeman(int ident, int end, int px, int py);
    ~Pikeman();
};

class Archer : public Unit
{
public:
    // Contructor for new units
    Archer(int ident, int px, int py);
    // Contructor for existing units
    Archer(int ident, int end, int px, int py);
    ~Archer();
};

class Swordsman : public Unit
{
public:
    // Contructor for new units
    Swordsman(int ident, int px, int py);
    // Contructor for existing units
    Swordsman(int ident, int end, int px, int py);
    ~Swordsman();
};

class Knight : public Unit
{
public:
    // Contructor for new units
    Knight(int ident, int px, int py);
    // Contructor for existing units
    Knight(int ident, int end, int px, int py);
    ~Knight();
};

// List of player units
struct listUnits
{
    // Main list of units (excluding base)
    std::map<int, std::unique_ptr<Unit>> units;
    // Damage map for each unit (used to decrement enemy endurance after attack has been issued)
    std::map<int, std::map<char, int>> id2dmg;
    // Human-readable version of id2type
    std::map<int, std::string> id2typeName;
    // Translate id to attack range
    std::map<int, int> id2arange;
    // Translate id to unit type
    std::map<int, char> id2type;
    // Translate id to unit speed
    std::map<int, int> id2speed;

    // Leftover from player script. Not used here
    hitListType hitList;

    // Total number of each unit type
    int qWorker = 0, qCatapult = 0, qRam = 0, qPikeman = 0, qArcher = 0;
    int qSwordsman = 0, qKnight = 0, qAll = 0;

    // The base
    Base base;

    // Method to add a base. Id uniqness is ensured
    bool addBase(int ident, int end, int px, int py, char q);
    bool addBase(int ident, int end, int px, int py, char q, int qT);

    // Method to remove unit on death
    bool removeUnit(int id);

    // Method to add workers. Id uniqness is ensured
    bool addWorker(int ident, int px, int py);
    bool addWorker(int ident, int end, int px, int py);
    // Method to remove worker on death
    bool removeWorker(int id);

    // Method to add catapults. Id uniqness is ensured
    bool addCatapult(int ident, int px, int py);
    bool addCatapult(int ident, int end, int px, int py);
    // Method to remove catapult on death
    bool removeCatapult(int id);

    // Method to add ram. Id uniqness is ensured
    bool addRam(int ident, int px, int py);
    bool addRam(int ident, int end, int px, int py);
    // Method to remove ram on death
    bool removeRam(int id);

    // Method to add pikeman. Id uniqness is ensured
    bool addPikeman(int ident, int px, int py);
    bool addPikeman(int ident, int end, int px, int py);
    // Method to remove pikeman on death
    bool removePikeman(int id);

    // Method to add archer. Id uniqness is ensured
    bool addArcher(int ident, int px, int py);
    bool addArcher(int ident, int end, int px, int py);
    // Method to remove archer on death
    bool removeArcher(int id);

    // Method to add swordsman. Id uniqness is ensured
    bool addSwordsman(int ident, int px, int py);
    bool addSwordsman(int ident, int end, int px, int py);
    // Method to remove swordsman on death
    bool removeSwordsman(int id);

    // Method to add knight. Id uniqness is ensured
    bool addKnight(int ident, int px, int py);
    bool addKnight(int ident, int end, int px, int py);
    // Method to remove knight on death
    bool removeKnight(int id);

    // Id uniqness test 
    bool is_unique(int id);
};

// Distance between First and Second
int Dist(int xFirst, int yFirst, int xSecond, int ySecond);

#endif