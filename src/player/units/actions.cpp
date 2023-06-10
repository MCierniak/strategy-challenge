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

#include "actions.h"

bool attack(std::string &payload, int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) Choosing attack target" << std::endl;
    #endif
    // queue object for sorting potential targets by endurance, ascending
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> enemiesInRange;
    std::stringstream ss; // payload buffer
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1]; // check all gridObj within attack range permutation vector
        if (newY < 0 || newY >= int(map.size())) continue; // out of bounds guard
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if (map[newY][newX]->checkEnemyNr() > 0) // found enemies
        {
            for (int i = 0; i < map[newY][newX]->checkEnemyNr(); i++)
            {
                #ifdef VERBOSE_TRUE
                    std::cout << "(Player) Found one!" << std::endl;
                #endif
                int eid = map[newY][newX]->getEnemyId(i);
                int ehp;
                if (enemies.id2type[eid] == 'B') ehp = enemies.base.endurance; // SegFault guard
                else ehp = enemies.units[eid]->endurance;
                if (ehp > 0)
                {
                    enemiesInRange.push(std::pair<int, int>(ehp, eid)); // sort enemies by endurance, exclude dead enemies
                }
                #ifdef VERBOSE_TRUE
                    else std::cout << "(Player) Nevermind..." << std::endl;
                #endif
            }
        }
    }
    if (!enemiesInRange.empty()) 
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) Target acquired." << std::endl;
        #endif
        int trgt_id = enemiesInRange.top().second;  // if queue not empty, output attack command to payload,
        ss << sId << " A " << trgt_id << '\n';      // decrement endurance so that other units won't needlesly target dead enemies
        payload += ss.str();

        if (enemies.id2type[trgt_id] == 'B') enemies.base.endurance -= allies.id2dmg[sId]['B'];
        else enemies.units[trgt_id]->endurance -= allies.id2dmg[sId][enemies.id2type[trgt_id]];

        #ifdef VERBOSE_TRUE
            std::cout << "(Player) Attacking!" << std::endl;
        #endif
        return true;
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) No viable targets in range" << std::endl;
    #endif
    return false;
}

bool evade(std::string &payload, int sId, const grid &map, listUnits &allies)
{
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) Engaging evasive maneuvers!" << std::endl;
    #endif
    evade_queue eQueue; // sort all nodes in range by potential damage next turn. top will be the best node to stand on.

    char type = allies.id2type[sId];
    int cX = allies.units[sId]->posx;
    int cY = allies.units[sId]->posy;
    if (cY < 0 || cY >= int(map.size())) return false; // sanity check
    if (cX < 0 || cX >= int(map[0].size())) return false;
    int dmg = map[cY][cX]->checkDmg(type);

    eQueue.push(evade_queue_item(dmg, coord(cY, cX)));

    // Not in range of enemies, do nothing
    if (dmg == 1) return false;

    for (auto &&mod : allies.id2moveV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if (!map[newY][newX]->checkTrav()) continue;

        dmg = map[newY][newX]->checkDmg(type);

        eQueue.push(evade_queue_item(dmg, coord(newY, newX)));

        // If target node out of range of any enemy, no point to iterate, just move to it
        if (dmg == 1)
        {
            std::stringstream ss;
            ss << sId << " M " << newX << ' ' << newY << '\n';
            payload = ss.str(); // output command payload
            if (allies.id2type[sId] == 'W') // If unit is a worker, modify workerid flags in map gridObj
            {
                map[newY][newX]->addWorkerId(sId);
                map[allies.units[sId]->posy][allies.units[sId]->posx]->removeWorkerId(sId);
            }
            allies.units[sId]->posx = newX; // make moves
            allies.units[sId]->posy = newY;
            return true;
        }
    }
    if (!eQueue.empty())
    {
        std::stringstream ss;
        coord next = eQueue.top().second;
        if (next.second == cX && next.first == cY) return false;
        ss << sId << " M " << next.second << ' ' << next.first << '\n';
        payload = ss.str(); // output command payload
        if (allies.id2type[sId] == 'W') // If unit is a worker, modify workerid flags in map gridObj
        {
            map[next.first][next.second]->addWorkerId(sId);
            map[allies.units[sId]->posy][allies.units[sId]->posx]->removeWorkerId(sId);
        }
        allies.units[sId]->posx = next.second; // make moves
        allies.units[sId]->posy = next.first;
        return true;
    }
    else return false;
}

