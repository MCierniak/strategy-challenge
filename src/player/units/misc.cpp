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
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->base = Base(ident, end, px, py, q);                               // Construct base
    this->id2arange[ident] = 0;                                             // Base cannot attack, arange = 0
    this->id2type[ident] = 'B';                                             // Base type char
    this->id2speed[ident] = 0;                                              // Base cannot move, speed = 0
    this->qAll += 1;                                                        // Base counts as a unit

    this->id2dmg[ident]['B'] = 0;                                           // Base cannot attack
    this->id2dmg[ident]['W'] = 0; 
    this->id2dmg[ident]['K'] = 0;
    this->id2dmg[ident]['P'] = 0;
    this->id2dmg[ident]['C'] = 0;
    this->id2dmg[ident]['R'] = 0;
    this->id2dmg[ident]['A'] = 0;
    this->id2dmg[ident]['S'] = 0;

    this->id2moveattackV[ident] = std::vector<std::vector<int>>();          // Base cannot attack or move, all permutation vectors set to empty
    this->id2slowMoveV[ident] = std::vector<std::vector<int>>();
    this->id2attackV[ident] = std::vector<std::vector<int>>();
    this->id2moveV[ident] = std::vector<std::vector<int>>();

    this->hitList.push_back(ident);                                         // Push base to hitList, presumably will stay at the bottom

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
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Worker>(ident, end, px, py);      // create unique_ptr for a Worker object
    this->id2arange[ident] = ATTACK_WORKER;                                 // add attack range value (int)
    this->id2speed[ident] = SPEED_WORKER;                                   // add speed value (int)
    this->id2type[ident] = 'W';                                             // add unit type (char)
    this->qWorker += 1;                                                     // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = WORKER2BASE;                                 // populate damage map
    this->id2dmg[ident]['W'] = WORKER2WORKER;
    this->id2dmg[ident]['K'] = WORKER2KNIGHT;
    this->id2dmg[ident]['P'] = WORKER2PIKEMAN;
    this->id2dmg[ident]['C'] = WORKER2CATAPULT;
    this->id2dmg[ident]['R'] = WORKER2RAM;
    this->id2dmg[ident]['A'] = WORKER2ARCHER;
    this->id2dmg[ident]['S'] = WORKER2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addCatapult(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Catapult>(ident, end, px, py);    // create unique_ptr for a Catapult object
    this->id2arange[ident] = ATTACK_CATAPULT;                               // add attack range value (int)
    this->id2speed[ident] = SPEED_CATAPULT;                                 // add speed value (int)
    this->id2type[ident] = 'C';                                             // add unit type (char)
    this->qCatapult += 1;                                                   // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = CATAPULT2BASE;                               // populate damage map
    this->id2dmg[ident]['W'] = CATAPULT2WORKER;
    this->id2dmg[ident]['K'] = CATAPULT2KNIGHT;
    this->id2dmg[ident]['P'] = CATAPULT2PIKEMAN;
    this->id2dmg[ident]['C'] = CATAPULT2CATAPULT;
    this->id2dmg[ident]['R'] = CATAPULT2RAM;
    this->id2dmg[ident]['A'] = CATAPULT2ARCHER;
    this->id2dmg[ident]['S'] = CATAPULT2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_8;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_7;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addRam(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check
    
    this->units[ident] = std::make_unique<Ram>(ident, end, px, py);         // create unique_ptr for a ram object
    this->id2arange[ident] = ATTACK_RAM;                                    // add attack range value (int)
    this->id2speed[ident] = SPEED_RAM;                                      // add speed value (int)
    this->id2type[ident] = 'R';                                             // add unit type (char)
    this->qRam += 1;                                                        // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = RAM2BASE;                                    // populate damage map
    this->id2dmg[ident]['W'] = RAM2WORKER;
    this->id2dmg[ident]['K'] = RAM2KNIGHT;
    this->id2dmg[ident]['P'] = RAM2PIKEMAN;
    this->id2dmg[ident]['C'] = RAM2CATAPULT;
    this->id2dmg[ident]['R'] = RAM2RAM;
    this->id2dmg[ident]['A'] = RAM2ARCHER;
    this->id2dmg[ident]['S'] = RAM2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addPikeman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Pikeman>(ident, end, px, py);     // create unique_ptr for a pikeman object
    this->id2arange[ident] = ATTACK_PIKEMAN;                                // add attack range value (int)
    this->id2speed[ident] = SPEED_PIKEMAN;                                  // add speed value (int)
    this->id2type[ident] = 'P';                                             // add unit type (char)
    this->qPikeman += 1;                                                    // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = PIKEMAN2BASE;                                // populate damage map
    this->id2dmg[ident]['W'] = PIKEMAN2WORKER;
    this->id2dmg[ident]['K'] = PIKEMAN2KNIGHT;
    this->id2dmg[ident]['P'] = PIKEMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = PIKEMAN2CATAPULT;
    this->id2dmg[ident]['R'] = PIKEMAN2RAM;
    this->id2dmg[ident]['A'] = PIKEMAN2ARCHER;
    this->id2dmg[ident]['S'] = PIKEMAN2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_3;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_2;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addArcher(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Archer>(ident, end, px, py);      // create unique_ptr for an archer object
    this->id2arange[ident] = ATTACK_ARCHER;                                 // add attack range value (int)
    this->id2speed[ident] = SPEED_ARCHER;                                   // add speed value (int)
    this->id2type[ident] = 'A';                                             // add unit type (char)
    this->qArcher += 1;                                                     // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = ARCHER2BASE;                                 // populate damage map
    this->id2dmg[ident]['W'] = ARCHER2WORKER;
    this->id2dmg[ident]['K'] = ARCHER2KNIGHT;
    this->id2dmg[ident]['P'] = ARCHER2PIKEMAN;
    this->id2dmg[ident]['C'] = ARCHER2CATAPULT;
    this->id2dmg[ident]['R'] = ARCHER2RAM;
    this->id2dmg[ident]['A'] = ARCHER2ARCHER;
    this->id2dmg[ident]['S'] = ARCHER2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_6;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_5;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addSwordsman(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Swordsman>(ident, end, px, py);   // create unique_ptr for a swordsman object
    this->id2arange[ident] = ATTACK_SWORDSMAN;                              // add attack range value (int)
    this->id2speed[ident] = SPEED_SWORDSMAN;                                // add speed value (int)
    this->id2type[ident] = 'S';                                             // add unit type (char)
    this->qSwordsman += 1;                                                  // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = SWORDSMAN2BASE;                              // populate damage map
    this->id2dmg[ident]['W'] = SWORDSMAN2WORKER;
    this->id2dmg[ident]['K'] = SWORDSMAN2KNIGHT;
    this->id2dmg[ident]['P'] = SWORDSMAN2PIKEMAN;
    this->id2dmg[ident]['C'] = SWORDSMAN2CATAPULT;
    this->id2dmg[ident]['R'] = SWORDSMAN2RAM;
    this->id2dmg[ident]['A'] = SWORDSMAN2ARCHER;
    this->id2dmg[ident]['S'] = SWORDSMAN2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_2;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::addKnight(int ident, int end, int px, int py)
{
    if (!this->is_unique(ident)) return false;                              // id uniqness check

    this->units[ident] = std::make_unique<Knight>(ident, end, px, py);      // create unique_ptr for a knight object
    this->id2arange[ident] = ATTACK_KNIGHT;                                 // add attack range value (int)
    this->id2speed[ident] = SPEED_KNIGHT;                                   // add speed value (int)
    this->id2type[ident] = 'K';                                             // add unit type (char)
    this->qKnight += 1;                                                     // increment unit count
    this->qAll += 1;                                                        // increment total unit count

    this->id2dmg[ident]['B'] = KNIGHT2BASE;                                 // populate damage map
    this->id2dmg[ident]['W'] = KNIGHT2WORKER;
    this->id2dmg[ident]['K'] = KNIGHT2KNIGHT;
    this->id2dmg[ident]['P'] = KNIGHT2PIKEMAN;
    this->id2dmg[ident]['C'] = KNIGHT2CATAPULT;
    this->id2dmg[ident]['R'] = KNIGHT2RAM;
    this->id2dmg[ident]['A'] = KNIGHT2ARCHER;
    this->id2dmg[ident]['S'] = KNIGHT2SWORDSMAN;

    this->id2moveattackV[ident] = MOVE_5;                                   // add move, move-attack, attack in place and slow move permutation matrices
    this->id2slowMoveV[ident] = MOVE_4;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_5;

    this->hitList.push_back(ident);                                         // add id to hitList 

    return true;
}

bool listUnits::is_unique(int id)
{
    return (this->id2type.find(id) == this->id2type.end());
}

bool find_target_swordsman(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Swordsman) Looking for targets in attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2attackV[sId]) // check all gridObj within attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Swordsman) Found targets in attack range. Staying in place." << std::endl;
            #endif
            for (auto &&enemId : map[newY][newX]->getEnemyId())
            {
                if (enemies.id2type[enemId] == 'B') // watch out for base, calling listUnits::units with this id will cause Segmentation Fault
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
                else if (enemies.units[enemId]->endurance > 0) // if not base, check if enemy still alive before setting target
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
            }
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Swordsman) Nevermind." << std::endl;
            #endif
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Swordsman) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy within attack range after speed-1 movement, set target
                {
                    #ifdef VERBOSE_TRUE
                        std::cout << "(Player) (Swordsman) Found targets in move-attack range. Moving to position." << std::endl;
                    #endif
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest enemy to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Swordsman) No targets in move-attack range. Looking for distant targets..." << std::endl;
    #endif
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick any enemy
    {
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B') // SegFault guard
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Swordsman) Found target. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Swordsman) No viable targets found." << std::endl;
    #endif
    return false;
}

