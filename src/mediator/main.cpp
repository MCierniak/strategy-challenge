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

#include <iostream>
#include <fstream>
#include <random>

// Initial resource for each player
#define INITIAL_GOLD_1 2000
#define INITIAL_GOLD_2 2000
// Define chance for random map tile to be empty (val*10%)
#define EMPTY_CHANCE 7
// Define chance for random map tile to be RESOURCE (val*10%)
#define RESOURCE_CHANCE 1
// The chance for barrier tiles is 100% - EMPTY_CHANCE*10% - RESOURCE_CHANCE*10%

// Function preparing the initial state of the game,
// generating randomized map file "mapa.txt",
// generating corresponding "status1.txt", "status2.txt" files for both players.
void start_game();

void print_map(const std::vector<std::vector<char>> &map, int X, int Y);

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        /*do something*/
    }
    else if (argc == 1)
    {
        start_game();
    }
    return 0;
}

void start_game()
{
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
            int grid = type(gen);
            if (grid <= EMPTY_CHANCE - 1)
            {
                map[i][j] = '0';
            }
            else if (grid > EMPTY_CHANCE - 1 && grid <= EMPTY_CHANCE + RESOURCE_CHANCE - 1)
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
    std::ofstream file("data/mapa.txt");
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

    file.open("data/status1.txt");
    file << gold_1 << '\n';
    file << "P B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
    file << "E B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
    file.close();

    file.open("data/status2.txt");
    file << gold_2 << '\n';
    file << "E B 0 " << trgt_x_1 << " " << trgt_y_1 << " 200 0\n";
    file << "P B 1 " << trgt_x_2 << " " << trgt_y_2 << " 200 0\n";
    file.close();
}

void print_map(const std::vector<std::vector<char>> &map, int X, int Y)
{
    std::cout << "Map:\n";
    std::cout << "Size: (" << X << ", " << Y << ")\n\n";
    std::cout << "Geography:" << "\n\n";
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}