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
            std::cerr << "(Mediator) Can't open mediator.txt!" << std::endl;
            return false;
        }

        // Parse file, start with 1st line, indicating the last turn
        std::string line;
        getline(file, line);

        // Parse index guard. If failed to parse, terminate
        getline(file, line);
        if (line.length() == 0)
        {
            std::cerr << "(Mediator) Can't parse line 2 of mediator.txt!" << std::endl;
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
            std::cerr << "(Mediator) Can't parse line 3 of mediator.txt!" << std::endl;
            return false;
        }
        else
        {
            gold_p1 = std::stol(line);
        }
        getline(file, line);
        if (line.length() == 0)
        {
            std::cerr << "(Mediator) Can't parse line 4 of mediator.txt!" << std::endl;
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
            std::stringstream ss(line);
            std::string eol_guard;

            ss >> alliegence >> type;
            if (!ss) // if not enought values to unpack, return
            {
                std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                return false;
            }

            // Determine type of unit first, alliegence last.
            switch (type)
            {
            case 'B': // Base unit, assume line has extra queue param
                int bqTime;
                ss >> id >> posx >> posy >> endurance >> bQueue >> bqTime;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addBase(id, endurance, posx, posy, bQueue, bqTime))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addBase(id, endurance, posx, posy, bQueue, bqTime))) return false;
                }
                continue;
            case 'K': // Knight unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addKnight(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addKnight(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'S': // Swordsman unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addSwordsman(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addSwordsman(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'A': // Archer unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addArcher(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addArcher(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'P': // Pikeman unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addPikeman(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addPikeman(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'C': // Catapult unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addCatapult(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addCatapult(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'R': // Ram unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addRam(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addRam(id, endurance, posx, posy))) return false;
                }
                continue;
            case 'W': // Worker unit
                ss >> id >> posx >> posy >> endurance;
                if (!ss) // if not enought values to unpack, return
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                ss >> eol_guard; // test if more inputs remain on line
                if (ss)
                {
                    std::cerr << "(Mediator) Error in parsing status data!" << std::endl;
                    return false;
                }
                if (alliegence == "P1")
                {
                    // If unit belongs to p1, add to p1 unitlists and set p2 map flags
                    map_p2[posy][posx]->setTrav(false);
                    if(!(units_p1.addWorker(id, endurance, posx, posy))) return false;
                }
                else
                {
                    // ... and vice versa
                    map_p1[posy][posx]->setTrav(false);
                    if(!(units_p2.addWorker(id, endurance, posx, posy))) return false;
                }
                continue;
            default: // Error in unit tag, terminate
                std::cerr << "(Mediator) Error! Unrecognised unit tag!" << std::endl;
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
    // Open file in read mode
    std::ifstream file(orders_path);
    if (file.fail())
    {
        std::cerr << "(Mediator) Can't open order file!" << std::endl;
        return false;
    }

    // Parse orders
    std::string line;
    while(getline(file, line))
    {
        std::stringstream ss(line);
        int id;
        char action;
        ss >> id >> action;
        if(!ss) // if not enought values to unpack, disqualify player
        {
            std::cout << "(Mediator) Error in orders! Incomplete order!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return true;
        }
        if (!playerUnits.is_unique(id))
        {
            // Interpret orders
            if (playerUnits.id2type[id] == 'B')
            {
                if(!process_base_orders(id, action, ss, gold, playerUnits, playerWins, opponentWins)) return true;
            }
            else
            {
                if(!process_unit_orders(id, action, ss, map, playerUnits, opponentUnits, playerWins, opponentWins)) return true;
                continue;
            }
        }
        else // if error in orders, disqualify player
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " does not exist!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return true;
        }
    }
    file.close();
    return true;
}

