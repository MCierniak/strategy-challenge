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

#ifndef MEDIATOR_IO_H
#define MEDIATOR_IO_H

#include "defaults.h"
#include "units.h"

#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>

// Parse map from file, output parsed map and X,Y size
bool get_map(const std::string &map_path, grid &map, int &X, int &Y);

// Parse status from file, output rosters of own and enemy units
bool get_status(const std::string &status_path, int &max_index, grid &map_p1, grid &map_p2, long &gold_p1, long &gold_p2, listUnits &units_p1, listUnits &units_p2);

// Parse, test and apply player orders
bool get_orders(const std::string &orders_path, grid &map, long &gold, listUnits &playerUnits, listUnits &opponentUnits, bool &playerWins, bool &opponentWins);

// Function preparing the initial state of the game,
// generating randomized map file "mapa.txt",
// generating corresponding "status1.txt", "status2.txt" files for both players.
bool start_game();

// Function evaluating last order and updating status for the next player.
bool prep_next_turn(int &turn, bool &player1Win, bool &player2Win, bool &draw);

// Interpret player orders for base
bool process_base_orders(int id, char task, std::stringstream &order, long &gold, listUnits &units, bool &playerWins, bool &opponentWins);
// Interpret player orders for units
bool process_unit_orders(int id, char task, std::stringstream &order, const grid &map, listUnits &units, listUnits &enemies, bool &playerWins, bool &opponentWins);

// Remove untis with 0 or negative endurance
bool remove_dead_units(listUnits &units, bool &playerWins, bool &opponentWins);
// Add built unit
bool add_new_unit(int &max_index, listUnits &units);

// Output for player status files
std::string unit_output_player(const std::string &name, listUnits &units);
// Output for mediator status files
std::string unit_output_mediator(const std::string &name, listUnits &units);

// Human readable map for the makeshift GUI :)
void write_hr_map_status(const grid &map, listUnits &units_p1, listUnits &units_p2);

// Check if the file provided in name string exists
bool file_exists(const std::string &name);

#endif