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
    this->id2slowMoveV[ident] = std::vector<std::vector<int>>();
    this->id2attackV[ident] = std::vector<std::vector<int>>();
    this->id2moveV[ident] = std::vector<std::vector<int>>();

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_7;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_2;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_5;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_1;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_2;

    this->hitList.push_back(ident);

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
    this->id2slowMoveV[ident] = MOVE_4;
    this->id2attackV[ident] = MOVE_1;
    this->id2moveV[ident] = MOVE_5;

    this->hitList.push_back(ident);

    return true;
}

bool listUnits::is_unique(int id)
{
    return (this->id2type.find(id) == this->id2type.end());
}

bool find_target_swordsman(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    std::cout << "(Player) (Swordsman) Looking for targets in attack range..." << std::endl;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            std::cout << "(Player) (Swordsman) Found targets in attack range. Staying in place." << std::endl;
            allies.units[sId]->trgtX = allies.units[sId]->posx;
            allies.units[sId]->trgtY = allies.units[sId]->posy;
            return true;
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    std::cout << "(Player) (Swordsman) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    for (auto &&mod : allies.id2moveattackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId])
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue;
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue;

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                {
                    std::cout << "(Player) (Swordsman) Found targets in move-attack range. Moving to position." << std::endl;
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest enemy to own base, move within attack range
    std::cout << "(Player) (Swordsman) No targets in move-attack range. Looking for distant targets..." << std::endl;
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    for (auto &&eId : enemies.hitList)
    {
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B')
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Swordsman) Found target. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    std::cout << "(Player) (Swordsman) No viable targets found." << std::endl;
    return false;
}

bool find_target_archer(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    std::cout << "(Player) (Archer) Looking for targets in attack range..." << std::endl;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            std::cout << "(Player) (Archer) Found targets in attack range. Staying in place." << std::endl;
            allies.units[sId]->trgtX = allies.units[sId]->posx;
            allies.units[sId]->trgtY = allies.units[sId]->posy;
            return true;
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    std::cout << "(Player) (Archer) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    for (auto &&mod : allies.id2moveattackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId])
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue;
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue;

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                {
                    std::cout << "(Player) (Archer) Found targets in move-attack range. Moving to position." << std::endl;
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest worker to own base, move within attack range
    std::cout << "(Player) (Archer) No targets in move-attack range. Looking for distant enemy workers..." << std::endl;
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qWorker > 0)
    {
        for (auto &&eId : enemies.hitList)
        {
            if (!(enemies.id2type[eId] == 'W')) continue;
            evade_queue closestGridNode;
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue;
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty())
            {
                std::cout << "(Player) (Archer) Found worker target. Calculating path..." << std::endl;
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no workers, find closest enemy to own base, move within attack range
    std::cout << "(Player) (Archer) Did not find workers. Looking for other targets..." << std::endl;
    for (auto &&eId : enemies.hitList)
    {
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B')
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Archer) Found target. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    std::cout << "(Player) (Archer) No viable targets found." << std::endl;
    return false;
}

bool find_target_pikeman(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    std::cout << "(Player) (Pikeman) Looking for targets in attack range..." << std::endl;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            std::cout << "(Player) (Pikeman) Found targets in attack range. Staying in place." << std::endl;
            allies.units[sId]->trgtX = allies.units[sId]->posx;
            allies.units[sId]->trgtY = allies.units[sId]->posy;
            return true;
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    std::cout << "(Player) (Pikeman) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    for (auto &&mod : allies.id2moveattackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId])
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue;
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue;

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                {
                    std::cout << "(Player) (Pikeman) Found targets in move-attack range. Moving to position." << std::endl;
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest knight to own base, move within attack range
    std::cout << "(Player) (Pikeman) No targets in move-attack range. Looking for distant enemy knights..." << std::endl;
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qKnight > 0)
    {
        for (auto &&eId : enemies.hitList)
        {
            if (!(enemies.id2type[eId] == 'K')) continue;
            evade_queue closestGridNode;
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue;
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty())
            {
                std::cout << "(Player) (Pikeman) Found knight target. Calculating path..." << std::endl;
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no knights, find closest enemy to own base, move within attack range
    std::cout << "(Player) (Pikeman) Did not find workers. Looking for other targets..." << std::endl;
    for (auto &&eId : enemies.hitList)
    {
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B')
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Pikeman) Found target. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    std::cout << "(Player) (Pikeman) No viable targets found." << std::endl;
    return false;
}

bool find_target_knight(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    std::cout << "(Player) (Knight) Looking for targets in attack range..." << std::endl;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            std::cout << "(Player) (Knight) Found targets in attack range. Staying in place." << std::endl;
            allies.units[sId]->trgtX = allies.units[sId]->posx;
            allies.units[sId]->trgtY = allies.units[sId]->posy;
            return true;
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    std::cout << "(Player) (Knight) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    for (auto &&mod : allies.id2moveattackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId])
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue;
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue;

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                {
                    std::cout << "(Player) (Knight) Found targets in move-attack range. Moving to position." << std::endl;
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest catapult/ram/archer/worker to own base,
    // move within attack range
    std::cout << "(Player) (Knight) No targets in move-attack range. Looking for distant enemy catapults, rams, archers or workers..." << std::endl;
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    if (enemies.qCatapult > 0 || enemies.qRam > 0 || enemies.qArcher > 0 || enemies.qWorker > 0)
    {
        for (auto &&eId : enemies.hitList)
        {
            if (!(enemies.id2type[eId] == 'C' || enemies.id2type[eId] == 'R' || enemies.id2type[eId] == 'A' || enemies.id2type[eId] == 'W')) continue;
            evade_queue closestGridNode;
            for (auto &&mod : allies.id2attackV[sId])
            {
                int newY = enemies.units[eId]->posy + mod[0], newX = enemies.units[eId]->posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue;
                if (newX < 0 || newX >= int(map[newY].size())) continue;
                if (!map[newY][newX]->checkTrav()) continue;

                closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
            }
            if (!closestGridNode.empty())
            {
                std::cout << "(Player) (Knight) Found catapult/ram/archer/worker target. Calculating path..." << std::endl;
                coord trgt = closestGridNode.top().second;
                allies.units[sId]->trgtX = trgt.second;
                allies.units[sId]->trgtY = trgt.first;
                return true;
            }
        }
    }
    // Else, if enemy has no catapults/rams/archers/workers, find closest enemy to own base, move within attack range
    std::cout << "(Player) (Knight) Did not find catapults/rams/archers/workers. Looking for other targets..." << std::endl;
    for (auto &&eId : enemies.hitList)
    {
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B')
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Knight) Found target. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    std::cout << "(Player) (Knight) No viable targets found." << std::endl;
    return false;
}

bool find_target_ram(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    int sX = allies.units[sId]->posx, sY = allies.units[sId]->posy;
    int bX = enemies.base.posx, bY = enemies.base.posy;
    // If base in attack range, stay in place
    std::cout << "(Player) (Ram) Looking for enemy base..." << std::endl;
    if (Dist(sX, sY, bX, bY) == allies.id2arange[sId])
    {
        std::cout << "(Player) (Ram) Enemy base in range. Staying in place." << std::endl;
        allies.units[sId]->trgtX = allies.units[sId]->posx;
        allies.units[sId]->trgtY = allies.units[sId]->posy;
        return true;
    }
    // Else, if base within move-attack range, move to position
    else if (Dist(sX, sY, bX, bY) == allies.id2speed[sId] - 1)
    {
        std::cout << "(Player) (Ram) Enemy base in move-attack range. Looking for path..." << std::endl;
        for (auto &&mod : allies.id2moveattackV[sId])
        {
            int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;

            if(newY == bY && newX == bX)
            {
                for (auto &&mod2 : allies.id2slowMoveV[sId])
                {
                    int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                    if (newY2 < 0 || newY2 >= int(map.size())) continue;
                    if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                    if (!map[newY2][newX2]->checkTrav()) continue;

                    if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                    {
                        std::cout << "(Player) (Ram) Path found. Moving to position." << std::endl;
                        allies.units[sId]->trgtX = newX2;
                        allies.units[sId]->trgtY = newY2;
                        return true;
                    }
                }
            }
        }
        std::cout << "(Player) (Ram) Enemy base unreachable. Staying in place." << std::endl;
        return false;
    }
    // Else, if base far away, find position within range and move to it
    else
    {
        std::cout << "(Player) (Ram) Enemy base out of range. Looking for target path..." << std::endl;
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY = bY + mod[0], newX = bX + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sX, sY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Ram) Target path found. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
        else
        {
            std::cout << "(Player) (Ram) Enemy base unreachable. Staying in place." << std::endl;
            return false;
        }
    }
}

bool find_target_catapult(int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    // If enemies in range, stay in place
    std::cout << "(Player) (Catapult) Looking for targets in attack range..." << std::endl;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            std::cout << "(Player) (Catapult) Found targets in attack range. Staying in place." << std::endl;
            allies.units[sId]->trgtX = allies.units[sId]->posx;
            allies.units[sId]->trgtY = allies.units[sId]->posy;
            return true;
        }
    }
    // Else, if enemies within move-attack range, move to attack range
    std::cout << "(Player) (Catapult) No targets in attack range. Lookign for targets in move-attack range..." << std::endl;
    for (auto &&mod : allies.id2moveattackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if(map[newY][newX]->checkEnemyNr() > 0)
        {
            for (auto &&mod2 : allies.id2slowMoveV[sId])
            {
                int newY2 = allies.units[sId]->posy + mod2[0], newX2 = allies.units[sId]->posx + mod2[1];
                if (newY2 < 0 || newY2 >= int(map.size())) continue;
                if (newX2 < 0 || newX2 >= int(map[newY2].size())) continue;
                if (!map[newY2][newX2]->checkTrav()) continue;

                if (Dist(newX2, newY2, newX, newY) <= allies.id2arange[sId])
                {
                    std::cout << "(Player) (Catapult) Found targets in move-attack range. Moving to position." << std::endl;
                    allies.units[sId]->trgtX = newX2;
                    allies.units[sId]->trgtY = newY2;
                    return true;
                }
            }
        }
    }
    // Else, if no enemies in range, find closest enemy to own base, move within attack range
    std::cout << "(Player) (Catapult) No targets in move-attack range. Looking for distant targets..." << std::endl;
    int sPosX = allies.units[sId]->posx, sPosY = allies.units[sId]->posy;
    for (auto &&eId : enemies.hitList)
    {
        evade_queue closestGridNode;
        for (auto &&mod : allies.id2attackV[sId])
        {
            int newY, newX;
            if (enemies.id2type[eId] == 'B')
            {
                newY = enemies.base.posy + mod[0];
                newX = enemies.base.posx + mod[1];
            }
            else
            {
                newY = enemies.units[eId]->posy + mod[0];
                newX = enemies.units[eId]->posx + mod[1];
            }
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;

            closestGridNode.push(evade_queue_item(Dist(sPosX, sPosY, newX, newY), coord(newY, newX)));
        }
        if (!closestGridNode.empty())
        {
            std::cout << "(Player) (Catapult) Found target. Calculating path..." << std::endl;
            coord trgt = closestGridNode.top().second;
            allies.units[sId]->trgtX = trgt.second;
            allies.units[sId]->trgtY = trgt.first;
            return true;
        }
    }
    std::cout << "(Player) (Catapult) No viable targets found." << std::endl;
    return false;
}

int Dist(int xFirst, int yFirst, int xSecond, int ySecond)
{
    return std::abs(int(xFirst) - int(xSecond)) + std::abs(int(yFirst) - int(ySecond));
}