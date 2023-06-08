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

bool find_target_worker(int sId, const grid &map, listUnits &allies)
{
    // If already on empty resource node, stay there
    // The third condition ensures that at most one worker will stay
    if (
        map[allies.units[sId]->posy][allies.units[sId]->posx]->checkResource() && 
        (
            map[allies.units[sId]->posy][allies.units[sId]->posx]->getWorkerId().size() == 1 || 
            map[allies.units[sId]->posy][allies.units[sId]->posx]->getWorkerId()[0] == allies.units[sId]->id
        )
    )
    {
        allies.units[sId]->trgtY = allies.units[sId]->posy;
        allies.units[sId]->trgtX = allies.units[sId]->posx;
        return true;
    }
    // If not, find nearest empty resource node
    for (auto &&el : resource::resNodeList)
    {
        if (map[el[0]][el[1]]->checkTrav() && map[el[0]][el[1]]->getWorkerId().size() == 0)
        {
            allies.units[sId]->trgtY = el[0];
            allies.units[sId]->trgtX = el[1];
            return true;
        }
    }
    // If none and unit already on resource node, stay there
    if (map[allies.units[sId]->posy][allies.units[sId]->posx]->checkResource())
    {
        allies.units[sId]->trgtY = allies.units[sId]->posy;
        allies.units[sId]->trgtX = allies.units[sId]->posx;
        return true;
    }
    // If not, find nearest resource node without enemies
    for (auto &&el : resource::resNodeList)
    {
        if (map[el[0]][el[1]]->checkTrav())
        {
            allies.units[sId]->trgtY = el[0];
            allies.units[sId]->trgtX = el[1];
            return true;
        }
    }
    // If all taken by the enemy, return false
    return false;
}

bool attack(std::string &payload, int sId, const grid &map, listUnits &allies, listUnits &enemies)
{
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
                int eid = map[newY][newX]->getEnemyId(i);
                int ehp = enemies.units[eid]->endurance;
                if (ehp > 0) enemiesInRange.push(std::pair<int, int>(ehp, eid));
            }
        }
    }
    if (!enemiesInRange.empty())
    {
        int trgt_id = enemiesInRange.top().second;
        ss << sId << " A " << trgt_id << '\n';
        payload += ss.str();

        enemies.units[trgt_id]->endurance -= allies.id2dmg[sId][enemies.id2type[trgt_id]];

        return true;
    }
    return false;
}

bool evade(std::string &payload, int sId, const grid &map, listUnits &allies)
{
    evade_queue eQueue;

    bool makeMove = false;
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
        bool secondQueue = (allies.qAll == 2 && allies.qWorker == 1);

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
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Once the archer is ready, build a worker
        else if (secondQueue && CAN_GET_WORKER(gold))
        {
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        //If you have no workers, build them immediately!
        else if (noWorkers && CAN_GET_WORKER(gold))
        {
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (CAN_GET_CATAPULT(gold))
        {
            ss << allies.base.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If 800 > gold >= 500 and enemy has no units left, build rams.
        else if (!CAN_GET_CATAPULT(gold) && CAN_GET_RAM(gold) && needRams)
        {
            ss << allies.base.id << " B R\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and enemy has many catapults/rams/archers,
        // build knights.
        else if (CAN_GET_KNIGHT(gold) && needKnights)
        {
            ss << allies.base.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and enemy has many knights, build pikemen
        else if (CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            ss << allies.base.id << " B P\n";
            payload = ss.str();
            return true;
        }
        // If you have few workers (but not 0), built them now.
        else if (CAN_GET_WORKER(gold) && needWorkers)
        {
            ss << allies.base.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If enemy has many workers, build archers.
        else if (CAN_GET_ARCHER(gold) && needArchers)
        {
            ss << allies.base.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen.
        else if (CAN_GET_SWORDSMAN(gold))
        {
            ss << allies.base.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

bool action_unit(std::string &payload, int unitId, const grid &map, listUnits &allies, listUnits &enemies)
{
    if(allies.units[unitId]->find_target(map))
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
            std::ostringstream ss;
            ss << unitId << " M " << allies.units[unitId]->trgtX << ' ' << allies.units[unitId]->trgtY << '\n';
            payload = ss.str();
            return attack(payload, unitId, map, allies, enemies);
        }
        // Target far away, determine shortest path and move
        // Use Dijkstra's algorithm
        else
        {
            int stepX, stepY;
            if(!dijkstra_find_path(
                unitId, allies, map,
                allies.units[unitId]->posx, allies.units[unitId]->posy,
                allies.units[unitId]->trgtX, allies.units[unitId]->trgtY,
                stepX, stepY
            )) return false;
            std::ostringstream ss;
            ss << unitId << " M " << stepX << ' ' << stepY << '\n';
            payload = ss.str();
            return true;
        }
    }
    // No valid targets, evade damage and wait
    else return evade(payload, unitId, map, allies);
}