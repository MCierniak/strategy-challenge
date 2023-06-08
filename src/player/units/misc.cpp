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

#include "misc.h"

bool listUnits::addBase(int ident, int end, int px, int py, char q)
{
    if (!this->is_unique(ident)) return false;

    this->base = Base(ident, end, px, py, q);
    this->id2arange[ident] = 0;
    this->id2type[ident] = 'B';
    this->id2speed[ident] = 0;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = 0;
    this->id2dmg[ident]['W'] = 0;
    this->id2dmg[ident]['K'] = 0;
    this->id2dmg[ident]['P'] = 0;
    this->id2dmg[ident]['C'] = 0;
    this->id2dmg[ident]['R'] = 0;
    this->id2dmg[ident]['A'] = 0;
    this->id2dmg[ident]['S'] = 0;

    this->id2moveattackV[ident] = std::vector<std::vector<int>>();
    this->id2attackV[ident] = std::vector<std::vector<int>>();
    this->id2moveV[ident] = std::vector<std::vector<int>>();

    return true;
}

bool listUnits::addUnit(char type, int ident, int end, int px, int py)
{
    switch (type)
    {
    case 'W':
        return addWorker(ident, end, px, py);
    case 'C':
        return addCatapult(ident, end, px, py);
    case 'R':
        return addRam(ident, end, px, py);
    case 'P':
        return addPikeman(ident, end, px, py);
    case 'A':
        return addArcher(ident, end, px, py);
    case 'S':
        return addSwordsman(ident, end, px, py);
    case 'K':
        return addKnight(ident, end, px, py);
    default:
        return false;
    }
}

bool listUnits::addWorker(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Worker>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_WORKER;
    this->id2speed[ident] = SPEED_WORKER;
    this->id2type[ident] = 'W';
    this->qWorker += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = WORKER2BASE;
    this->id2dmg[ident]['W'] = WORKER2WORKER;
    this->id2dmg[ident]['K'] = WORKER2KNIGHT;
    this->id2dmg[ident]['P'] = WORKER2PIKEMAN;
    this->id2dmg[ident]['C'] = WORKER2CATAPULT;
    this->id2dmg[ident]['R'] = WORKER2RAM;
    this->id2dmg[ident]['A'] = WORKER2ARCHER;
    this->id2dmg[ident]['S'] = WORKER2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addCatapult(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Catapult>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_CATAPULT;
    this->id2speed[ident] = SPEED_CATAPULT;
    this->id2type[ident] = 'C';
    this->qCatapult += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = CATAPULT2BASE;
    this->id2dmg[ident]['W'] = CATAPULT2WORKER;
    this->id2dmg[ident]['K'] = CATAPULT2KNIGHT;
    this->id2dmg[ident]['P'] = CATAPULT2PIKEMAN;
    this->id2dmg[ident]['C'] = CATAPULT2CATAPULT;
    this->id2dmg[ident]['R'] = CATAPULT2RAM;
    this->id2dmg[ident]['A'] = CATAPULT2ARCHER;
    this->id2dmg[ident]['S'] = CATAPULT2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_8;
    this->id2attackV[ident] = MOVE_7;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addRam(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;
    
    this->units[ident] = std::make_unique<Ram>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_RAM;
    this->id2speed[ident] = SPEED_RAM;
    this->id2type[ident] = 'R';
    this->qRam += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = RAM2BASE;
    this->id2dmg[ident]['W'] = RAM2WORKER;
    this->id2dmg[ident]['K'] = RAM2KNIGHT;
    this->id2dmg[ident]['P'] = RAM2PIKEMAN;
    this->id2dmg[ident]['C'] = RAM2CATAPULT;
    this->id2dmg[ident]['R'] = RAM2RAM;
    this->id2dmg[ident]['A'] = RAM2ARCHER;
    this->id2dmg[ident]['S'] = RAM2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addPikeman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Pikeman>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_PIKEMAN;
    this->id2speed[ident] = SPEED_PIKEMAN;
    this->id2type[ident] = 'P';
    this->qPikeman += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = PIKEMAN2BASE;
    this->id2dmg[ident]['W'] = PIKEMAN2WORKER;
    this->id2dmg[ident]['K'] = PIKEMAN2KNIGHT;
    this->id2dmg[ident]['P'] = PIKEMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = PIKEMAN2CATAPULT;
    this->id2dmg[ident]['R'] = PIKEMAN2RAM;
    this->id2dmg[ident]['A'] = PIKEMAN2ARCHER;
    this->id2dmg[ident]['S'] = PIKEMAN2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_3;
    this->id2attackV[ident] = MOVE_2;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addArcher(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Archer>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_ARCHER;
    this->id2speed[ident] = SPEED_ARCHER;
    this->id2type[ident] = 'A';
    this->qArcher += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = ARCHER2BASE;
    this->id2dmg[ident]['W'] = ARCHER2WORKER;
    this->id2dmg[ident]['K'] = ARCHER2KNIGHT;
    this->id2dmg[ident]['P'] = ARCHER2PIKEMAN;
    this->id2dmg[ident]['C'] = ARCHER2CATAPULT;
    this->id2dmg[ident]['R'] = ARCHER2RAM;
    this->id2dmg[ident]['A'] = ARCHER2ARCHER;
    this->id2dmg[ident]['S'] = ARCHER2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_6;
    this->id2attackV[ident] = MOVE_5;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addSwordsman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Swordsman>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_SWORDSMAN;
    this->id2speed[ident] = SPEED_SWORDSMAN;
    this->id2type[ident] = 'S';
    this->qSwordsman += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = SWORDSMAN2BASE;
    this->id2dmg[ident]['W'] = SWORDSMAN2WORKER;
    this->id2dmg[ident]['K'] = SWORDSMAN2KNIGHT;
    this->id2dmg[ident]['P'] = SWORDSMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = SWORDSMAN2CATAPULT;
    this->id2dmg[ident]['R'] = SWORDSMAN2RAM;
    this->id2dmg[ident]['A'] = SWORDSMAN2ARCHER;
    this->id2dmg[ident]['S'] = SWORDSMAN2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    return true;
}

bool listUnits::addKnight(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;

    this->units[ident] = std::make_unique<Knight>(ident, end, px, py);
    this->id2arange[ident] = ATTACK_KNIGHT;
    this->id2speed[ident] = SPEED_KNIGHT;
    this->id2type[ident] = 'K';
    this->qKnight += 1;
    this->qAll += 1;

    this->id2dmg[ident]['B'] = KNIGHT2BASE;
    this->id2dmg[ident]['W'] = KNIGHT2WORKER;
    this->id2dmg[ident]['K'] = KNIGHT2KNIGHT;
    this->id2dmg[ident]['P'] = KNIGHT2PIKEMAN;
    this->id2dmg[ident]['C'] = KNIGHT2CATAPULT;
    this->id2dmg[ident]['R'] = KNIGHT2RAM;
    this->id2dmg[ident]['A'] = KNIGHT2ARCHER;
    this->id2dmg[ident]['S'] = KNIGHT2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_5;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_5;

    return true;
}

bool listUnits::is_unique(int id)
{
    return (this->id2type.find(id) == this->id2type.end());
}

int Dist(int xFirst, int yFirst, int xSecond, int ySecond)
{
    return std::abs(int(xFirst) - int(xSecond)) + std::abs(int(yFirst) - int(ySecond));
}