bool start_game()
{
    try
    {
        std::cout << "(Mediator) Starting new game" << std::endl;
        // Random engine initialization for map generation
        std::random_device rd;
        std::mt19937 gen(rd());
        // Random int distribution for map size (min 2, max 100 rows/columns)
        // Random int distribution for map tile type
        std::uniform_int_distribution<> len(GRID_MIN, GRID_MAX), type(0, 9);

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
            std::cerr << "(Mediator) Can't open mapa.txt!" << std::endl;
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

        // Output status files
        file.open(STATUS_P1_LOC);
        if (file.fail())
        {
            std::cerr << "(Mediator) Can't open status1.txt!" << std::endl;
            return false;
        }
        file << gold_1 << '\n';
        file << "P B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
        file << "E B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
        file.close();

        file.open(STATUS_P2_LOC);
        if (file.fail())
        {
            std::cerr << "(Mediator) Can't open status2.txt!" << std::endl;
            return false;
        }
        file << gold_2 << '\n';
        file << "E B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
        file << "P B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
        file.close();

        file.open(MEDIATOR_LOC);
        if (file.fail())
        {
            std::cerr << "(Mediator) Can't open mediator.txt!" << std::endl;
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

bool prep_next_turn(int &turn, bool &player1Win, bool &player2Win, bool &draw)
{
    // Load raw map into memory. Ignore units. Separate maps for each player to specify respective traversal flags.
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
        if (player1Win || player2Win) return true;
        // Incr gold
        for (auto const& [id, unit] : units_p1.units)
        {
            if (units_p1.id2type[id] == 'W' && map_p1[units_p1.units[id]->posy][units_p1.units[id]->posx]->checkResource())
            {
                std::cout << "(Mediator) Unit with id " << id << " (worker) mined gold at " <<  unit->posx << " " << unit->posy << " for Player 1\n";
                gold_p1 += 50;
            }
        }
        // Decr queue
        if (units_p1.base.queue != '0') units_p1.base.qTime -= 1;
        // If build complete, insert new unit
        if(!add_new_unit(max_index, units_p1)) return false;
        // If any enemy unit has hp <= 0, remove it. Check if enemy base is dead.
        if (!remove_dead_units(units_p2, player1Win, player2Win)) return false;
        if (player1Win || player2Win) return true;
    }
    else
    {
        // Parse orders
        if (!get_orders(ORDERS_P2_LOC, map_p2, gold_p2, units_p2, units_p1, player2Win, player1Win)) return false;
        if (player1Win || player2Win) return true;
        // Incr gold
        for (auto const& [id, unit] : units_p2.units)
        {
            if (units_p2.id2type[id] == 'W' && map_p2[units_p2.units[id]->posy][units_p2.units[id]->posx]->checkResource())
            {
                std::cout << "(Mediator) Unit with id " << id << " (worker) mined gold at " <<  unit->posx << " " << unit->posy << " for Player 2\n";
                gold_p2 += 50;
            }
        }
        // Decr queue
        if (units_p2.base.queue != '0') units_p2.base.qTime -= 1;
        // If build complete, insert new unit
        if(!add_new_unit(max_index, units_p2)) return false;
        // If any enemy unit has hp <= 0, remove it. Check if enemy base is dead.
        if (!remove_dead_units(units_p1, player2Win, player1Win)) return false;
        if (player1Win || player2Win) return true;
    }

    if (turn > 2000) // If turn limit is exceeded, declare winner or draw
    {
        draw = units_p1.qAll == units_p2.qAll;
        player1Win = units_p1.qAll > units_p2.qAll;
        player2Win = units_p1.qAll < units_p2.qAll;
        return true;
    }

    // Update mediator.txt, prep new statusX.txt file.
    std::ofstream file(STATUS_P1_LOC);
    if (file.fail())
    {
        std::cerr << "(Mediator) Can't open status1.txt!" << std::endl;
        return false;
    }
    file << gold_p1 << '\n';
    file << unit_output_player("P", units_p1);
    file << unit_output_player("E", units_p2);
    file.close();

    file.open(STATUS_P2_LOC);
    if (file.fail())
    {
        std::cerr << "(Mediator) Can't open status2.txt!" << std::endl;
        return false;
    }
    file << gold_p2 << '\n';
    file << unit_output_player("P", units_p2);
    file << unit_output_player("E", units_p1);
    file.close();

    file.open(MEDIATOR_LOC);
    if (file.fail())
    {
        std::cerr << "(Mediator) Can't open mediator.txt!" << std::endl;
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

bool process_base_orders(int id, char task, std::stringstream &order, long &gold, listUnits &units, bool &playerWins, bool &opponentWins)
{
    // Check if order is "build"
    std::string eol_guard;
    char target;
    order >> target;
    if (!order) // Check if order has valid format
    {
        std::cout << "(Mediator) Error in orders! Incomplete order!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
    order >> eol_guard;
    if(order)
    {
        std::cout << "(Mediator) Error in orders! Invalid format!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
    if (task != 'B')
    {
        std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
    else
    {
        // Is the target valid
        std::vector<char> check_order = {'K', 'S', 'A', 'P', 'R', 'C', 'W'};
        if(std::find(check_order.begin(), check_order.end(), target) == check_order.end())
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid target!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        std::cout << "(Mediator) Unit with id " << id << " (base) received order to build " << target << "." << std::endl;

        // Does the unit have an empty build queue
        if(units.base.queue != '0')
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " is already building!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        // If all tests passed, update base build status
        units.base.queue = target;
        units.base.qTime = BUILD_TIME(target);

        // Does the player have enough gold
        gold -= BUILD_COST(target);
        if (gold < 0)
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " cannot begin construction! Insufficient funds! " << gold << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
    }
    return true;
}

bool process_unit_orders(int id, char task, std::stringstream &order, const grid &map, listUnits &units, listUnits &enemies, bool &playerWins, bool &opponentWins)
{
    // Move action
    if (task == 'M')
    {
        int tX, tY;
        std::string eol_guard;
        order >> tX >> tY;
        if (!order) // Check if order has valid format
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        order >> eol_guard;
        if (order)
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        // Check if order does not exceed map bounds
        if (tX >= int(map[0].size()) || tX < 0 || tY >= int(map.size()) || tY < 0)
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        // Check if order does not direct to a barrier node
        if (!map[tY][tX]->checkTrav())
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " attempts an illegal move!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        std::cout << "(Mediator) Unit with id " << id << " (" << units.id2typeName[id];
        std::cout << ") received order to move from " << units.units[id]->posx << " " << units.units[id]->posy;
        std::cout << " to " << tX << " " << tY << " (distance ";
        std::cout << Dist(units.units[id]->posx, units.units[id]->posy, tX, tY) << ")" << std::endl;

        // Check if order is possible within the units speed limit
        if (Dist(units.units[id]->posx, units.units[id]->posy, tX, tY) > units.id2speed[id])
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " cannot move that far!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        // Update unit status
        units.units[id]->posx = tX;
        units.units[id]->posy = tY;

        return true;
    }
    // Attack action
    else if (task == 'A')
    {
        int tId;
        std::string eol_guard;
        order >> tId;
        if (!order) // Check if order has valid format
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
        order >> eol_guard;
        if (order)
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }

        std::cout << "(Mediator) Unit with id " << id << " (" << units.id2typeName[id];
        std::cout << ") received order to attack unit with id " << tId;
        std::cout << " (" << enemies.id2typeName[tId] << ", distance ";
        if (enemies.id2type[tId] == 'B') std::cout << Dist(units.units[id]->posx, units.units[id]->posy, enemies.base.posx, enemies.base.posy) <<")" << std::endl;
        else std::cout << Dist(units.units[id]->posx, units.units[id]->posy, enemies.units[tId]->posx, enemies.units[tId]->posy) <<")" << std::endl;

        bool condition;
        if (enemies.id2type[tId] == 'B') // Seg Fault guard
        {
            condition = Dist
            (
                units.units[id]->posx, units.units[id]->posy,
                enemies.base.posx, enemies.base.posy
            ) <= units.id2arange[id];
        }
        else
        {
            condition = Dist
            (
                units.units[id]->posx, units.units[id]->posy,
                enemies.units[tId]->posx, enemies.units[tId]->posy
            ) <= units.id2arange[id];
        }
        if(condition) // Check if target within attack range, update endurance if yes
        {
            if (enemies.id2type[tId] == 'B') enemies.base.endurance -= units.id2dmg[id]['B'];
            else enemies.units[tId]->endurance -= units.id2dmg[id][enemies.id2type[tId]];
            return true;
        }
        else
        {
            std::cout << "(Mediator) Error in orders! Unit with id " << id << " cannot attack that far!" << std::endl;
            playerWins = false;
            opponentWins = true;
            return false;
        }
    }
    else
    {
        std::cout << "(Mediator) Error in orders! Unit with id " << id << " received invalid command!" << std::endl;
        playerWins = false;
        opponentWins = true;
        return false;
    }
}

bool remove_dead_units(listUnits &units, bool &playerWins, bool &opponentWins)
{
    if (units.base.endurance <= 0) // If base endurance <= 0 declare winner
    {
        playerWins = true;
        opponentWins = false;
        return true;
    }
    std::vector<int> deadBox;
    for (auto &[key, val] : units.units) // gather all dead units
    {
        if (val->endurance <= 0)
        {
            std::cout << "(Mediator) Unit with id " << key << " died." << std::endl;
            deadBox.push_back(key);
        }
    }
    for (auto &&id : deadBox) // remove all dead units
    {
        units.removeUnit(id);
    }
    return true;
}

bool add_new_unit(int &max_index, listUnits &units)
{
    // add a unit if base qTime == 0
    if (units.base.queue != '0' && units.base.qTime == 0)
    {
        max_index++;
        switch (units.base.queue)
        {
        case 'K':
        {
            units.addKnight(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'S':
        {
            units.addSwordsman(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'A':
        {
            units.addArcher(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'P':
        {
            units.addPikeman(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'R':
        {
            units.addRam(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'C':
        {
            units.addCatapult(max_index, units.base.posx, units.base.posy);
            break;
        }
        case 'W':
        {
            units.addWorker(max_index, units.base.posx, units.base.posy);
            break;
        }
        default:
            std::cerr << "(Mediator) Error in base queue!" << std::endl;
            return false;
        }
        units.base.queue = '0';
    }
    return true;
}

std::string unit_output_player(const std::string &name, listUnits &units)
{
    // string buffer for player status files
    std::stringstream ss;
    ss << name << " B " << units.base.id << " " << units.base.posx << " " << units.base.posy << " " << units.base.endurance << " " << units.base.queue << '\n';
    for (auto &[id, unit] : units.units)
    {
        ss << name << " " << units.id2type[id] << " " << id << " " << unit->posx << " " << unit->posy << " " << unit->endurance << '\n';
    }
    return ss.str();
}

std::string unit_output_mediator(const std::string &name, listUnits &units)
{
    // string buffer for mediator status file
    std::stringstream ss;
    ss << name << " B " << units.base.id << " " << units.base.posx << " " << units.base.posy;
    ss << " " << units.base.endurance << " " << units.base.queue << " " << units.base.qTime << '\n';
    for (auto &[id, unit] : units.units)
    {
        ss << name << " " << units.id2type[id] << " " << id << " " << unit->posx << " " << unit->posy << " " << unit->endurance << '\n';
    }
    return ss.str();
}

void write_hr_map_status(const grid &map, listUnits &units_p1, listUnits &units_p2)
{
    // print map using the format (x,y,[e/b/r],[units],p1,p2)
    // where x,y are coordinates, e - empty, b - barrier, r - resource
    // units are named A1, K1,... for player 1, and A2, K2,... for player 2
    // p1 and p2 is the total number of units of each player on the node
    std::ofstream file("data/mapaHR.txt");
    for (int i = 0; i < int(map.size()); i++)
    {
        for (int j = 0; j < int(map[0].size()); j++)
        {
            int p1_count = 0, p2_count = 0;
            for (auto &[key, value] : units_p1.units)
            {
                if (value->posx == j && value->posy == i) p1_count += 1;
            }
            for (auto &[key, value] : units_p2.units)
            {
                if (value->posx == j && value->posy == i) p2_count += 1;
            }

            file << "(" << j << "," << i << "," << map[i][j]->print();
            file << "," << p1_count << "," << p2_count;
            if (units_p1.base.posx == j && units_p1.base.posy == i) file << ",B1";
            if (units_p2.base.posx == j && units_p2.base.posy == i) file << ",B2";
            for (auto &[id, unit] : units_p1.units)
            {
                if (unit->posx == j && unit->posy == i) file << "," << units_p1.id2type[id] << "1";
            }
            for (auto &[id, unit] : units_p2.units)
            {
                if (unit->posx == j && unit->posy == i) file << "," << units_p2.id2type[id] << "2";
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