bool cover(int sId, const grid &map, listUnits &allies, int &stepX, int &stepY)
{
    if 
    (
        (map[stepY][stepX]->checkDmg(allies.id2type[sId]) > 1 &&                                    // If moving to within range of an enemy,
        map[allies.units[sId]->posy][allies.units[sId]->posx]->checkDmg(allies.id2type[sId]) == 1)  // find closest safe ndoe instead
    )
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) Taking cover! Moving to a better position than " << stepX << " " << stepY << std::endl;
        #endif
        int distToStep = Dist(allies.units[sId]->posx, allies.units[sId]->posy, stepX, stepY); // Distance to original target gridObj
        int cX = allies.units[sId]->posx, cY = allies.units[sId]->posy; // coordinates of the original target gridObj
        for (auto &&mod : allies.id2moveV[sId])
        {
            int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue; // out of bounds and traverse check
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;
            if 
            (
                map[newY][newX]->checkDmg(allies.id2type[sId]) == 1 &&                                          // try to find a safe gridObj
                Dist(newX, newY, allies.units[sId]->posx, allies.units[sId]->posy) <= allies.id2speed[sId] &&   // sanity test
                Dist(newX, newY, stepX, stepX) < distToStep                                                     // make sure the unit is not moving backwards
            )
            {
                distToStep = Dist(newX, newY, stepX, stepX);
                cX = newX;
                cY = newY;
            }
        }
        if (cX == allies.units[sId]->posx && cY == allies.units[sId]->posy) return false; // output no commands if safest node is the units current position
        else
        {
            stepX = cX; // otherwise, output coordinates
            stepY = cY;
        }
        return true;
    }
    else if (map[stepY][stepX]->checkDmg(allies.id2type[sId]) >= allies.units[sId]->endurance) // if unit would die next turn, repeat the above but allow to move backwards if needed
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) Taking cover! Avoiding imminent death on " << stepX << " " << stepY << std::endl;
        #endif
        int cX = allies.units[sId]->posx, cY = allies.units[sId]->posy;
        int dmg = map[cY][cX]->checkDmg(allies.id2type[sId]);
        for (auto &&mod : allies.id2moveV[sId])
        {
            int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
            if (newY < 0 || newY >= int(map.size())) continue;
            if (newX < 0 || newX >= int(map[newY].size())) continue;
            if (!map[newY][newX]->checkTrav()) continue;
            if 
            (
                Dist(newX, newY, allies.units[sId]->posx, allies.units[sId]->posy) <= allies.id2speed[sId] && // sanity check
                map[newY][newX]->checkDmg(allies.id2type[sId]) < dmg // pick grid with the lowest potential damage next turn
            )
            {
                dmg = map[newY][newX]->checkDmg(allies.id2type[sId]);
                cX = newX;
                cY = newY;
            }
        }
        if (cX == allies.units[sId]->posx && cY == allies.units[sId]->posy) return false; // output no commands if safest node is the units current position
        else
        {
            stepX = cX;
            stepY = cY;
            return true;
        }
    }
    return true;
}

