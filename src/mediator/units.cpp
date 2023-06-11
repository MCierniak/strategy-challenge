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

#include "units.h"

Unit::Unit(int ident, int end, int px, int py):
    id(ident), endurance(end), posx(px), posy(py)
{}

Base::Base():
    Unit(0, 0, 0, 0), queue('0')
{}

Base::Base(int ident, int end, int px, int py, char q):
    Unit(ident, end, px, py), queue(q)
{}

Base::Base(int ident, int end, int px, int py, char q, int qT):
    Unit(ident, end, px, py), queue(q), qTime(qT)
{}

Worker::Worker(int ident, int px, int py):
    Unit(ident, 20, px, py)
{}

Worker::Worker(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Catapult::Catapult(int ident, int px, int py):
    Unit(ident, 50, px, py)
{}

Catapult::Catapult(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Ram::Ram(int ident, int px, int py):
    Unit(ident, 90, px, py)
{}

Ram::Ram(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Pikeman::Pikeman(int ident, int px, int py):
    Unit(ident, 50, px, py)
{}

Pikeman::Pikeman(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Archer::Archer(int ident, int px, int py):
    Unit(ident, 40, px, py)
{}

Archer::Archer(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Swordsman::Swordsman(int ident, int px, int py):
    Unit(ident, 60, px, py)
{}

Swordsman::Swordsman(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

Knight::Knight(int ident, int px, int py):
    Unit(ident, 70, px, py)
{}

Knight::Knight(int ident, int end, int px, int py):
    Unit(ident, end, px, py)
{}

bool listUnits::addBase(int ident, int end, int px, int py, char q)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->id2typeName[ident] = std::string("base"); // add human-readable name
    this->base = Base(ident, end, px, py, q); // Construct base
    this->id2arange[ident] = 0; // Base cannot attack, arange = 0
    this->id2type[ident] = 'B'; // Base type char
    this->id2speed[ident] = 0; // Base cannot move, speed = 0
    this->qAll += 1; // Base counts as a unit

    this->id2dmg[ident]['B'] = 0; // Base cannot attack
    this->id2dmg[ident]['W'] = 0;
    this->id2dmg[ident]['K'] = 0;
    this->id2dmg[ident]['P'] = 0;
    this->id2dmg[ident]['C'] = 0;
    this->id2dmg[ident]['R'] = 0;
    this->id2dmg[ident]['A'] = 0;
    this->id2dmg[ident]['S'] = 0;

    return true;
}

bool listUnits::addBase(int ident, int end, int px, int py, char q, int qT)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->id2typeName[ident] = std::string("base"); // add human-readable name
    this->base = Base(ident, end, px, py, q, qT); // Construct base with active build queue
    this->id2arange[ident] = 0; // Base cannot attack, arange = 0
    this->id2type[ident] = 'B'; // Base type char
    this->id2speed[ident] = 0; // Base cannot move, speed = 0
    this->qAll += 1; // Base counts as a unit

    this->id2dmg[ident]['B'] = 0; // Base cannot attack
    this->id2dmg[ident]['W'] = 0;
    this->id2dmg[ident]['K'] = 0;
    this->id2dmg[ident]['P'] = 0;
    this->id2dmg[ident]['C'] = 0;
    this->id2dmg[ident]['R'] = 0;
    this->id2dmg[ident]['A'] = 0;
    this->id2dmg[ident]['S'] = 0;

    return true;
}

bool listUnits::removeUnit(int id)
{
    switch (this->id2type[id])
    {
    case 'W':
        return this->removeWorker(id);
    case 'C':
        return this->removeCatapult(id);
    case 'R':
        return this->removeRam(id);
    case 'P':
        return this->removePikeman(id);
    case 'A':
        return this->removeArcher(id);
    case 'S':
        return this->removeSwordsman(id);
    case 'K':
        return this->removeKnight(id);
    default:
        return false;
    }
}

bool listUnits::addWorker(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Worker>(ident, px, py); // create unique_ptr for a Worker object with max endurance
    this->id2typeName[ident] = std::string("worker"); // add human-readable name
    this->id2arange[ident] = ATTACK_WORKER; // add attack range value (int)
    this->id2speed[ident] = SPEED_WORKER; // add speed value (int)
    this->id2type[ident] = 'W'; // add unit type (char)
    this->qWorker += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = WORKER2BASE; // populate damage map
    this->id2dmg[ident]['W'] = WORKER2WORKER;
    this->id2dmg[ident]['K'] = WORKER2KNIGHT;
    this->id2dmg[ident]['P'] = WORKER2PIKEMAN;
    this->id2dmg[ident]['C'] = WORKER2CATAPULT;
    this->id2dmg[ident]['R'] = WORKER2RAM;
    this->id2dmg[ident]['A'] = WORKER2ARCHER;
    this->id2dmg[ident]['S'] = WORKER2SWORDSMAN;

    return true;
}

bool listUnits::addWorker(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Worker>(ident, end, px, py); // create unique_ptr for a Worker object
    this->id2typeName[ident] = std::string("worker"); // add human-readable name
    this->id2arange[ident] = ATTACK_WORKER; // add attack range value (int)
    this->id2speed[ident] = SPEED_WORKER; // add speed value (int)
    this->id2type[ident] = 'W'; // add unit type (char)
    this->qWorker += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = WORKER2BASE; // populate damage map
    this->id2dmg[ident]['W'] = WORKER2WORKER;
    this->id2dmg[ident]['K'] = WORKER2KNIGHT;
    this->id2dmg[ident]['P'] = WORKER2PIKEMAN;
    this->id2dmg[ident]['C'] = WORKER2CATAPULT;
    this->id2dmg[ident]['R'] = WORKER2RAM;
    this->id2dmg[ident]['A'] = WORKER2ARCHER;
    this->id2dmg[ident]['S'] = WORKER2SWORDSMAN;

    return true;
}

bool listUnits::removeWorker(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qWorker -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addCatapult(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Catapult>(ident, px, py); // create unique_ptr for a Catapult object with max endurance
    this->id2typeName[ident] = std::string("catapult"); // add human-readable name
    this->id2arange[ident] = ATTACK_CATAPULT; // add attack range value (int)
    this->id2speed[ident] = SPEED_CATAPULT; // add speed value (int)
    this->id2type[ident] = 'C'; // add unit type (char)
    this->qCatapult += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = CATAPULT2BASE; // populate damage map
    this->id2dmg[ident]['W'] = CATAPULT2WORKER;
    this->id2dmg[ident]['K'] = CATAPULT2KNIGHT;
    this->id2dmg[ident]['P'] = CATAPULT2PIKEMAN;
    this->id2dmg[ident]['C'] = CATAPULT2CATAPULT;
    this->id2dmg[ident]['R'] = CATAPULT2RAM;
    this->id2dmg[ident]['A'] = CATAPULT2ARCHER;
    this->id2dmg[ident]['S'] = CATAPULT2SWORDSMAN;

    return true;
}

bool listUnits::addCatapult(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Catapult>(ident, end, px, py); // create unique_ptr for a Catapult object
    this->id2typeName[ident] = std::string("catapult"); // add human-readable name
    this->id2arange[ident] = ATTACK_CATAPULT; // add attack range value (int)
    this->id2speed[ident] = SPEED_CATAPULT; // add speed value (int)
    this->id2type[ident] = 'C'; // add unit type (char)
    this->qCatapult += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = CATAPULT2BASE; // populate damage map
    this->id2dmg[ident]['W'] = CATAPULT2WORKER;
    this->id2dmg[ident]['K'] = CATAPULT2KNIGHT;
    this->id2dmg[ident]['P'] = CATAPULT2PIKEMAN;
    this->id2dmg[ident]['C'] = CATAPULT2CATAPULT;
    this->id2dmg[ident]['R'] = CATAPULT2RAM;
    this->id2dmg[ident]['A'] = CATAPULT2ARCHER;
    this->id2dmg[ident]['S'] = CATAPULT2SWORDSMAN;

    return true;
}

bool listUnits::removeCatapult(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qCatapult -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addRam(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Ram>(ident, px, py); // create unique_ptr for a ram object with max endurance
    this->id2typeName[ident] = std::string("ram"); // add human-readable name
    this->id2arange[ident] = ATTACK_RAM; // add attack range value (int)
    this->id2speed[ident] = SPEED_RAM; // add speed value (int)
    this->id2type[ident] = 'R'; // add unit type (char)
    this->qRam += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = RAM2BASE; // populate damage map
    this->id2dmg[ident]['W'] = RAM2WORKER;
    this->id2dmg[ident]['K'] = RAM2KNIGHT;
    this->id2dmg[ident]['P'] = RAM2PIKEMAN;
    this->id2dmg[ident]['C'] = RAM2CATAPULT;
    this->id2dmg[ident]['R'] = RAM2RAM;
    this->id2dmg[ident]['A'] = RAM2ARCHER;
    this->id2dmg[ident]['S'] = RAM2SWORDSMAN;

    return true;
}

bool listUnits::addRam(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check
    
    this->units[ident] = std::make_unique<Ram>(ident, end, px, py); // create unique_ptr for a ram object
    this->id2typeName[ident] = std::string("ram"); // add human-readable name
    this->id2arange[ident] = ATTACK_RAM; // add attack range value (int)
    this->id2speed[ident] = SPEED_RAM; // add speed value (int)
    this->id2type[ident] = 'R'; // add unit type (char)
    this->qRam += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = RAM2BASE; // populate damage map
    this->id2dmg[ident]['W'] = RAM2WORKER;
    this->id2dmg[ident]['K'] = RAM2KNIGHT;
    this->id2dmg[ident]['P'] = RAM2PIKEMAN;
    this->id2dmg[ident]['C'] = RAM2CATAPULT;
    this->id2dmg[ident]['R'] = RAM2RAM;
    this->id2dmg[ident]['A'] = RAM2ARCHER;
    this->id2dmg[ident]['S'] = RAM2SWORDSMAN;

    return true;
}

bool listUnits::removeRam(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qRam -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addPikeman(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Pikeman>(ident, px, py); // create unique_ptr for a pikeman object with max endurance
    this->id2typeName[ident] = std::string("pikeman"); // add human-readable name
    this->id2arange[ident] = ATTACK_PIKEMAN; // add attack range value (int)
    this->id2speed[ident] = SPEED_PIKEMAN; // add speed value (int)
    this->id2type[ident] = 'P'; // add unit type (char)
    this->qPikeman += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = PIKEMAN2BASE; // populate damage map
    this->id2dmg[ident]['W'] = PIKEMAN2WORKER;
    this->id2dmg[ident]['K'] = PIKEMAN2KNIGHT;
    this->id2dmg[ident]['P'] = PIKEMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = PIKEMAN2CATAPULT;
    this->id2dmg[ident]['R'] = PIKEMAN2RAM;
    this->id2dmg[ident]['A'] = PIKEMAN2ARCHER;
    this->id2dmg[ident]['S'] = PIKEMAN2SWORDSMAN;

    return true;
}

bool listUnits::addPikeman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Pikeman>(ident, end, px, py); // create unique_ptr for a pikeman object
    this->id2typeName[ident] = std::string("pikeman"); // add human-readable name
    this->id2arange[ident] = ATTACK_PIKEMAN; // add attack range value (int)
    this->id2speed[ident] = SPEED_PIKEMAN; // add speed value (int)
    this->id2type[ident] = 'P'; // add unit type (char)
    this->qPikeman += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = PIKEMAN2BASE; // populate damage map
    this->id2dmg[ident]['W'] = PIKEMAN2WORKER;
    this->id2dmg[ident]['K'] = PIKEMAN2KNIGHT;
    this->id2dmg[ident]['P'] = PIKEMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = PIKEMAN2CATAPULT;
    this->id2dmg[ident]['R'] = PIKEMAN2RAM;
    this->id2dmg[ident]['A'] = PIKEMAN2ARCHER;
    this->id2dmg[ident]['S'] = PIKEMAN2SWORDSMAN;

    return true;
}

bool listUnits::removePikeman(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qPikeman -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addArcher(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Archer>(ident, px, py); // create unique_ptr for an archer object with max endurance
    this->id2typeName[ident] = std::string("archer"); // add human-readable name
    this->id2arange[ident] = ATTACK_ARCHER; // add attack range value (int)
    this->id2speed[ident] = SPEED_ARCHER; // add speed value (int)
    this->id2type[ident] = 'A'; // add unit type (char)
    this->qArcher += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = ARCHER2BASE; // populate damage map
    this->id2dmg[ident]['W'] = ARCHER2WORKER;
    this->id2dmg[ident]['K'] = ARCHER2KNIGHT;
    this->id2dmg[ident]['P'] = ARCHER2PIKEMAN;
    this->id2dmg[ident]['C'] = ARCHER2CATAPULT;
    this->id2dmg[ident]['R'] = ARCHER2RAM;
    this->id2dmg[ident]['A'] = ARCHER2ARCHER;
    this->id2dmg[ident]['S'] = ARCHER2SWORDSMAN;

    return true;
}

bool listUnits::addArcher(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Archer>(ident, end, px, py); // create unique_ptr for an archer object
    this->id2typeName[ident] = std::string("archer"); // add human-readable name
    this->id2arange[ident] = ATTACK_ARCHER; // add attack range value (int)
    this->id2speed[ident] = SPEED_ARCHER; // add speed value (int)
    this->id2type[ident] = 'A'; // add unit type (char)
    this->qArcher += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = ARCHER2BASE; // populate damage map
    this->id2dmg[ident]['W'] = ARCHER2WORKER;
    this->id2dmg[ident]['K'] = ARCHER2KNIGHT;
    this->id2dmg[ident]['P'] = ARCHER2PIKEMAN;
    this->id2dmg[ident]['C'] = ARCHER2CATAPULT;
    this->id2dmg[ident]['R'] = ARCHER2RAM;
    this->id2dmg[ident]['A'] = ARCHER2ARCHER;
    this->id2dmg[ident]['S'] = ARCHER2SWORDSMAN;

    return true;
}

bool listUnits::removeArcher(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qArcher -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addSwordsman(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Swordsman>(ident, px, py); // create unique_ptr for a swordsman object with max endurance
    this->id2typeName[ident] = std::string("swordsman"); // add human-readable name
    this->id2arange[ident] = ATTACK_SWORDSMAN; // add attack range value (int)
    this->id2speed[ident] = SPEED_SWORDSMAN; // add speed value (int)
    this->id2type[ident] = 'S'; // add unit type (char)
    this->qSwordsman += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = SWORDSMAN2BASE; // populate damage map
    this->id2dmg[ident]['W'] = SWORDSMAN2WORKER;
    this->id2dmg[ident]['K'] = SWORDSMAN2KNIGHT;
    this->id2dmg[ident]['P'] = SWORDSMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = SWORDSMAN2CATAPULT;
    this->id2dmg[ident]['R'] = SWORDSMAN2RAM;
    this->id2dmg[ident]['A'] = SWORDSMAN2ARCHER;
    this->id2dmg[ident]['S'] = SWORDSMAN2SWORDSMAN;

    return true;
}

bool listUnits::addSwordsman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Swordsman>(ident, end, px, py); // create unique_ptr for a swordsman object
    this->id2typeName[ident] = std::string("swordsman"); // add human-readable name
    this->id2arange[ident] = ATTACK_SWORDSMAN; // add attack range value (int)
    this->id2speed[ident] = SPEED_SWORDSMAN; // add speed value (int)
    this->id2type[ident] = 'S'; // add unit type (char)
    this->qSwordsman += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = SWORDSMAN2BASE; // populate damage map
    this->id2dmg[ident]['W'] = SWORDSMAN2WORKER;
    this->id2dmg[ident]['K'] = SWORDSMAN2KNIGHT;
    this->id2dmg[ident]['P'] = SWORDSMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = SWORDSMAN2CATAPULT;
    this->id2dmg[ident]['R'] = SWORDSMAN2RAM;
    this->id2dmg[ident]['A'] = SWORDSMAN2ARCHER;
    this->id2dmg[ident]['S'] = SWORDSMAN2SWORDSMAN;

    return true;
}

bool listUnits::removeSwordsman(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qSwordsman -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::addKnight(int ident, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Knight>(ident, px, py); // create unique_ptr for a knight object with max endurance
    this->id2typeName[ident] = std::string("knight"); // add human-readable name
    this->id2arange[ident] = ATTACK_KNIGHT; // add attack range value (int)
    this->id2speed[ident] = SPEED_KNIGHT; // add speed value (int)
    this->id2type[ident] = 'K'; // add unit type (char)
    this->qKnight += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = KNIGHT2BASE; // populate damage map
    this->id2dmg[ident]['W'] = KNIGHT2WORKER;
    this->id2dmg[ident]['K'] = KNIGHT2KNIGHT;
    this->id2dmg[ident]['P'] = KNIGHT2PIKEMAN;
    this->id2dmg[ident]['C'] = KNIGHT2CATAPULT;
    this->id2dmg[ident]['R'] = KNIGHT2RAM;
    this->id2dmg[ident]['A'] = KNIGHT2ARCHER;
    this->id2dmg[ident]['S'] = KNIGHT2SWORDSMAN;

    return true;
}

bool listUnits::addKnight(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false; // id uniqness check

    this->units[ident] = std::make_unique<Knight>(ident, end, px, py); // create unique_ptr for a knight object
    this->id2typeName[ident] = std::string("knight"); // add human-readable name
    this->id2arange[ident] = ATTACK_KNIGHT; // add attack range value (int)
    this->id2speed[ident] = SPEED_KNIGHT; // add speed value (int)
    this->id2type[ident] = 'K'; // add unit type (char)
    this->qKnight += 1; // increment unit count
    this->qAll += 1; // increment total unit count

    this->id2dmg[ident]['B'] = KNIGHT2BASE; // populate damage map
    this->id2dmg[ident]['W'] = KNIGHT2WORKER;
    this->id2dmg[ident]['K'] = KNIGHT2KNIGHT;
    this->id2dmg[ident]['P'] = KNIGHT2PIKEMAN;
    this->id2dmg[ident]['C'] = KNIGHT2CATAPULT;
    this->id2dmg[ident]['R'] = KNIGHT2RAM;
    this->id2dmg[ident]['A'] = KNIGHT2ARCHER;
    this->id2dmg[ident]['S'] = KNIGHT2SWORDSMAN;

    return true;
}

bool listUnits::removeKnight(int id)
{
    if (this->is_unique(id)) return false; // check if id exists

    this->units.erase(id); // erase all map elements with this id key
    this->id2typeName.erase(id);
    this->id2arange.erase(id);
    this->id2speed.erase(id);
    this->id2type.erase(id);
    this->qKnight -= 1; // decrement unit count
    this->qAll -= 1; // decrement total unit count

    this->id2dmg.erase(id);

    return true;
}

bool listUnits::is_unique(int id)
{
    return (this->id2type.find(id) == this->id2type.end());
}

Unit::~Unit(){}

Base::~Base(){}

Worker::~Worker(){}

Catapult::~Catapult(){}

Ram::~Ram(){}

Pikeman::~Pikeman(){}

Archer::~Archer(){}

Swordsman::~Swordsman(){}

Knight::~Knight(){}

int Dist(int xFirst, int yFirst, int xSecond, int ySecond)
{
    return std::abs(int(xFirst) - int(xSecond)) + std::abs(int(yFirst) - int(ySecond));
}