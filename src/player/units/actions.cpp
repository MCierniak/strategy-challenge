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
    std::cout << "(Player) Choosing attack target" << std::endl;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> enemiesInRange;
    std::stringstream ss;
    for (auto &&mod : allies.id2attackV[sId])
    {
        int newY = allies.units[sId]->posy + mod[0], newX = allies.units[sId]->posx + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if (map[newY][newX]->checkEnemyNr() > 0)
        {
            for (int i = 0; i < map[newY][newX]->checkEnemyNr(); i++)
            {
                std::cout << "(Player) Found one!" << std::endl;
                int eid = map[newY][newX]->getEnemyId(i);
                int ehp;
                if (enemies.id2type[eid] == 'B') ehp = enemies.base.endurance;
                else ehp = enemies.units[eid]->endurance;
                if (ehp > 0)
                {
                    enemiesInRange.push(std::pair<int, int>(ehp, eid));
                }
                else std::cout << "(Player) Nevermind..." << std::endl;
            }
        }
    }
    if (!enemiesInRange.empty())
    {
        std::cout << "(Player) Target acquired." << std::endl;
        int trgt_id = enemiesInRange.top().second;
        ss << sId << " A " << trgt_id << '\n';
        payload += ss.str();

        if (enemies.id2type[trgt_id] == 'B') enemies.base.endurance -= allies.id2dmg[sId]['B'];
        else enemies.units[trgt_id]->endurance -= allies.id2dmg[sId][enemies.id2type[trgt_id]];

        std::cout << "(Player) Attacking!" << std::endl;
        return true;
    }
    std::cout << "(Player) Aborting attack" << std::endl;
    return false;
}

bool evade(std::string &payload, int sId, const grid &map, listUnits &allies)
{
    std::cout << "(Player) Engaging evasive maneuvers!" << std::endl;
    evade_queue eQueue;

    char type = allies.id2type[sId];
    int cX = allies.units[sId]->posx;
    int cY = allies.units[sId]->posy;
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

        // If target node out of range of any enemy, no point to iterate, just move to it
        if (dmg == 1)
        {
            std::ostringstream ss;
            ss << sId << " M " << newX << ' ' << newY << '\n';
            payload = ss.str();
            return true;
        }
    }
    if (!eQueue.empty())
    {
        std::ostringstream ss;
        coord next = eQueue.top().second;
        ss << sId << " M " << next.second << ' ' << next.first << '\n';
        payload = ss.str();
        return true;
    }
    else return false;
}

bool action_base(std::string &payload, long gold, const listUnits &allies, const listUnits &enemies)
{
    std::ostringstream ss;

    if (allies.base.queue == '0')
    {
        // Only in turn 1 can both players have exactly 1 unit simultaneously.
        bool firstTurn = (allies.qAll == 1 && enemies.qAll == 1);

        // Second queue, once the first turn choice is completed.
        bool secondQueue = (allies.qAll == 2 && allies.qArcher == 1);

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
            std::cout << "(Player) (Base) I will build archer, because it is turn 1." << std::endl;
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Once the archer is ready, build a worker
        else if (secondQueue && CAN_GET_WORKER(gold))
        {
            std::cout << "(Player) (Base) I will build worker, because it is turn 2." << std::endl;
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        //If you have no workers, build them immediately!
        else if (noWorkers && CAN_GET_WORKER(gold))
        {
            std::cout << "(Player) (Base) I will build worker, because I have none." << std::endl;
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (CAN_GET_CATAPULT(gold))
        {
            std::cout << "(Player) (Base) I will build catapults, because I can." << std::endl;
            ss << allies.base.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If 800 > gold >= 500 and enemy has no units left, build rams.
        else if (!CAN_GET_CATAPULT(gold) && CAN_GET_RAM(gold) && needRams)
        {
            std::cout << "(Player) (Base) I will build rams, because the enemy has no untis left and I can't afford a catapult." << std::endl;
            ss << allies.base.id << " B R\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and enemy has many catapults/rams/archers,
        // build knights.
        else if (CAN_GET_KNIGHT(gold) && needKnights)
        {
            std::cout << "(Player) (Base) I will build knight, because the enemy has many catapults/rams/archers/workers." << std::endl;
            ss << allies.base.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and enemy has many knights, build pikemen
        else if (CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            std::cout << "(Player) (Base) I will build pikeman, because the enemy has many knights." << std::endl;
            ss << allies.base.id << " B P\n";
            payload = ss.str();
            return true;
        }
        // If you have few workers (but not 0), built them now.
        else if (CAN_GET_WORKER(gold) && needWorkers)
        {
            std::cout << "(Player) (Base) I will build worker, because I need more gold." << std::endl;
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If enemy has many workers, build archers.
        else if (CAN_GET_ARCHER(gold) && needArchers)
        {
            std::cout << "(Player) (Base) I will build archer, to kill enemy workers." << std::endl;
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen.
        else if (CAN_GET_SWORDSMAN(gold))
        {
            std::cout << "(Player) (Base) I will build swordsman." << std::endl;
            ss << allies.base.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

bool action_unit(std::string &payload, int unitId, const grid &map, listUnits &allies, listUnits &enemies)
{
    if(allies.units[unitId]->find_target(map, allies, enemies))
    {
        // Already on target, attack in place
        if
        (
            allies.units[unitId]->trgtX == allies.units[unitId]->posx &&
            allies.units[unitId]->trgtY == allies.units[unitId]->posy
        ) return attack(payload, unitId, map, allies, enemies);
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
            std::cout << "(Player) Moving full range" << std::endl;
            std::ostringstream ss;
            ss << unitId << " M " << allies.units[unitId]->trgtX << ' ' << allies.units[unitId]->trgtY << '\n';
            payload = ss.str();
            return true;
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
            std::cout << "(Player) Moving to attack." << std::endl;
            std::ostringstream ss;
            ss << unitId << " M " << allies.units[unitId]->trgtX << ' ' << allies.units[unitId]->trgtY << '\n';
            payload = ss.str();
            attack(payload, unitId, map, allies, enemies);
            return true;
        }
        // Target far away, determine shortest path and move
        // Use BFS algorithm
        else
        {
            std::cout << "(Player) Consulting BFS" << std::endl;
            int stepX, stepY;
            if(!bfs_find_path(
                map,
                allies.units[unitId]->posx, allies.units[unitId]->posy,
                allies.units[unitId]->trgtX, allies.units[unitId]->trgtY,
                stepX, stepY, allies.id2moveV[unitId]
            )) return false;
            std::cout << "(Player) Moving full range" << std::endl;
            std::ostringstream ss;
            ss << unitId << " M " << stepX << ' ' << stepY << '\n';
            payload = ss.str();
            return true;
        }
    }
    // No valid targets, evade damage and wait
    else return evade(payload, unitId, map, allies);
}