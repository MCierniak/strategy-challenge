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
                    temp.push_back(std::make_unique<emptySpace>(i, Y));
                }
                // Set resource nodes
                else if (line[i] == '6')
                {
                    temp.push_back(std::make_unique<resource>(i, Y));
                }
                // Set barriers
                else
                {
                    temp.push_back(std::make_unique<barrier>(i, Y));
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
        int id, endurance;
        std::size_t posx, posy;
        while(getline(file, line))
        {
            std::istringstream ss(line);

            // Determine type of unit first, alliegence last.
            switch (line[2])
            {
            case 'B': // Base unit, assume line has extra queue param
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> bQueue;
                if (alliegence == 'P')
                {
                    Base unit(id, endurance, posx, posy, bQueue);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Base unit(id, endurance, posx, posy, bQueue);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                }
                continue;
            case 'K': // Knight unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Knight unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Knight unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_5)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(KNIGHT2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(KNIGHT2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(KNIGHT2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(KNIGHT2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(KNIGHT2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(KNIGHT2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(KNIGHT2WORKER);
                    }
                    
                }
                continue;
            case 'S': // Swordsman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Swordsman unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Swordsman unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_2)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(SWORDSMAN2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(SWORDSMAN2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(SWORDSMAN2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(SWORDSMAN2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(SWORDSMAN2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(SWORDSMAN2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(SWORDSMAN2WORKER);
                    }
                }
                continue;
            case 'A': // Archer unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Archer unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Archer unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_6)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(ARCHER2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(ARCHER2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(ARCHER2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(ARCHER2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(ARCHER2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(ARCHER2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(ARCHER2WORKER);
                    }
                }
                continue;
            case 'P': // Pikeman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Pikeman unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Pikeman unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_3)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(PIKEMAN2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(PIKEMAN2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(PIKEMAN2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(PIKEMAN2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(PIKEMAN2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(PIKEMAN2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(PIKEMAN2WORKER);
                    }
                }
                continue;
            case 'C': // Catapult unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Catapult unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Catapult unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_8)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(CATAPULT2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(CATAPULT2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(CATAPULT2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(CATAPULT2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(CATAPULT2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(CATAPULT2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(CATAPULT2WORKER);
                    }
                }
                continue;
            case 'R': // Ram unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Ram unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                }
                else
                {
                    Ram unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_2)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(RAM2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(RAM2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(RAM2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(RAM2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(RAM2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(RAM2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(RAM2WORKER);
                    }
                }
                continue;
            case 'W': // Worker unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == 'P')
                {
                    Worker unit(id, endurance, posx, posy);
                    if(!(myTeam.addUnit(unit))) return false;
                    map[posy][posx]->addWorkerId(id);
                }
                else
                {
                    Worker unit(id, endurance, posx, posy);
                    if(!(enemy.addUnit(unit))) return false;
                    map[posy][posx]->addEnemyId(id);
                    for (auto &&mod : MOVE_2)
                    {
                        if (int(posy) + mod[0] < 0 || int(posy) + mod[0] >= int(map.size())) continue;
                        if (int(posx) + mod[1] < 0 || int(posx) + mod[1] >= int(map[posy + mod[0]].size())) continue;
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Archer(WORKER2ARCHER);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Catapult(WORKER2CATAPULT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Knight(WORKER2KNIGHT);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Pikeman(WORKER2PIKEMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Ram(WORKER2RAM);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Swordsman(WORKER2SWORDSMAN);
                        map[posy + mod[0]][posx + mod[1]]->addDmg2Worker(WORKER2WORKER);
                    }
                }
                continue;
            default: // Error in unit tag, terminate
                return false;
            }
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

void print_map(const grid &map, int X, int Y)
{
    std::cout << "Map:\n";
    std::cout << "Size: (" << X << ", " << Y << ")\n\n";
    std::cout << "Geography:" << "\n\n";
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            std::cout << map[i][j]->print() << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void print_status(const listUnits &myUnits, const listUnits &enemyUnits)
{
    std::cout << "My base:\n";
    std::cout << "ID: " << myUnits.bases[0].id << " HP: " << myUnits.bases[0].endurance << " POS: (" << myUnits.bases[0].posx << ", " << myUnits.bases[0].posy << ")\n";
    std::cout << "building: " << myUnits.bases[0].queue << "\n\n";
    if (myUnits.knights.size() > 0)
    {
        std::cout << "My knights:\n";
        for (auto &&unit : myUnits.knights)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.archers.size() > 0)
    {
        std::cout << "My archers\n";
        for (auto &&unit : myUnits.archers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.catapults.size() > 0)
    {
        std::cout << "My catapults\n";
        for (auto &&unit : myUnits.catapults)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.pikemen.size() > 0)
    {
        std::cout << "My pikemen\n";
        for (auto &&unit : myUnits.pikemen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.rams.size() > 0)
    {
        std::cout << "My rams\n";
        for (auto &&unit : myUnits.rams)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.swordsmen.size() > 0)
    {
        std::cout << "My swordsmen\n";
        for (auto &&unit : myUnits.swordsmen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (myUnits.workers.size() > 0)
    {
        std::cout << "My workers\n";
        for (auto &&unit : myUnits.workers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }

    std::cout << "Enemy base:\n";
    std::cout << "ID: " << enemyUnits.bases[0].id << " HP: " << enemyUnits.bases[0].endurance << " POS: (" << enemyUnits.bases[0].posx << ", " << enemyUnits.bases[0].posy << ")\n";
    std::cout << "building: " << enemyUnits.bases[0].queue << "\n\n";
    if (enemyUnits.knights.size() > 0)
    {
        std::cout << "Enemy knights:\n";
        for (auto &&unit : enemyUnits.knights)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.archers.size() > 0)
    {
        std::cout << "Enemy archers\n";
        for (auto &&unit : enemyUnits.archers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.catapults.size() > 0)
    {
        std::cout << "Enemy catapults\n";
        for (auto &&unit : enemyUnits.catapults)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.pikemen.size() > 0)
    {
        std::cout << "Enemy pikemen\n";
        for (auto &&unit : enemyUnits.pikemen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.rams.size() > 0)
    {
        std::cout << "Enemy rams\n";
        for (auto &&unit : enemyUnits.rams)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.swordsmen.size() > 0)
    {
        std::cout << "Enemy swordsmen\n";
        for (auto &&unit : enemyUnits.swordsmen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (enemyUnits.workers.size() > 0)
    {
        std::cout << "Enemy workers\n";
        for (auto &&unit : enemyUnits.workers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
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
        test1.archers.size() == 0 && \
        test1.catapults.size() == 0 && \
        test1.knights.size() == 0 && \
        test1.pikemen.size() == 0 && \
        test1.rams.size() == 0 && \
        test1.swordsmen.size() == 0 &&
        test1.workers.size() == 0
    )
    {
        std::cout << "get_status() wrong address test passed (3/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Player listUnits is not empty (3/4)" << std::endl;
    }
    if (
        test2.archers.size() == 0 && \
        test2.catapults.size() == 0 && \
        test2.knights.size() == 0 && \
        test2.pikemen.size() == 0 && \
        test2.rams.size() == 0 && \
        test2.swordsmen.size() == 0 &&
        test2.workers.size() == 0
    )
    {
        std::cout << "get_status() wrong address test passed (4/4)" << std::endl;
    }
    else
    {
        std::cout << "get_status() wrong address test failed! Enemy listUnits is not empty (4/4)" << std::endl;
    }
}
