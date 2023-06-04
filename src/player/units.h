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

#ifndef UNITS_H
#define UNITS_H

#include <vector>

// Vector for units
#define listW std::vector<Worker>
#define listC std::vector<Catapult>
#define listR std::vector<Ram>
#define listP std::vector<Pikeman>
#define listA std::vector<Archer>
#define listS std::vector<Swordsman>
#define listK std::vector<Knight>
#define listB std::vector<Base>

// Abstract interface for units
class Unit
{
public:
    const int id, endurance, speed, attackRange;
    const int posx, posy;
    
    Unit(int ident, int end, int sp, int aR, int px, int py);
    virtual ~Unit() = 0;
};

class Base : public Unit
{
public:
    const char queue;
    const bool init;

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
};

#endif