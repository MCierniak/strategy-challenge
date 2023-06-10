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

#include "defaults.h"

// Unit tests

#include "path/dijkstra.h"
#include "units/misc.h"
#include "io.h"

// Color macros
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESET "\033[0m"

void test_io_get_map();
void test_io_get_status();
void test_units_units_worker_find_target();
void test_units_actions_action_unit();
void test_main_resNodeList_sort();
void test_units_misc_listUnits();
void test_units_actions_evade();
void test_units_actions_attack();
void test_grid_addId();
void test_grid_resource_resNodeList();
void test_path_dijkstra_priority_queue();