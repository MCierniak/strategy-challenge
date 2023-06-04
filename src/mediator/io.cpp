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

bool get_status(const std::string &status_path, bool &player1Turn, int &max_index, grid &map_p1, grid &map_p2, long &gold_p1, long &gold_p2, listUnits &units_p1, listUnits &units_p2)
{
    try
    {
        // Open file in read mode
        std::ifstream file(status_path);
        if (file.fail())
        {
            std::cerr << "Can't open mediator.txt!" << std::endl;
            gold_p1 = 0;
            gold_p2 = 0;
            return false;
        }

        // Parse file, start with 1st line, indicating the player that took the last turn
        std::string line;
        getline(file, line);
        if (line == "1")
        {
            std::cout << "player 1 submitted orders." << std::endl;
            player1Turn = false;
        }
        else if (line == "2")
        {
            std::cout << "player 2 submitted orders." << std::endl;
            player1Turn = true;
        }
        else
        {
            std::cerr << "Can't parse line 1 of mediator.txt!" << std::endl;
            return false;
        }

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

            // Determine type of unit first, alliegence last.
            switch (line[3])
            {
            case 'B': // Base unit, assume line has extra queue param
                ss >> alliegence >> type >> id >> posx >> posy >> endurance >> bQueue;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.bases.push_back(Base(id, endurance, posx, posy, bQueue));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'B';
                    units_p1.id2index[id] = units_p1.bases.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.bases.push_back(Base(id, endurance, posx, posy, bQueue));
                    units_p1.unitCount++;
                    units_p2.id2type[id] = 'B';
                    units_p2.id2index[id] = units_p2.bases.size() - 1;
                }
                continue;
            case 'K': // Knight unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.knights.push_back(Knight(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'K';
                    units_p1.id2index[id] = units_p1.knights.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.knights.push_back(Knight(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'K';
                    units_p2.id2index[id] = units_p2.knights.size() - 1;
                }
                continue;
            case 'S': // Swordsman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.swordsmen.push_back(Swordsman(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'S';
                    units_p1.id2index[id] = units_p1.swordsmen.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.swordsmen.push_back(Swordsman(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'S';
                    units_p2.id2index[id] = units_p2.swordsmen.size() - 1;
                }
                continue;
            case 'A': // Archer unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.archers.push_back(Archer(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'A';
                    units_p1.id2index[id] = units_p1.archers.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.archers.push_back(Archer(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'A';
                    units_p2.id2index[id] = units_p2.archers.size() - 1;
                }
                continue;
            case 'P': // Pikeman unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.pikemen.push_back(Pikeman(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'P';
                    units_p1.id2index[id] = units_p1.pikemen.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.pikemen.push_back(Pikeman(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'P';
                    units_p2.id2index[id] = units_p2.pikemen.size() - 1;
                }
                continue;
            case 'C': // Catapult unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.catapults.push_back(Catapult(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'C';
                    units_p1.id2index[id] = units_p1.catapults.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.catapults.push_back(Catapult(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'C';
                    units_p2.id2index[id] = units_p2.catapults.size() - 1;
                }
                continue;
            case 'R': // Ram unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.rams.push_back(Ram(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'R';
                    units_p1.id2index[id] = units_p1.rams.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.rams.push_back(Ram(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'R';
                    units_p2.id2index[id] = units_p2.rams.size() - 1;
                }
                continue;
            case 'W': // Worker unit
                ss >> alliegence >> type >> id >> posx >> posy >> endurance;
                if (alliegence == "P1")
                {
                    map_p2[posy][posx]->setTrav(false);
                    units_p1.workers.push_back(Worker(id, endurance, posx, posy));
                    units_p1.unitCount++;
                    units_p1.id2type[id] = 'W';
                    units_p1.id2index[id] = units_p1.workers.size() - 1;
                }
                else
                {
                    map_p1[posy][posx]->setTrav(false);
                    units_p2.workers.push_back(Worker(id, endurance, posx, posy));
                    units_p2.unitCount++;
                    units_p2.id2type[id] = 'W';
                    units_p2.id2index[id] = units_p2.workers.size() - 1;
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

bool get_orders(const std::string &orders_path, int &max_index, grid &map, long &gold, listUnits &playerUnits, listUnits &opponentUnits, bool &playerWins, bool &opponentWins)
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
            int id, posx, posy;
            char action, target;
            ss >> id >> action;
            if (auto itType = playerUnits.id2type.find(id); itType != playerUnits.id2type.end())
            {
                switch (itType -> second)
                {
                case 'B': // Base unit
                    getline(ss, line);
                    if (line.length() > 2)
                    {
                        std::cout << "Error in orders! Unit with id " << id << " received an invalid command!" << std::endl;
                        playerWins = false;
                        opponentWins = true;
                        return true;
                    }
                    else
                    {
                        std::cout << "Unit with id " << id << " (B) received an order to build " << line[1] << "." << std::endl;
                        auto itInd = playerUnits.id2index.find(id);
                        playerUnits.bases[itInd -> second].queue = line[1];
                        playerUnits.bases[itInd -> second].qTime = BUILD_TIME(line[1]);
                    }
                //other orders go here
                    continue;
                default: // Error in unit tag, terminate
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

bool prep_next_turn(bool &player1Win, bool &player2Win)
{
    // Load raw map into memory. Ignore units.
    int X = 0, Y = 0;
    grid map_p1, map_p2;
    if (!get_map(MAP_LOC, map_p1, X, Y)) return false;
    if (!get_map(MAP_LOC, map_p2, X, Y)) return false;

    // Get game status prior to last turn
    bool player1Turn;
    long gold_p1 = 0, gold_p2 = 0;
    int max_index = 0;
    listUnits units_p1, units_p2;
    if (!get_status(MEDIATOR_LOC, player1Turn, max_index, map_p1, map_p2, gold_p1, gold_p2, units_p1, units_p2)) return false;
    
    // Parse player orders, decr building queue
    if (player1Turn)
    {
        if (!get_orders(ORDERS_P2_LOC, max_index, map_p2, gold_p2, units_p2, units_p1, player2Win, player1Win)) return false;
        if (units_p1.bases[0].queue != '0' && --units_p1.bases[0].qTime == 0)
        {
            // Build new unit, set base queue to '0'
        }
    }
    else
    {
        if (!get_orders(ORDERS_P1_LOC, max_index, map_p1, gold_p1, units_p1, units_p2, player1Win, player2Win)) return false;
        if (units_p2.bases[0].queue != '0' && --units_p2.bases[0].qTime == 0)
        {
            // Build new unit, set base queue to '0'
        }
    }

    return true;
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
            std::cout << map[i][j] -> print() << " ";
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

bool file_exists (const std::string &name) {
  struct stat buffer;   
  return (stat(name.c_str(), &buffer) == 0); 
}