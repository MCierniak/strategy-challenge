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

#ifndef PLAYER_UNITS_H
#define PLAYER_UNITS_H

#include "grid.h"

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

// Vector for units
#define listW std::vector<Worker>
#define listC std::vector<Catapult>
#define listR std::vector<Ram>
#define listP std::vector<Pikeman>
#define listA std::vector<Archer>
#define listS std::vector<Swordsman>
#define listK std::vector<Knight>
#define listB std::vector<Base>

// Build cost logic
#define CAN_GET_WORKER(x) (x >= 100)
#define CAN_GET_CATAPULT(x) (x >= 800)
#define CAN_GET_RAM(x) (x >= 500)
#define CAN_GET_PIKEMAN(x) (x >= 200)
#define CAN_GET_ARCHER(x) (x >= 250)
#define CAN_GET_SWORDSMAN(x) (x >= 250)
#define CAN_GET_KNIGHT(x) (x >= 400)

// Damage
#define KNIGHT2KNIGHT 35
#define KNIGHT2SWORDSMAN 35
#define KNIGHT2ARCHER 35
#define KNIGHT2PIKEMAN 35
#define KNIGHT2CATAPULT 35
#define KNIGHT2RAM 50
#define KNIGHT2WORKER 35
#define KNIGHT2BASE 35

#define SWORDSMAN2KNIGHT 30
#define SWORDSMAN2SWORDSMAN 30
#define SWORDSMAN2ARCHER 30
#define SWORDSMAN2PIKEMAN 20
#define SWORDSMAN2CATAPULT 20
#define SWORDSMAN2RAM 30
#define SWORDSMAN2WORKER 30
#define SWORDSMAN2BASE 30

#define ARCHER2KNIGHT 15
#define ARCHER2SWORDSMAN 15
#define ARCHER2ARCHER 15
#define ARCHER2PIKEMAN 15
#define ARCHER2CATAPULT 10
#define ARCHER2RAM 10
#define ARCHER2WORKER 15
#define ARCHER2BASE 15

#define PIKEMAN2KNIGHT 35
#define PIKEMAN2SWORDSMAN 15
#define PIKEMAN2ARCHER 15
#define PIKEMAN2PIKEMAN 15
#define PIKEMAN2CATAPULT 15
#define PIKEMAN2RAM 10
#define PIKEMAN2WORKER 15
#define PIKEMAN2BASE 10

#define CATAPULT2KNIGHT 40
#define CATAPULT2SWORDSMAN 40
#define CATAPULT2ARCHER 40
#define CATAPULT2PIKEMAN 40
#define CATAPULT2CATAPULT 40
#define CATAPULT2RAM 40
#define CATAPULT2WORKER 40
#define CATAPULT2BASE 50

#define RAM2KNIGHT 10
#define RAM2SWORDSMAN 10
#define RAM2ARCHER 10
#define RAM2PIKEMAN 10
#define RAM2CATAPULT 10
#define RAM2RAM 10
#define RAM2WORKER 10
#define RAM2BASE 50

#define WORKER2KNIGHT 5
#define WORKER2SWORDSMAN 5
#define WORKER2ARCHER 5
#define WORKER2PIKEMAN 5
#define WORKER2CATAPULT 5
#define WORKER2RAM 5
#define WORKER2WORKER 5
#define WORKER2BASE 1

// Speed
#define SPEED_KNIGHT 5
#define SPEED_SWORDSMAN 2
#define SPEED_ARCHER 2
#define SPEED_PIKEMAN 2
#define SPEED_RAM 2
#define SPEED_CATAPULT 2
#define SPEED_WORKER 2

// Attack Range
#define ATTACK_KNIGHT 1
#define ATTACK_SWORDSMAN 1
#define ATTACK_ARCHER 5
#define ATTACK_PIKEMAN 2
#define ATTACK_RAM 1
#define ATTACK_CATAPULT 7
#define ATTACK_WORKER 1

// Abstract interface for units
class Unit
{
public:
    const int id, endurance;
    const std::size_t posx, posy;
    
    Unit(int ident, int end, std::size_t px, std::size_t py);
    virtual ~Unit() = 0;
};

class Base : public Unit
{
public:
    const char queue;
    const bool init;

    Base();
    Base(int ident, int end, std::size_t px, std::size_t py, char q);
    ~Base();

    bool isInit();
};

class Worker : public Unit
{
public:
    Worker(int ident, int end, std::size_t px, std::size_t py);
    ~Worker();
};

class Catapult : public Unit
{
public:
    Catapult(int ident, int end, std::size_t px, std::size_t py);
    ~Catapult();
};

class Ram : public Unit
{
public:
    Ram(int ident, int end, std::size_t px, std::size_t py);
    ~Ram();
};

class Pikeman : public Unit
{
public:
    Pikeman(int ident, int end, std::size_t px, std::size_t py);
    ~Pikeman();
};

class Archer : public Unit
{
public:
    Archer(int ident, int end, std::size_t px, std::size_t py);
    ~Archer();
};

class Swordsman : public Unit
{
public:
    Swordsman(int ident, int end, std::size_t px, std::size_t py);
    ~Swordsman();
};

class Knight : public Unit
{
public:
    Knight(int ident, int end, std::size_t px, std::size_t py);
    ~Knight();
};

struct listUnits
{
    listW workers;
    listC catapults;
    listR rams;
    listP pikemen;
    listA archers;
    listS swordsmen;
    listK knights;
    listB bases;
    int unitCount = 0;
    std::unordered_map<int, char> id2type;
    std::unordered_map<int, int> id2index;

    bool addUnit(Worker &unit);
    bool addUnit(Catapult &unit);
    bool addUnit(Ram &unit);
    bool addUnit(Pikeman &unit);
    bool addUnit(Archer &unit);
    bool addUnit(Swordsman &unit);
    bool addUnit(Knight &unit);
    bool addUnit(Base &unit);

    bool is_unique(int id);
};

//Decision making functions
bool action(std::string &payload, const Base &unit, long gold, const grid &map, const listUnits &allies, const listUnits &enemies);
bool action(std::string &payload, const Worker &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Catapult &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Ram &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Pikeman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Archer &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Swordsman &unit, const grid &map, const listUnits &enemies);
bool action(std::string &payload, const Knight &unit, const grid &map, const listUnits &enemies);

//Misc
std::size_t Dist(Unit *first, Unit *second);
std::size_t Dist(Unit *first, std::size_t xSecond, std::size_t ySecond);

#endif