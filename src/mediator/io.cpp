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
                    temp.push_back(
                        std::make_unique<emptySpace>()
                    );
                }
                // Set resource nodes
                else if (line[i] == '6')
                {
                    temp.push_back(
                        std::make_unique<resource>()
                    );
                }
                // Set barriers
                else
                {
                    temp.push_back(
                        std::make_unique<barrier>()
                    );
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

bool get_status(const std::string &status_path, int &max_index, grid &map_p1, grid &map_p2, long &gold_p1, long &gold_p2, listUnits &units_p1, listUnits &units_p2)
{
    try
    {
        // Open file in read mode
        std::ifstream file(status_path);
        if (file.fail())
        {
            std::cerr << "Can't open mediator.txt!" << std::endl;
            return false;
        }

        // Parse file, start with 1st line, indicating the last turn
        std::string line;
        getline(file, line);

        // Parse index guard. If failed to parse, terminate
        getline(file, line);
        if (line.length() == 0)
        {
            std::cerr << "Can't parse line 2 of mediator.txt!" << std::endl;
            return false;
        }
        else
        {
            max_index = std::stoi(line);
        }

        // Parse gold qty. If failed to parse, terminate
        getline(file, line);
        if (line.length() == 0)
        {
            std::cerr << "Can't parse line 3 of mediator.txt!" << std::endl;
            return false;
        }
        else
        {
            gold_p1 = std::stol(line);
        }
        getline(file, line);
        if (line.length() == 0)
        {
            std::cerr << "Can't parse line 4 of mediator.txt!" << std::endl;
            return false;
        }
        else
        {
            gold_p2 = std::stol(line);
        }

        // Parse rest of mediator.txt (units)
        std::string alliegence;
        char type, bQueue;
        int id, posx, posy, endurance;
        while(getline(file, line))
        {
            std::istringstream ss(line);
            std::string eol_guard;

            // Determine type of unit first, alliegence last.
            switch (line[3])
            {
            case 'B': // Base unit, assume line has extra queue param
                int bqTime;
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> bQueue >> bqTime >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Base unit(id, endurance, posx, posy, bQueue, bqTime);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Base unit(id, endurance, posx, posy, bQueue, bqTime);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'K': // Knight unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Knight unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Knight unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'S': // Swordsman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Swordsman unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Swordsman unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'A': // Archer unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Archer unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Archer unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'P': // Pikeman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Pikeman unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Pikeman unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'C': // Catapult unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Catapult unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Catapult unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'R': // Ram unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Ram unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Ram unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            case 'W': // Worker unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> eol_guard;
                if (eol_guard.length() != 0)
                {
                    std::cerr << "Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    Worker unit(id, endurance, posx, posy);
                    if(!(units_p1.addUnit(unit))) return false;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    Worker unit(id, endurance, posx, posy);
                    if(!(units_p2.addUnit(unit))) return false;
                }
                continue;
            default: // Error in unit tag, terminate
                std::cerr << "Error! Unrecognised unit tag!" << std::endl;
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

bool get_orders(const std::string &orders_path, grid &map, long &gold, listUnits &playerUnits, listUnits &opponentUnits, bool &playerWins, bool &opponentWins)
{
    try
    {
        // Open file in read mode
        std::ifstream file(orders_path);
        if (file.fail())
        {
            std::cerr << "Can't open rozkazy.txt!" << std::endl;
            return false;
        }

        // Parse orders
        std::string line;
        while(getline(file, line))
        {
            std::istringstream ss(line);
            int id;
            char action;
            ss >> id >> action;
            if (auto itType = playerUnits.id2type.find(id); itType != playerUnits.id2type.end())
            {
                switch (itType->second)
                {
                case 'B': // Base unit
                    getline(ss, line);
                    if(!process_base_orders(id, action, line, gold, playerUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'W': // Worker units
                    getline(ss, line);
                    if(!process_worker_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'K': // Knight units
                    getline(ss, line);
                    if(!process_knight_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'S': // Swordsman units
                    getline(ss, line);
                    if(!process_swordsman_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'A': // Archer units
                    getline(ss, line);
                    if(!process_archer_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'P': // Pikeman units
                    getline(ss, line);
                    if(!process_pikeman_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'C': // Catapult units
                    getline(ss, line);
                    if(!process_catapult_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                case 'R': // Ram units
                    getline(ss, line);
                    if(!process_ram_orders(id, action, line, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                    continue;
                // TODO: other orders go here
                default: // Error in unit tag, terminate
                    std::cerr << "Error in unit tags!" << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "Error in orders! Unit with id " << id << " does not exist!" << std::endl;
                playerWins = false;
                opponentWins = true;
                return true;
            }
        }
        return true;
    }
    catch(...)
    {
        // If something unexpected happens, terminate
        return false;
    }
}

bool start_game()
{
    try
    {
        std::cout << "Starting new game" << std::endl;
        // Random engine initialization for map generation
        std::random_device rd;
        std::mt19937 gen(rd());
        // Random int distribution for map size (min 2, max 100 rows/columns)
        // Random int distribution for map tile type
        std::uniform_int_distribution<> len(2, 100), type(0, 9);

        // Randomized map size
        int X = len(gen), Y = len(gen);

        // Generating map geography without bases
        std::vector<std::vector<char>> map(Y, std::vector<char>(X));
        for (int i = 0; i < Y; i++)
        {
            for (int j = 0; j < X; j++)
            {
                int gridPoint = type(gen);
                if (gridPoint <= EMPTY_CHANCE - 1)
                {
                    map[i][j] = '0';
                }
                else if (gridPoint > EMPTY_CHANCE - 1 && gridPoint <= EMPTY_CHANCE + RESOURCE_CHANCE - 1)
                {
                    map[i][j] = '6';
                }
                else
                {
                    map[i][j] = '9';
                }
            }
        }

        // Random int distribution for base location within map bounds
        std::uniform_int_distribution<> posx(0, X-1), posy(0, Y-1);

        // Generate position of base 1, make sure not to overwrite a barrier tile or base 2
        int trgt_x_1 = posx(gen), trgt_y_1 = posy(gen);
        while (map[trgt_y_1][trgt_x_1] == '9' || map[trgt_y_1][trgt_x_1] == '2')
        {
            trgt_x_1 = posx(gen);
            trgt_y_1 = posy(gen);
        }
        map[trgt_y_1][trgt_x_1] = '1';

        // Generate position of base 2, make sure not to overwrite a barrier tile or base 1
        int trgt_x_2 = posx(gen), trgt_y_2 = posy(gen);
        while (map[trgt_y_2][trgt_x_2] == '9' || map[trgt_y_2][trgt_x_2] == '1')
        {
            trgt_x_2 = posx(gen);
            trgt_y_2 = posy(gen);
        }
        map[trgt_y_2][trgt_x_2] = '2';

        // Output map to file
        std::ofstream file(MAP_LOC);
        if (file.fail())
        {
            std::cerr << "Can't open mapa.txt!" << std::endl;
            return false;
        }
        for (int i = 0; i < Y; i++)
        {
            for (int j = 0; j < X; j++)
            {
                file << map[i][j];
            }
            file << '\n';
        }
        file.close();

        // Set initial resource distribution
        long gold_1 = INITIAL_GOLD_1, gold_2 = INITIAL_GOLD_2;

        file.open(STATUS_P1_LOC);
        if (file.fail())
        {
            std::cerr << "Can't open status1.txt!" << std::endl;
            return false;
        }
        file << gold_1 << '\n';
        file << "P B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
        file << "E B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
        file.close();

        file.open(STATUS_P2_LOC);
        if (file.fail())
        {
            std::cerr << "Can't open status2.txt!" << std::endl;
            return false;
        }
        file << gold_2 << '\n';
        file << "E B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
        file << "P B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
        file.close();

        file.open(MEDIATOR_LOC);
        if (file.fail())
        {
            std::cerr << "Can't open mediator.txt!" << std::endl;
            return false;
        }
        file << 1 << '\n';
        file << 1 << '\n';
        file << gold_1 << '\n';
        file << gold_2 << '\n';
        file << "P1 B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0 0\n";
        file << "P2 B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0 0\n";
        file.close();
        return true;
    }
    catch(...)
    {
        // If something unexpected happens, terminate
        return false;
    }
}

bool prep_next_turn(int &turn, bool &player1Win, bool &player2Win)
{
    // Load raw map into memory. Ignore units.
    int X = 0, Y = 0;
    grid map_p1, map_p2;
    if (!get_map(MAP_LOC, map_p1, X, Y)) return false;
    if (!get_map(MAP_LOC, map_p2, X, Y)) return false;

    // Get game status prior to last turn
    long gold_p1 = 0, gold_p2 = 0;
    int max_index = 0;
    listUnits units_p1, units_p2;
    if (!get_status(MEDIATOR_LOC, max_index, map_p1, map_p2, gold_p1, gold_p2, units_p1, units_p2)) return false;
    
    // Parse player orders, incr gold, decr building time, add completed units, remove killed units
    if (turn % 2 == 1)
    {
        // Parse orders
        if (!get_orders(ORDERS_P1_LOC, map_p1, gold_p1, units_p1, units_p2, player1Win, player2Win)) return false;
        // Incr gold
        for (auto &&work : units_p1.workers) if (map_p1[work.posy][work.posx]->checkResource()) gold_p1 += 50;
        // Decr queue
        if (units_p1.bases[0].queue != '0') units_p1.bases[0].qTime -= 1;
        // If build complete, insert new unit
        if(!add_new_unit(max_index, units_p1)) return false;
        // If any enemy unit has hp <= 0, remove it. Check if enemy base is dead.
        if (!remove_dead_units(units_p2, player1Win, player2Win)) return false;
    }
    else
    {
        // Parse orders
        if (!get_orders(ORDERS_P2_LOC, map_p2, gold_p2, units_p2, units_p1, player2Win, player1Win)) return false;
        // Incr gold
        for (auto &&work : units_p2.workers) if (map_p2[work.posy][work.posx]->checkResource()) gold_p2 += 50;
        // Decr queue
        if (units_p2.bases[0].queue != '0') units_p2.bases[0].qTime -= 1;
        // If build complete, insert new unit
        if(!add_new_unit(max_index, units_p2)) return false;
        // If any enemy unit has hp <= 0, remove it. Check if enemy base is dead.
        if (!remove_dead_units(units_p1, player2Win, player1Win)) return false;
    }

    // Update mediator.txt, prep new statusX.txt file.
    std::ofstream file(STATUS_P1_LOC);
    if (file.fail())
    {
        std::cerr << "Can't open status1.txt!" << std::endl;
        return false;
    }
    file << gold_p1 << '\n';
    file << unit_output_player("P", units_p1);
    file << unit_output_player("E", units_p2);
    file.close();

    file.open(STATUS_P2_LOC);
    if (file.fail())
    {
        std::cerr << "Can't open status2.txt!" << std::endl;
        return false;
    }
    file << gold_p2 << '\n';
    file << unit_output_player("P", units_p2);
    file << unit_output_player("E", units_p1);
    file.close();

    file.open(MEDIATOR_LOC);
    if (file.fail())
    {
        std::cerr << "Can't open mediator.txt!" << std::endl;
        return false;
    }
    file << turn << '\n';
    file << max_index << '\n';
    file << gold_p1 << '\n';
    file << gold_p2 << '\n';
    file << unit_output_mediator("P1", units_p1);
    file << unit_output_mediator("P2", units_p2);
    file.close();

    write_hr_map_status(map_p1, units_p1, units_p2);

    return true;
}

bool process_base_orders(int id, char task, const std::string &order, long &gold, listUnits &units, bool &playerWins, bool &opponentWins)
{
    // Check if order is "build"
    if (task != 'B')
    {
        std::cout << "Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
    // Order format check
    if (order.length() > 2)
    {
        std::cout << "Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
    else
    {
        // Does the order contain valid targets
        std::vector<char> check_order = {'K', 'S', 'A', 'P', 'R', 'C', 'W'};
        if(std::find(check_order.begin(), check_order.end(), order[1]) == check_order.end())
        {
            std::cout << "Error in orders! Unit with id " << id << " received invalid target!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        std::cout << "Unit with id " << id << " (B) received order to build " << order[1] << "." << std::endl;
        auto itInd = units.id2index.find(id);

        // Does the unit have an empty build queue
        if(units.bases[itInd->second].queue != '0')
        {
            std::cout << "Error in orders! Unit with id " << id << " is already building!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        units.bases[itInd->second].queue = order[1];
        units.bases[itInd->second].qTime = BUILD_TIME(order[1]);

        // Does the player have enough gold
        gold -= BUILD_COST(order[1]);
        if (gold < 0)
        {
            std::cout << "Error in orders! Unit with id " << id << " cannot begin construction! Insufficient funds!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
    }
    return true;
}

bool process_worker_orders(int id, char task, const std::string &order, const grid &map, listUnits &units, listUnits &enemies, bool &playerWins, bool &opponentWins)
{
    // move action
    if (task == 'M')
    {
        std::stringstream parser(order);
        std::string eol_guard;
        int tX, tY;
        parser >> tX >> tY >> eol_guard;
        if (eol_guard.length() > 0)
        {
            std::cout << "Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        int sX = units.workers[units.id2index[id]].posx, sY = units.workers[units.id2index[id]].posy;
        if (tX >= int(map[0].size()) || tX < 0 || tY >= int(map.size()) || tY < 0)
        {
            std::cout << "Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        std::cout << "Unit with id " << id << " (W) received order to move from " << sX << " " << sY << " to " << tX << " " << tY << std::endl;
        if (Dist(&units.workers[units.id2index[id]], tX, tY) > 2)
        {
            std::cout << "Error in orders! Unit with id " << id << " cannot move that far!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        else if (!map[tY][tX]->checkTrav())
        {
            std::cout << "Error in orders! Unit with id " << id << " attempts an illegal move!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        else
        {
            units.workers[units.id2index[id]].posx = tX;
            units.workers[units.id2index[id]].posy = tY;
            return true;
        }
    }
    // attack action
    else if (task == 'A') 
    {
        std::cout << "Unit with id " << id << " (W) received order to attack!" << std::endl;
        // TODO
        return true;
    }
    else
    {
        std::cout << "Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
}

bool remove_dead_units(listUnits &units, bool &playerWins, bool &opponentWins)
{
    if (units.bases[0].endurance <= 0)
    {
        playerWins = true;
        opponentWins = false;
        return true;
    }
    std::remove_if(units.archers.begin(), units.archers.end(), [](const Archer &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.catapults.begin(), units.catapults.end(), [](const Catapult &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.knights.begin(), units.knights.end(), [](const Knight &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.pikemen.begin(), units.pikemen.end(), [](const Pikeman &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.rams.begin(), units.rams.end(), [](const Ram &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.swordsmen.begin(), units.swordsmen.end(), [](const Swordsman &unit)
        {
            return unit.endurance <= 0;
        }
    );
    std::remove_if(units.workers.begin(), units.workers.end(), [](const Worker &unit)
        {
            return unit.endurance <= 0;
        }
    );
    return true;
}

bool add_new_unit(int &max_index, listUnits &units)
{
    if (units.bases[0].queue != '0' && units.bases[0].qTime == 0)
    {
        max_index++;
        switch (units.bases[0].queue)
        {
        case 'K':
        {
            Knight unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'S':
        {
            Swordsman unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'A':
        {
            Archer unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'P':
        {
            Pikeman unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'R':
        {
            Ram unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'C':
        {
            Catapult unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        case 'W':
        {
            Worker unit(max_index, units.bases[0].posx, units.bases[0].posy);
            units.addUnit(unit);
            units.bases[0].queue = '0';
            break;
        }
        default:
            std::cerr << "Error in base queue!" << std::endl;
            return false;
        }
    }
    return true;
}

std::string unit_output_player(const std::string &name, const listUnits &units)
{
    std::stringstream ss;
    for (auto &&unit : units.bases)
    {
        ss << name << " B " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << " " << unit.queue << '\n';
    }
    for (auto &&unit : units.archers)
    {
        ss << name << " A " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.catapults)
    {
        ss << name << " C " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.knights)
    {
        ss << name << " K " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.pikemen)
    {
        ss << name << " P " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.rams)
    {
        ss << name << " R " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.swordsmen)
    {
        ss << name << " S " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.workers)
    {
        ss << name << " W " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    return ss.str();
}

std::string unit_output_mediator(const std::string &name, const listUnits &units)
{
    std::stringstream ss;
    for (auto &&unit : units.bases)
    {
        ss << name << " B " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << " " << unit.queue << " " << unit.qTime << '\n';
    }
    for (auto &&unit : units.archers)
    {
        ss << name << " A " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.catapults)
    {
        ss << name << " C " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.knights)
    {
        ss << name << " K " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.pikemen)
    {
        ss << name << " P " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.rams)
    {
        ss << name << " R " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.swordsmen)
    {
        ss << name << " S " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    for (auto &&unit : units.workers)
    {
        ss << name << " W " << unit.id << " " << unit.posx << " " << unit.posy << " " << unit.endurance << '\n';
    }
    return ss.str();
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

void print_status(const listUnits &units_p1, const listUnits &units_p2)
{
    std::cout << "Player 1 base:\n";
    std::cout << "ID: " << units_p1.bases[0].id << " HP: " << units_p1.bases[0].endurance << " POS: (" << units_p1.bases[0].posx << ", " << units_p1.bases[0].posy << ")\n";
    std::cout << "building: " << units_p1.bases[0].queue << "\n\n";
    if (units_p1.knights.size() > 0)
    {
        std::cout << "Player 1 knights:\n";
        for (auto &&unit : units_p1.knights)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.archers.size() > 0)
    {
        std::cout << "Player 1 archers\n";
        for (auto &&unit : units_p1.archers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.catapults.size() > 0)
    {
        std::cout << "Player 1 catapults\n";
        for (auto &&unit : units_p1.catapults)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.pikemen.size() > 0)
    {
        std::cout << "Player 1 pikemen\n";
        for (auto &&unit : units_p1.pikemen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.rams.size() > 0)
    {
        std::cout << "Player 1 rams\n";
        for (auto &&unit : units_p1.rams)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.swordsmen.size() > 0)
    {
        std::cout << "Player 1 swordsmen\n";
        for (auto &&unit : units_p1.swordsmen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p1.workers.size() > 0)
    {
        std::cout << "Player 1 workers\n";
        for (auto &&unit : units_p1.workers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }

    std::cout << "Player 2 base:\n";
    std::cout << "ID: " << units_p2.bases[0].id << " HP: " << units_p2.bases[0].endurance << " POS: (" << units_p2.bases[0].posx << ", " << units_p2.bases[0].posy << ")\n";
    std::cout << "building: " << units_p2.bases[0].queue << "\n\n";
    if (units_p2.knights.size() > 0)
    {
        std::cout << "Player 2 knights:\n";
        for (auto &&unit : units_p2.knights)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.archers.size() > 0)
    {
        std::cout << "Player 2 archers\n";
        for (auto &&unit : units_p2.archers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.catapults.size() > 0)
    {
        std::cout << "Player 2 catapults\n";
        for (auto &&unit : units_p2.catapults)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.pikemen.size() > 0)
    {
        std::cout << "Player 2 pikemen\n";
        for (auto &&unit : units_p2.pikemen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.rams.size() > 0)
    {
        std::cout << "Player 2 rams\n";
        for (auto &&unit : units_p2.rams)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.swordsmen.size() > 0)
    {
        std::cout << "Player 2 swordsmen\n";
        for (auto &&unit : units_p2.swordsmen)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
    if (units_p2.workers.size() > 0)
    {
        std::cout << "Player 2 workers\n";
        for (auto &&unit : units_p2.workers)
        {
            std::cout << "ID: " << unit.id << " HP: " << unit.endurance << " POS: (" << unit.posx << ", " << unit.posy << ")\n";
        }
    }
}

void write_hr_map_status(const grid &map, const listUnits &units_p1, const listUnits &units_p2)
{
    std::ofstream file("data/mapaHR.txt");
    for (int i = 0; i < int(map.size()); i++)
    {
        for (int j = 0; j < int(map[0].size()); j++)
        {
            file << "(" << j << "," << i << "," << map[i][j]->print();
            for (auto &&unit : units_p1.archers)
            {
                if (unit.posx == j && unit.posy == i) file << ",A1";
            }
            for (auto &&unit : units_p1.bases)
            {
                if (unit.posx == j && unit.posy == i) file << ",B1";
            }
            for (auto &&unit : units_p1.catapults)
            {
                if (unit.posx == j && unit.posy == i) file << ",C1";
            }
            for (auto &&unit : units_p1.knights)
            {
                if (unit.posx == j && unit.posy == i) file << ",K1";
            }
            for (auto &&unit : units_p1.pikemen)
            {
                if (unit.posx == j && unit.posy == i) file << ",P1";
            }
            for (auto &&unit : units_p1.rams)
            {
                if (unit.posx == j && unit.posy == i) file << ",R1";
            }
            for (auto &&unit : units_p1.swordsmen)
            {
                if (unit.posx == j && unit.posy == i) file << ",S1";
            }
            for (auto &&unit : units_p1.workers)
            {
                if (unit.posx == j && unit.posy == i) file << ",W1";
            }
            for (auto &&unit : units_p2.archers)
            {
                if (unit.posx == j && unit.posy == i) file << ",A2";
            }
            for (auto &&unit : units_p2.bases)
            {
                if (unit.posx == j && unit.posy == i) file << ",B2";
            }
            for (auto &&unit : units_p2.catapults)
            {
                if (unit.posx == j && unit.posy == i) file << ",C2";
            }
            for (auto &&unit : units_p2.knights)
            {
                if (unit.posx == j && unit.posy == i) file << ",K2";
            }
            for (auto &&unit : units_p2.pikemen)
            {
                if (unit.posx == j && unit.posy == i) file << ",P2";
            }
            for (auto &&unit : units_p2.rams)
            {
                if (unit.posx == j && unit.posy == i) file << ",R2";
            }
            for (auto &&unit : units_p2.swordsmen)
            {
                if (unit.posx == j && unit.posy == i) file << ",S2";
            }
            for (auto &&unit : units_p2.workers)
            {
                if (unit.posx == j && unit.posy == i) file << ",W2";
            }
            file << ") ";
        }
        file << '\n';
    }
    file << '\n';
    file.close();
}

bool file_exists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}