bool find_target_archer(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Archer) Looking for targets in attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2attackV[sId]) // check all gridObj within attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Archer) Found targets in attack range. Staying in place." << std::endl;
            #endif
            for (auto &&enemId : map[newY][newX]->getEnemyId())
            {
                if (enemies.id2type[enemId] == 'B') // watch out for base, calling listUnits::units with this id will cause Segmentation Fault
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
                else if (enemies.units[enemId]->endurance > 0) // if not base, check if enemy still alive before setting target
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
            }
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Archer) Nevermind." << std::endl;
            #endif
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Archer) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy within attack range after speed-1 movement, set target
                {
                    #ifdef VERBOSE_TRUE
                        std::cout << "(Player) (Archer) Found targets in move-attack range. Moving to position." << std::endl;
                    #endif
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest worker to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Archer) No targets in move-attack range. Looking for distant enemy workers..." << std::endl;
    #endif
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qWorker > 0)
    {
        for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick the first worker
        {
            if (!(enemies.id2type[eId] == 'W')) continue;
            evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
            {
                #ifdef VERBOSE_TRUE
                    std::cout << "(Player) (Archer) Found worker target. Calculating path..." << std::endl;
                #endif
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no workers, find closest enemy to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Archer) Did not find workers. Looking for other targets..." << std::endl;
    #endif
    for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick any enemy
    {
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B') // SegFault guard
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Archer) Found target. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Archer) No viable targets found." << std::endl;
    #endif
    return false;
}

