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

#ifndef PLAYER_UNITS_UNITS_H
#define PLAYER_UNITS_UNITS_H

#include "../defaults.h"

#include "misc.fwd.h"

#include "../utils.h"
#include "../grid.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

// Build cost logic
#define CAN_GET_WORKER(x) (x >= 100)
#define CAN_GET_SWORDSMAN(x) (x >= 250)
#define CAN_GET_ARCHER(x) (x >= 250)
#define CAN_GET_PIKEMAN(x) (x >= 200)
#define CAN_GET_KNIGHT(x) (x >= 400)
#define CAN_GET_RAM(x) (x >= 500)
#define CAN_GET_CATAPULT(x) (x >= 800)

// Damage
#define WORKER2KNIGHT 5
#define WORKER2SWORDSMAN 5
#define WORKER2ARCHER 5
#define WORKER2PIKEMAN 5
#define WORKER2CATAPULT 5
#define WORKER2RAM 5
#define WORKER2WORKER 5
#define WORKER2BASE 1

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

#define KNIGHT2KNIGHT 35
#define KNIGHT2SWORDSMAN 35
#define KNIGHT2ARCHER 35
#define KNIGHT2PIKEMAN 35
#define KNIGHT2CATAPULT 35
#define KNIGHT2RAM 50
#define KNIGHT2WORKER 35
#define KNIGHT2BASE 35

#define RAM2KNIGHT 10
#define RAM2SWORDSMAN 10
#define RAM2ARCHER 10
#define RAM2PIKEMAN 10
#define RAM2CATAPULT 10
#define RAM2RAM 10
#define RAM2WORKER 10
#define RAM2BASE 50

#define CATAPULT2KNIGHT 40
#define CATAPULT2SWORDSMAN 40
#define CATAPULT2ARCHER 40
#define CATAPULT2PIKEMAN 40
#define CATAPULT2CATAPULT 40
#define CATAPULT2RAM 40
#define CATAPULT2WORKER 40
#define CATAPULT2BASE 50

// Speed
#define SPEED_WORKER 2
#define SPEED_SWORDSMAN 2
#define SPEED_ARCHER 2
#define SPEED_PIKEMAN 2
#define SPEED_KNIGHT 5
#define SPEED_RAM 2
#define SPEED_CATAPULT 2

// Attack Range
#define ATTACK_WORKER 1
#define ATTACK_SWORDSMAN 1
#define ATTACK_ARCHER 5
#define ATTACK_PIKEMAN 2
#define ATTACK_KNIGHT 1
#define ATTACK_RAM 1
#define ATTACK_CATAPULT 7

// Abstract interface for units
class Unit
{
public:
    // Unit id
    int id;
    // Unit HP
    int endurance;
    // Unit position
    int posx, posy;
    // Coordinates of the target
    int trgtX, trgtY;
    
    Unit(int ident, int end, int px, int py);
    virtual ~Unit() = 0;

    virtual bool find_target(const grid &map, listUnits &allies, listUnits &enemies) = 0;
};

class Base : public Unit
{
public:
    char queue;
    bool init;

    Base();
    Base(int ident, int end, int px, int py, char q);
    ~Base();

    bool isInit();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Worker : public Unit
{
public:
    Worker(int ident, int end, int px, int py);
    ~Worker();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Swordsman : public Unit
{
public:
    Swordsman(int ident, int end, int px, int py);
    ~Swordsman();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Archer : public Unit
{
public:
    Archer(int ident, int end, int px, int py);
    ~Archer();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Pikeman : public Unit
{
public:
    Pikeman(int ident, int end, int px, int py);
    ~Pikeman();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Knight : public Unit
{
public:
    Knight(int ident, int end, int px, int py);
    ~Knight();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Ram : public Unit
{
public:
    Ram(int ident, int end, int px, int py);
    ~Ram();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

class Catapult : public Unit
{
public:
    Catapult(int ident, int end, int px, int py);
    ~Catapult();

    bool find_target(const grid &map, listUnits &allies, listUnits &enemies);
};

#endif