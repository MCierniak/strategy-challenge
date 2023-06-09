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

#include "io.h"
#include "grid.h"
#include "units/misc.h"
#include "units/actions.h"

#include <algorithm>
#include <chrono>

// Main player function.
void make_moves(char* argv[], int time_limit);

int main(int argc, char* argv[])
{
    #ifndef TESTING_TRUE
        // If optional execution time parameter is passed, use it,
        // otherwise assume time limit is 5 seconds
        // do nothing if argc is different than 4 or 5
        if (argc == 5)
        {
            make_moves(argv, atoi(argv[4]));
        }
        else if (argc == 4)
        {
            make_moves(argv, 5);
        }
        return 0;
    #else
        #include "tests.h"
        test_io_get_map();
        test_io_get_status();
        test_units_units_worker_find_target();
        test_units_actions_action_unit();
        test_main_resNodeList_sort();
        test_units_misc_listUnits();
        test_units_actions_evade();
        test_units_actions_attack();
        test_grid_addId();
        test_path_dijkstra_priority_queue();
    #endif
}

void make_moves(char *argv[], int time_limit)
{
    // Get current time and translate the time limit to microseconds (possibly overkill)
    auto start = CURRENT_TIME;
    int time_limit_us = MICROSECONDS(SECONDS(time_limit)).count();

    // Load raw map into memory. Ignore bases.
    int X = 0, Y = 0;
    grid map;
    if (!get_map(argv[1], map, X, Y)) return;

    // Load status into memory. Separate by alliegence type.
    // Update grid flags based on enemy unit placement
    listUnits myUnits, enemyUnits;
    long gold;
    if (!get_status(argv[2], map, gold, myUnits, enemyUnits)) return;

    // Sort resource node list by distance to base
    resource::resNodeList.sort(
        [&myUnits](const std::vector<int> &first, const std::vector<int> &second)
        { 
            int baseX = myUnits.base.posx, baseY = myUnits.base.posy;
            return (Dist(baseX, baseY, first[1], first[0]) < Dist(baseX, baseY, second[1], second[0]));
        }
    );

    // Sort enemy unit ids by distance to my base
    enemyUnits.hitList.sort(
        [&myUnits, &enemyUnits](const int &a, const int &b)
        {
            int base_posx = myUnits.base.posx;
            int base_posy = myUnits.base.posy;

            int unita_posx, unita_posy, unitb_posx, unitb_posy;
            if (enemyUnits.id2type[a] == 'B')
            {
                unita_posx = enemyUnits.base.posx;
                unita_posy = enemyUnits.base.posy;
            }
            else
            {
                unita_posx = enemyUnits.units[a]->posx;
                unita_posy = enemyUnits.units[a]->posy;
            }
            if (enemyUnits.id2type[b] == 'B')
            {
                unitb_posx = enemyUnits.base.posx;
                unitb_posy = enemyUnits.base.posy;
            }
            else
            {
                unitb_posx = enemyUnits.units[b]->posx;
                unitb_posy = enemyUnits.units[b]->posy;
            }
            return (Dist(base_posx, base_posy, unita_posx, unita_posy) < Dist(base_posx, base_posy, unitb_posx, unitb_posy));
        }
    );

    // Open order file.
    std::ofstream file(argv[3]);
    if(file.fail()) return;

    std::string temp;
    if (action_base(temp, gold, myUnits, enemyUnits))
    {
        file << temp;
        temp = std::string();
    }
    int duration = DURATION(CURRENT_TIME - start);
    for (auto &[key, value] : myUnits.units)
    {
        #ifdef VERBOSE_TRUE
            std::cout << "(Player) I am making decisions for unit id " << key <<std::endl;
        #endif
        if (action_unit(temp, key, map, myUnits, enemyUnits))
        {
            file << temp;
            temp = std::string();
        }
        if (duration > time_limit_us - CLEANUP_TIME)
        {
            #ifdef VERBOSE_TRUE
                std::cout << "(Player) I have no time for more." <<std::endl;
            #endif
            break;
        }
    }
    #ifdef VERBOSE_TRUE
        std::cout << "(Player) I am finished." <<std::endl;
    #endif
    // cleanup
    file.close();
}
