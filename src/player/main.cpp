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
#include "grid.h"
#include "units.h"

#include <algorithm>
#include <chrono>

// Macros for wall time monitoring
#define DURATION(x) std::chrono::duration_cast<MICROSECONDS>(x).count()
#define CURRENT_TIME std::chrono::high_resolution_clock::now()
#define MICROSECONDS std::chrono::microseconds
#define SECONDS std::chrono::seconds
// Time (in microseconds) needed for final cleanup
#define CLEANUP_TIME 100

// Main player function.
void make_moves(char* argv[], int time_limit);

int main(int argc, char* argv[])
{
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
    // Update grid traversal flags based on enemy unit placement
    listUnits myUnits, enemyUnits;
    long gold;
    if (!get_status(argv[2], map, gold, myUnits, enemyUnits)) return;

    // Prep exit conditions for decision loop
    std::size_t i = 0;
    std::size_t max_i = std::max({
        myUnits.archers.size(), myUnits.bases.size(),
        myUnits.catapults.size(), myUnits.knights.size(),
        myUnits.pikemen.size(), myUnits.rams.size(),
        myUnits.swordsmen.size(), myUnits.workers.size()
    });

    // Open order file.
    std::ofstream file(argv[3]);
    if(file.fail()) return;

    // Decision loop. One unit of each type performs an action which
    // gets immediately written to file. Wall time is estimated so that
    // the player script has a chance to end without timeout disqualification.
    int duration = DURATION(CURRENT_TIME - start);
    while (duration < time_limit_us - CLEANUP_TIME)
    {
        if (i >= max_i) break;
        
        std::string temp;
        if (i < myUnits.bases.size())
        {
            if (action(temp, myUnits.bases[i], gold, map, myUnits, enemyUnits)) file << temp;
        }
        // other actions
        i++;
        duration = DURATION(CURRENT_TIME - start);
    }

    // cleanup
    file.close();
}
