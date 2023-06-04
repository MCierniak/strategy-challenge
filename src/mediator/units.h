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

// Build time
#define BUILD_TIME(x) (x == 'K' ? 5 : x == 'C' ? 6 : x == 'R' ? 4 : x == 'W' ? 2 : 3)

// Abstract interface for units
class Unit
{
public:
    const int id, endurance, speed, attackRange;
    const int posx, posy;
    
    Unit(int ident, int end, int sp, int aR, int px, int py);
    virtual ~Unit() = 0;

    //to zrobić...
    // virtual std::string state4Player() = 0;
    // virtual std::string state4Mediator() = 0;
};

class Base : public Unit
{
public:
    const bool init;
    char queue;
    int qTime = 0;

    Base();
    Base(int ident, int end, int px, int py, char q);
    ~Base();

    bool isInit();
};

class Worker : public Unit
{
public:
    Worker(int ident, int end, int px, int py);
    ~Worker();
};

class Catapult : public Unit
{
public:
    Catapult(int ident, int end, int px, int py);
    ~Catapult();
};

class Ram : public Unit
{
public:
    Ram(int ident, int end, int px, int py);
    ~Ram();
};

class Pikeman : public Unit
{
public:
    Pikeman(int ident, int end, int px, int py);
    ~Pikeman();
};

class Archer : public Unit
{
public:
    Archer(int ident, int end, int px, int py);
    ~Archer();
};

class Swordsman : public Unit
{
public:
    Swordsman(int ident, int end, int px, int py);
    ~Swordsman();
};

class Knight : public Unit
{
public:
    Knight(int ident, int end, int px, int py);
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

#endif