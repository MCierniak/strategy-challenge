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
        // If something unexpected happens, terminate without feedback. Any error here means a faulty input.
        return false;
    }
}

bool get_status(const std::string &status_path, grid &map, long &gold, listUnits &myTeam, listUnits &enemy)
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
        std::stringstream ss(line);
        std::string eol_guard;

        ss >> alliegence >> type;

        // Add own base
        if (alliegence == 'P' && type == 'B')
        {
            ss >> id >> posx >> posy >> endurance >> bQueue;
            if (!ss) return false; // if not enought values to unpack, return
            ss >> eol_guard; // test if more inputs remain on line
            if (ss) return false;
            if (posy < 0 || posy >= int(map.size())) return false; // test if input makes sense
            if (posx < 0 || posx >= int(map[0].size())) return false;
            if(!(myTeam.addBase(id, endurance, posx, posy, bQueue))) return false; // add base
        }
        // Add enemy base
        else if (alliegence == 'E' && type == 'B')
        {
            ss >> id >> posx >> posy >> endurance >> bQueue;
            if (!ss) return false; // if not enought values to unpack, return
            ss >> eol_guard; // test if more inputs remain on line
            if (ss) return false;
            if (posy < 0 || posy >= int(map.size())) return false; // test if input makes sense
            if (posx < 0 || posx >= int(map[0].size())) return false;
            if(!(enemy.addBase(id, endurance, posx, posy, bQueue))) return false; // add base
            map[posy][posx]->addEnemyId(id); // register enemy on map
        }
        // Add other own units
        else if (alliegence == 'P' && type != 'B')
        {
            ss >> id >> posx >> posy >> endurance;
            if (!ss) return false; // if not enought values to unpack, return
            ss >> eol_guard; // test if more inputs remain on line
            if (ss) return false;
            if (posy < 0 || posy >= int(map.size())) return false; // test if input makes sense
            if (posx < 0 || posx >= int(map[0].size())) return false;
            if(!(myTeam.addUnit(type, id, endurance, posx, posy))) return false; // add unit
            if (type == 'W') map[posy][posx]->addWorkerId(id); // register worker on map
        }
        // Add other enemy units
        else if (alliegence == 'E' && type != 'B')
        {
            ss >> id >> posx >> posy >> endurance;
            if (!ss) return false; // if not enought values to unpack, return
            ss >> eol_guard; // test if more inputs remain on line
            if (ss) return false;
            if (posy < 0 || posy >= int(map.size())) return false; // test if input makes sense
            if (posx < 0 || posx >= int(map[0].size())) return false;
            if(!(enemy.addUnit(type, id, endurance, posx, posy))) return false; // add unit
            map[posy][posx]->addEnemyId(id); // register enemy on map
            for (auto &&mod : enemy.id2moveattackV[id]) // update damage flags on map, based on added enemy damage profile
            {
                int newY = posy + mod[0], newX = posx + mod[1];
                if (newY < 0 || newY >= int(map.size())) continue; // check if within bounds
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