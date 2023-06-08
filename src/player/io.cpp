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

#include "io.h"

bool get_map(const std::string &map_path, grid &map, int &X, int &Y)
{
    try{
        // Initialize grid object and set X and Y
        grid emptyMap;
        map = grid();
        X = 0;
        Y = 0;

        // Open file in read mode
        std::ifstream file(map_path);

        // Parse file
        std::string line;
        while(getline(file, line))
        {
            grid_row temp;
            for (std::size_t i = 0; i < line.length(); i++)
            {
                // Set empty spaces on tiles without barriers. Ignore bases.
                if (line[i] == '0' || line[i] == '1' || line[i] == '2')
                {
                    temp.push_back(std::make_unique<emptySpace>());
                }
                // Set resource nodes
                else if (line[i] == '6')
                {
                    temp.push_back(std::make_unique<resource>(i, Y));
                }
                // Set barriers
                else
                {
                    temp.push_back(std::make_unique<barrier>());
                }
            }
            map.push_back(std::move(temp));
            // Implicitly assume that the map file has equal length rows
            X = line.length();
            // Increment row count
            Y += 1;
        }
        file.close();
        return !(map == emptyMap);
    }
    catch (...)
    {
        return false;
    }
}

bool get_status(const std::string &status_path, grid &map, long &gold, listUnits &myTeam, listUnits &enemy)
{
    try
    {
        // Open file in read mode
        std::ifstream file(status_path);

        // If file does not exist, terminate
        if (file.fail()) return false;

        // Parse file, start with 1st line (gold)
        std::string line;
        getline(file, line);

        // If failed to parse first line, terminate
        if (line.length() == 0) return false;
        else gold = std::stol(line);

        // Parse rest of status (units)
        char alliegence, type, bQueue;
        int id, endurance, posx, posy;
        while(getline(file, line))
        {
            std::istringstream ss(line);
            std::string eol_guard;

            // Add own base
            if (line[0] == 'P' && line[2] == 'B')
            {
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> bQueue >> eol_guard;
                if (eol_guard.length() > 0) return false;
                if(!(myTeam.addBase(id, endurance, posx, posy, bQueue))) return false;
            }
            // Add enemy base
            else if (line[0] == 'E' && line[2] == 'B')
            {
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> bQueue >> eol_guard;
                if (eol_guard.length() > 0) return false;
                if(!(enemy.addBase(id, endurance, posx, posy, bQueue))) return false;
                map[posy][posx]->addEnemyId(id);
            }
            // Add other own units
            else if (line[0] == 'P' && line[2] != 'B')
            {
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() > 0) return false;
                if(!(myTeam.addUnit(type, id, endurance, posx, posy))) return false;
            }
            // Add other enemy units
            else if (line[0] == 'E' && line[2] != 'B')
            {
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() > 0) return false;
                if(!(enemy.addUnit(type, id, endurance, posx, posy))) return false;
                map[posy][posx]->addEnemyId(id);
                for (auto &&mod : enemy.id2moveattackV[id])
                {
                    int newY = posy + mod[0], newX = posx + mod[1];
                    if (newY < 0 || newY >= int(map.size())) continue;
                    if (newX < 0 || newX >= int(map[newY].size())) continue;

                    map[newY][newX]->addDmg('B', enemy.id2dmg[id]['B']);
                    map[newY][newX]->addDmg('W', enemy.id2dmg[id]['W']);
                    map[newY][newX]->addDmg('K', enemy.id2dmg[id]['K']);
                    map[newY][newX]->addDmg('S', enemy.id2dmg[id]['S']);
                    map[newY][newX]->addDmg('P', enemy.id2dmg[id]['P']);
                    map[newY][newX]->addDmg('C', enemy.id2dmg[id]['C']);
                    map[newY][newX]->addDmg('R', enemy.id2dmg[id]['R']);
                    map[newY][newX]->addDmg('A', enemy.id2dmg[id]['A']);
                }
            }
            // Error in alliegence tag, terminate
            else return false;
        }
        
        file.close();
        return true;
    }
    catch (...)
    {
        // If something unexpected happens, terminate
        return false;
    }
}

void test_get_map()
{
    // Test wrong input address.
    // Desired result is an empty grid object and false return.
    grid test;
    int X, Y;
    bool testReturn = get_map("wrong address", test, X, Y);
    if (!testReturn)
    {
        std::cout << "get_map() wrong address test passed (1/2)" << std::endl;
    }
    else
    {
        std::cout << "get_map() wrong address test failed! Return is not false (1/2)" << std::endl;
    }
    if (test == grid())
    {
        std::cout << "get_map() wrong address test passed (2/2)" << std::endl;
    }
    else
    {
        std::cout << "get_map() wrong address test failed! Grid is not empty (2/2)" << std::endl;
    }
}

void test_get_status()
{
    // Test wrong input address.
    // Desired result will have unmodified objects and false return.
    listUnits test1, test2;
    grid testMap;
    long testGold;
    bool testReturn = get_status("wrong address", testMap, testGold, test1, test2);
    if (!testReturn)
    {
        std::cout << "get_status() wrong address test passed (1/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Return is not false (1/4)" << std::endl;
    }
    if (testGold == long())
    {
        std::cout << "get_status() wrong address test passed (2/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Gold is not 0 (2/4) " << testGold << std::endl;
    }
    if (
        test1.qArcher == 0 && \
        test1.qCatapult == 0 && \
        test1.qKnight == 0 && \
        test1.qPikeman == 0 && \
        test1.qRam == 0 && \
        test1.qSwordsman == 0 &&
        test1.qWorker == 0
    )
    {
        std::cout << "get_status() wrong address test passed (3/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Player listUnits is not empty (3/4)" << std::endl;
    }
    if (
        test2.qArcher == 0 && \
        test2.qCatapult == 0 && \
        test2.qKnight == 0 && \
        test2.qPikeman == 0 && \
        test2.qRam == 0 && \
        test2.qSwordsman == 0 &&
        test2.qWorker == 0
    )
    {
        std::cout << "get_status() wrong address test passed (4/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Enemy listUnits is not empty (4/4)" << std::endl;
    }
}
