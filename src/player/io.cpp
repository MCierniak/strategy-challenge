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

grid get_map(char map_path[], int &X, int &Y)
{
    // Initialize grid object and set X and Y
    grid map;
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
            // Set empty spaces on tiles without blockades. Ignore bases.
            if (line[i] == '0' || line[i] == '1' || line[i] == '2')
            {
                temp.push_back(
                    std::make_unique<emptySpace>()
                );
            }
            // Set resource nodes
            else if (line[i] == '6')
            {
                std::unique_ptr<emptySpace> tempPtr(new emptySpace());
                tempPtr -> setResource(true);
                temp.push_back(
                    std::move(tempPtr)
                );
            }
            // Set blockades
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
        // Increment column count
        Y += 1;
    }
    file.close();
    return map;
}

bool get_status(char status_path[], unitRoster &myTeam, unitRoster &enemy, long &gold)
{
    // Open file in read mode
    std::ifstream file(status_path);

    // Parse file
    std::string line;
    getline(file, line);
    gold = std::stol(line);
    std::cout << "Gold: " << gold << "\nLines:\n";
    while(getline(file, line))
    {
        std::cout << line << std::endl;
    }
    
    file.close();
    return false;
}

void test_get_map()
{
    // Test if wrong address will result in an empty grid object.
    // Desired result is true. Catch any additional errors.
    grid test;
    int X, Y;
    try
    {
        if (test == get_map(strdup("wrong address"), X, Y))
        {
            std::cout << "pars_map() test passed" << std::endl;
        }
        else
        {
            std::cout << "pars_map() test failed" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "pars_map() test failed" << std::endl;
    }
}