bool action_base(std::string &payload, long gold, const listUnits &allies, const listUnits &enemies)
{
    std::stringstream ss;

    if (allies.base.queue == '0')
    {
        // Only in turn 1 can both players have exactly 1 unit simultaneously.
        bool firstTurn = (allies.qAll == 1 && enemies.qAll == 1);

        // Second queue, once the first turn choice is completed.
        bool secondQueue = (allies.qAll == 2 && allies.qArcher == 1 && resource::getUnusedResourceCount() > 0);

        // Pikemen are a cheap hard counter to knights.
        bool needPikemen = (allies.qPikeman < enemies.qKnight);

        // There should be at least 1 worker per each resource node.
        // But not more than swordsmen. Otherwise the base would only produce workers.
        // Additionally, there should never be no workers.
        bool noWorkers = (allies.qWorker == 0);
        bool needWorkers = (
            allies.qWorker <= allies.qSwordsman && \
            allies.qWorker < resource::getUnusedResourceCount()
        );

        // Knights are very good against archers and rams.
        // They are also marginally better against catapults than other units.
        bool needKnights = (
            allies.qKnight < enemies.qCatapult || \
            allies.qKnight < enemies.qRam || \
            allies.qKnight < enemies.qArcher
        );

        // If the enemy has no units, build rams.
        bool needRams = (enemies.qAll == 1);

        // If the enemy has many workers, build archers.
        bool needArchers = (allies.qArcher < enemies.qWorker);

        // First turn. Build an archer.
        if (firstTurn && CAN_GET_ARCHER(gold))
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build archer, because it is turn 1." << std::endl;
            #endif
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Once the archer is ready, build a worker
        else if (secondQueue && CAN_GET_WORKER(gold))
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build worker, because it is turn 2." << std::endl;
            #endif
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        //If you have no workers, build them immediately!
        else if (noWorkers && CAN_GET_WORKER(gold))
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build worker, because I have none." << std::endl;
            #endif
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (CAN_GET_CATAPULT(gold))
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build catapults, because I can." << std::endl;
            #endif
            ss << allies.base.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If 800 > gold >= 500 and enemy has no units left, build rams.
        else if (!CAN_GET_CATAPULT(gold) && CAN_GET_RAM(gold) && needRams)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build rams, because the enemy has no untis left and I can't afford a catapult." << std::endl;
            #endif
            ss << allies.base.id << " B R\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and enemy has many catapults/rams/archers,
        // build knights.
        else if (CAN_GET_KNIGHT(gold) && needKnights)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build knight, because the enemy has many catapults/rams/archers/workers." << std::endl;
            #endif
            ss << allies.base.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and enemy has many knights, build pikemen
        else if (CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build pikeman, because the enemy has many knights." << std::endl;
            #endif
            ss << allies.base.id << " B P\n";
            payload = ss.str();
            return true;
        }
        // If you have few workers (but not 0), built them now.
        else if (CAN_GET_WORKER(gold) && needWorkers)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build worker, because I need more gold." << std::endl;
            #endif
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If enemy has many workers, build archers.
        else if (CAN_GET_ARCHER(gold) && needArchers)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build archer, to kill enemy workers." << std::endl;
            #endif
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen.
        else if (CAN_GET_SWORDSMAN(gold))
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) (Base) I will build swordsman." << std::endl;
            #endif
            ss << allies.base.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

bool action_unit(std::string &payload, int unitId, const grid &map, listUnits &allies, listUnits &enemies)
{
    if (allies.units[unitId]->posy < 0 || allies.units[unitId]->posy >= int(map.size())) return false; // sanity test, ignore out of bound units (error in status file)
    if (allies.units[unitId]->posx < 0 || allies.units[unitId]->posx >= int(map[0].size())) return false;
    if (allies.units[unitId]->find_target(map, allies, enemies))
    {
        if (allies.units[unitId]->trgtY < 0 || allies.units[unitId]->trgtY >= int(map.size())) return false;
        if (allies.units[unitId]->trgtX < 0 || allies.units[unitId]->trgtX >= int(map[0].size())) return false;
        // Already on target, attack in place
        if
        (
            allies.units[unitId]->trgtX == allies.units[unitId]->posx &&
            allies.units[unitId]->trgtY == allies.units[unitId]->posy
        )
        return attack(payload, unitId, map, allies, enemies);
        // Target in range, move to it
        else if 
        (
            Dist
            (
                allies.units[unitId]->posx, allies.units[unitId]->posy,
                allies.units[unitId]->trgtX, allies.units[unitId]->trgtY
            ) == allies.id2speed[unitId]
        )
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) Moving full range" << std::endl;
            #endif
            std::stringstream ss;
            if (cover(unitId, map, allies, allies.units[unitId]->trgtX, allies.units[unitId]->trgtY))
            {
                ss << unitId << " M " << allies.units[unitId]->trgtX << ' ' << allies.units[unitId]->trgtY << '\n';
                payload = ss.str();
                if (allies.id2type[unitId] == 'W')
                {
                    map[allies.units[unitId]->trgtY][allies.units[unitId]->trgtX]->addWorkerId(unitId);
                    map[allies.units[unitId]->posy][allies.units[unitId]->posx]->removeWorkerId(unitId);
                }
                allies.units[unitId]->posx = allies.units[unitId]->trgtX;
                allies.units[unitId]->posy = allies.units[unitId]->trgtY;
                return true;
            }
            else return false;
        }
        // Target in range, move to it, attack
        else if 
        (
            Dist
            (
                allies.units[unitId]->posx, allies.units[unitId]->posy,
                allies.units[unitId]->trgtX, allies.units[unitId]->trgtY
            ) == allies.id2speed[unitId] - 1
        )
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) Moving to attack." << std::endl;
            #endif
            std::stringstream ss;
            ss << unitId << " M " << allies.units[unitId]->trgtX << ' ' << allies.units[unitId]->trgtY << '\n';
            payload = ss.str();
            if (allies.id2type[unitId] == 'W')
            {
                map[allies.units[unitId]->trgtY][allies.units[unitId]->trgtX]->addWorkerId(unitId);
                map[allies.units[unitId]->posy][allies.units[unitId]->posx]->removeWorkerId(unitId);
            }
            allies.units[unitId]->posx = allies.units[unitId]->trgtX;
            allies.units[unitId]->posy = allies.units[unitId]->trgtY;
            attack(payload, unitId, map, allies, enemies);
            return true;
        }
        // Target far away, determine shortest path and move
        // Use BFS algorithm
        else
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) Consulting BFS" << std::endl;
            #endif
            int stepX, stepY;
            if(!bfs_find_path(
                map,
                allies.units[unitId]->posx, allies.units[unitId]->posy,
                allies.units[unitId]->trgtX, allies.units[unitId]->trgtY,
                stepX, stepY, allies.id2moveV[unitId]
            )) return false;
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) BFS-directed move." << std::endl;
            #endif
            std::stringstream ss;
            if (cover(unitId, map, allies, stepX, stepY))
            {
                ss << unitId << " M " << stepX << ' ' << stepY << '\n';
                payload = ss.str();
                if (allies.id2type[unitId] == 'W')
                {
                    map[stepY][stepX]->addWorkerId(unitId);
                    map[allies.units[unitId]->posy][allies.units[unitId]->posx]->removeWorkerId(unitId);
                }
                allies.units[unitId]->posx = stepX;
                allies.units[unitId]->posy = stepY;
                return true;
            }
            else return false;
        }
    }
    // No valid targets, evade damage and wait
    else return evade(payload, unitId, map, allies);
}