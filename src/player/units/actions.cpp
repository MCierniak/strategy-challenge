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

bool worker_attack(std::string &payload, Worker &unit, const grid &map, listUnits &enemies)
{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> enemiesInRange;
    std::stringstream ss;
    for (auto &&mod : MOVE_1)
    {
        int newY = int(unit.posy) + mod[0], newX = int(unit.posx) + mod[1];
        if (newY < 0 || newY >= int(map.size())) continue;
        if (newX < 0 || newX >= int(map[newY].size())) continue;

        if (map[newY][newX]->checkEnemyNr() > 0)
        {
            for (std::size_t i = 0; i < map[newY][newX]->checkEnemyNr(); i++)
            {
                int eid = map[newY][newX]->getEnemyId(i);
                int ehp = enemies.id2hp[eid];
                if (ehp > 0) enemiesInRange.push(std::pair<int, int>(ehp, eid));
            }
        }
    }
    if (!enemiesInRange.empty())
    {
        int trgt_id = enemiesInRange.top().second;
        int trgt_ind = enemies.id2ind[trgt_id];
        ss << unit.id << " A " << trgt_id << '\n';
        payload += ss.str();

        switch (enemies.id2type[trgt_id])
        {
        case 'B':
            enemies.bases[trgt_ind].endurance -= WORKER2BASE;
            break;
        case 'K':
            enemies.knights[trgt_ind].endurance -= WORKER2KNIGHT;
            break;
        case 'S':
            enemies.swordsmen[trgt_ind].endurance -= WORKER2SWORDSMAN;
            break;
        case 'A':
            enemies.archers[trgt_ind].endurance -= WORKER2ARCHER;
            break;
        case 'P':
            enemies.pikemen[trgt_ind].endurance -= WORKER2PIKEMAN;
            break;
        case 'R':
            enemies.rams[trgt_ind].endurance -= WORKER2RAM;
            break;
        case 'C':
            enemies.catapults[trgt_ind].endurance -= WORKER2CATAPULT;
            break;
        case 'W':
            enemies.workers[trgt_ind].endurance -= WORKER2WORKER;
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

bool action(std::string &payload, const Base &unit, long gold, const listUnits &allies, const listUnits &enemies)
{
    std::ostringstream ss;

    if (unit.queue == '0')
    {
        // Only in turn 1 can both players have exactly 1 unit simultaneously.
        bool firstTurn = (allies.unitCount == 1 && enemies.unitCount == 1);

        // Second queue, once the first turn choice is completed.
        bool secondQueue = (allies.unitCount == 2 && allies.workers.size() == 1);

        // Pikemen are a cheap hard counter to knights.
        bool needPikemen = (allies.pikemen.size() < enemies.knights.size());

        // There should be at least 1 worker per each resource node.
        // But not more than swordsmen. Otherwise the base would only produce workers.
        // Additionally, there should never be no workers.
        bool noWorkers = (allies.workers.size() == 0);
        bool needWorkers = (
            allies.workers.size() <= allies.swordsmen.size() && \
            allies.workers.size() < resource::getUnusedResourceCount()
        );

        // Knights are very good against archers and rams.
        // They are also marginally better against catapults than other units.
        bool needKnights = (
            allies.knights.size() < enemies.catapults.size() || \
            allies.knights.size() < enemies.rams.size() || \
            allies.knights.size() < enemies.archers.size()
        );

        // If the enemy has no units, build rams.
        bool needRams = (enemies.unitCount == 1);

        // If the enemy has many workers, build archers.
        bool needArchers = (allies.archers.size() < enemies.workers.size());

        // First turn. Build an archer.
        if (firstTurn && CAN_GET_ARCHER(gold))
        {
            ss << unit.id << " B A\n";
            payload = ss.str();
            return true;
        }
        // Once the archer is ready, build a worker
        else if (secondQueue && CAN_GET_WORKER(gold))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        //If you have no workers, build them immediately!
        else if (noWorkers && CAN_GET_WORKER(gold))
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 800 build catapults.
        else if (CAN_GET_CATAPULT(gold))
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If 800 > gold >= 500 and enemy has no units left, build rams.
        else if (!CAN_GET_CATAPULT(gold) && CAN_GET_RAM(gold) && needRams)
        {
            ss << unit.id << " B C\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 400 and enemy has many catapults/rams/archers,
        // build knights.
        else if (CAN_GET_KNIGHT(gold) && needKnights)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If gold >= 200 and enemy has many knights, build pikemen
        else if (CAN_GET_PIKEMAN(gold) && needPikemen)
        {
            ss << unit.id << " B K\n";
            payload = ss.str();
            return true;
        }
        // If you have few workers (but not 0), built them now.
        else if (CAN_GET_WORKER(gold) && needWorkers)
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // If enemy has many workers, build archers.
        else if (CAN_GET_ARCHER(gold) && needArchers)
        {
            ss << unit.id << " B W\n";
            payload = ss.str();
            return true;
        }
        // Finally, if nothing else applies, build swordsmen.
        else if (CAN_GET_SWORDSMAN(gold))
        {
            ss << unit.id << " B S\n";
            payload = ss.str();
            return true;
        }
    }
    return false;
}

bool action(std::string &payload, Worker &unit, const grid &map, listUnits &enemies)
{
    if(unit.find_target(map))
    {
        // Worker already on resource node, don't move, attack in place
        if (unit.trgtX == unit.posx && unit.trgtY == unit.posy) return worker_attack(payload, unit, map, enemies);
        // Resource node in range, move to it
        else if (Dist(&unit, unit.trgtX, unit.trgtY) == 2)
        {
            std::ostringstream ss;
            ss << unit.id << " M " << unit.trgtX << ' ' << unit.trgtY << '\n';
            payload = ss.str();
            return true;
        }
        // Resource node in range, move to it, check for valid attack targets
        else if (Dist(&unit, unit.trgtX, unit.trgtY) == 1)
        {
            std::ostringstream ss;
            ss << unit.id << " M " << unit.trgtX << ' ' << unit.trgtY << '\n';
            unit.posx = unit.trgtX;
            unit.posy = unit.trgtY;
            payload = ss.str();
            worker_attack(payload, unit, map, enemies);
            return true;
        }
        // Resource node far away, determine shortest path and move
        // Use Dijkstra's algorithm
        else
        {
            int stepX, stepY;
            if(!dijkstra_find_path_worker(map, unit.posx, unit.posy, unit.trgtX, unit.trgtY, stepX, stepY, MOVE_2)) return false;
            std::ostringstream ss;
            ss << unit.id << " M " << stepX << ' ' << stepY << '\n';
            payload = ss.str();
            return true;
        }
    }
    else
    {
        // All resource nodes under enemy control, evade damage and wait
        std::list<std::size_t> move_x, move_y;

        move_x.push_front(unit.posx);
        move_y.push_front(unit.posy);
        int dmg = map[unit.posy][unit.posx]->checkDmgWorker();
        bool makeMove = false;

        // Not in range of enemies, do nothing
        if (dmg == 1) return false;

        for (auto &&mod : MOVE_1)
        {
            if (int(unit.posy) + mod[0] < 0 || int(unit.posy) + mod[0] >= int(map.size())) continue;
            if (int(unit.posx) + mod[1] < 0 || int(unit.posx) + mod[1] >= int(map[unit.posy + mod[0]].size())) continue;

            int moddmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();

            // If target node out of range of any enemy, no point to iterate, just move to it
            if (moddmg == 1)
            {
                std::ostringstream ss;
                ss << unit.id << " M " << unit.posx + mod[1] << ' ' << unit.posy + mod[0] << '\n';
                payload = ss.str();
                return true;
            }
            else
            {
                if (dmg > map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker())
                {
                    dmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
                    move_x.push_front(unit.posy + mod[0]);
                    move_y.push_front(unit.posx + mod[1]);
                    makeMove = true;
                }
            }
        }
        for (auto &&mod : MOVE_2)
        {
            if (int(unit.posy) + mod[0] < 0 || int(unit.posy) + mod[0] >= int(map.size())) continue;
            if (int(unit.posx) + mod[1] < 0 || int(unit.posx) + mod[1] >= int(map[unit.posy + mod[0]].size())) continue;
            int moddmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
            // If target node out of range of any enemy, no point to iterate, just move to it
            if (moddmg == 1)
            {
                std::ostringstream ss;
                ss << unit.id << " M " << unit.posx + mod[1] << ' ' << unit.posy + mod[0] << '\n';
                payload = ss.str();
                return true;
            }
            else
            {
                if (dmg > moddmg)
                {
                    dmg = map[unit.posy + mod[0]][unit.posx + mod[1]]->checkDmgWorker();
                    move_x.push_front(unit.posy + mod[0]);
                    move_y.push_front(unit.posx + mod[1]);
                    makeMove = true;
                }
            }
        }
        if (makeMove)
        {
            std::ostringstream ss;
            ss << unit.id << " M " << move_x.front() << ' ' << move_y.front() << '\n';
            payload = ss.str();
            return true;
        }
        else return false;
    }
}