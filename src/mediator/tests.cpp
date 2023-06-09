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

#include "tests.h"

void test_remove_dead_units()
{
    bool pWins, oWins;
    listUnits units;
    units.addBase(1, 200, 0, 0, '0');
    units.addArcher(0, -1, 0, 0);
    units.addArcher(2, 2, 0, 0);
    std::cout << RESET << "(Mediator) io.h remove_dead_units kill test ";
    if (!remove_dead_units(units, pWins, oWins)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else
    {
        if (units.qArcher > 1 || !units.is_unique(0)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
        else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
}