bool find_target_pikeman(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Pikeman) Looking for targets in attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2attackV[sId]) // check all gridObj within attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Pikeman) Found targets in attack range. Staying in place." << std::endl;
            #endif
            for (auto &&enemId : map[newY][newX]->getEnemyId()) 
            {
                if (enemies.id2type[enemId] == 'B') // watch out for base, calling listUnits::units with this id will cause Segmentation Fault
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
                else if (enemies.units[enemId]->endurance > 0) // if not base, check if enemy still alive before setting target
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
            }
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Pikeman) Nevermind." << std::endl;
            #endif
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Pikeman) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy within attack range after speed-1 movement, set target
                {
                    #ifdef VERBOSE_TRUE
                        std::cout << "(Player) (Pikeman) Found targets in move-attack range. Moving to position." << std::endl;
                    #endif
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest knight to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Pikeman) No targets in move-attack range. Looking for distant enemy knights..." << std::endl;
    #endif
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qKnight > 0)
    {
        for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick the first knight
        {
            if (!(enemies.id2type[eId] == 'K')) continue;
            evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
            {
                #ifdef VERBOSE_TRUE
                    std::cout << "(Player) (Pikeman) Found knight target. Calculating path..." << std::endl;
                #endif
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no knights, find closest enemy to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Pikeman) Did not find workers. Looking for other targets..." << std::endl;
    #endif
    for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick any enemy
    {
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B') // SegFault guard
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Pikeman) Found target. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Pikeman) No viable targets found." << std::endl;
    #endif
    return false;
}

bool find_target_knight(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Knight) Looking for targets in attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2attackV[sId]) // check all gridObj within attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Knight) Found targets in attack range. Staying in place." << std::endl;
            #endif
            for (auto &&enemId : map[newY][newX]->getEnemyId())
            {
                if (enemies.id2type[enemId] == 'B') // watch out for base, calling listUnits::units with this id will cause Segmentation Fault
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
                else if (enemies.units[enemId]->endurance > 0) // if not base, check if enemy still alive before setting target
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
            }
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Knight) Nevermind." << std::endl;
            #endif
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Knight) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy within attack range after speed-1 movement, set target
                {
                    #ifdef VERBOSE_TRUE
                        std::cout << "(Player) (Knight) Found targets in move-attack range. Moving to position." << std::endl;
                    #endif
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest catapult/ram/archer/worker to own base,
    // move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Knight) No targets in move-attack range. Looking for distant enemy catapults, rams, archers or workers..." << std::endl;
    #endif
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qCatapult > 0 || enemies.qRam > 0 || enemies.qArcher > 0 || enemies.qWorker > 0)
    {
        for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick the first catapult/ram/archer/worker
        {
            if (!(enemies.id2type[eId] == 'C' || enemies.id2type[eId] == 'R' || enemies.id2type[eId] == 'A' || enemies.id2type[eId] == 'W')) continue;
            evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
            {
                #ifdef VERBOSE_TRUE
                    std::cout << "(Player) (Knight) Found catapult/ram/archer/worker target. Calculating path..." << std::endl;
                #endif
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no catapults/rams/archers/workers, find closest enemy to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Knight) Did not find catapults/rams/archers/workers. Looking for other targets..." << std::endl;
    #endif
    for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick any enemy
    {
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B') // SegFault guard
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Knight) Found target. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Knight) No viable targets found." << std::endl;
    #endif
    return false;
}

bool find_target_ram(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // Rams will only attack the enemy base
    int sX = allies.units[sId]->posx, sY = allies.units[sId]->posy;
    int bX = enemies.base.posx, bY = enemies.base.posy;
    // If base in attack range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Ram) Looking for enemy base..." << std::endl;
    #endif
    if (Dist(sX, sY, bX, bY) == allies.id2arange[sId])
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Ram) Enemy base in range. Staying in place." << std::endl;
        #endif
        allies.units[sId]->trgtX = allies.units[sId]->posx;
        allies.units[sId]->trgtY = allies.units[sId]->posy;
        return true;
    }
    // Else, if base within move-attack range, move to position
    else if (Dist(sX, sY, bX, bY) == allies.id2speed[sId] - 1)
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Ram) Enemy base in move-attack range. Looking for path..." << std::endl;
        #endif
        for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
        {
            int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;

            if(newY == bY && newX == bX)
            {
                for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
                {
                    int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                    if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                    if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                    if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                    if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy base within attack range after speed-1 movement, set target
                    {
                        #ifdef VERBOSE_TRUE
                            std::cout << "(Player) (Ram) Path found. Moving to position." << std::endl;
                        #endif
                        allies.units[sId]->trgtX = newX2;
                        allies.units[sId]->trgtY = newY2;
                        return true;
                    }
                }
            }
        }
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Ram) Enemy base unreachable. Staying in place." << std::endl;
        #endif
        return false;
    }
    // Else, if base far away, find position within range and move to it
    else
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) (Ram) Enemy base out of range. Looking for target path..." << std::endl;
        #endif
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the enemy base
        for (auto &&mod : allies.id2attackV[sId]) // Iterate over grid nodes within attack range of the base
        {
            int newY = bY + mod[0], newX = bX + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sX, sY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Ram) Target path found. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
        else // if enemy base unreachable, return false
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Ram) Enemy base unreachable. Staying in place." << std::endl;
            #endif
            return false;
        }
    }
}

bool find_target_catapult(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Catapult) Looking for targets in attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2attackV[sId]) // check all gridObj within attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Catapult) Found targets in attack range. Staying in place." << std::endl;
            #endif
            for (auto &&enemId : map[newY][newX]->getEnemyId())
            {
                if (enemies.id2type[enemId] == 'B') // watch out for base, calling listUnits::units with this id will cause Segmentation Fault
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
                else if (enemies.units[enemId]->endurance > 0) // if not base, check if enemy still alive before setting target
                {
                    allies.units[sId]->trgtX = allies.units[sId]->posx;
                    allies.units[sId]->trgtY = allies.units[sId]->posy;
                    return true;
                }
            }
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Catapult) Nevermind." << std::endl;
            #endif
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Catapult) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    #endif
    for (auto &&mod : allies.id2moveattackV[sId]) // check all gridObj within move-attack permutation vector
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0) // enemies found on grid
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId]) // check all gridObj within move-1 permutation vector
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue; // out of bounds guard
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue; // traversability check

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId]) // if enemy within attack range after speed-1 movement, set target
                {
                    #ifdef VERBOSE_TRUE
                        std::cout << "(Player) (Catapult) Found targets in move-attack range. Moving to position." << std::endl;
                    #endif
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest enemy to own base, move within attack range
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Catapult) No targets in move-attack range. Looking for distant targets..." << std::endl;
    #endif
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    for (auto &&eId : enemies.hitList) // Iterate over hitList (presumably sorted), pick any enemy
    {
        evade_queue closestGridNode; // use priority_queue for determinig closest gridObj within attack range of the target unit
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B') // SegFault guard
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traversability guard
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty()) // if queue not empty, the top will be the desired grid.
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Catapult) Found target. Calculating path..." << std::endl;
            #endif
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) (Catapult) No viable targets found." << std::endl;
    #endif
    return false;
}

int Dist(int xFirst, int yFirst, int xSecond, int ySecond)
{
    return std::abs(int(xFirst) - int(xSecond)) + std::abs(int(yFirst) - int(ySecond));
}