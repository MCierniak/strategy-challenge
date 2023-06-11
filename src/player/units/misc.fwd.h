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

#ifndef PLAYER_UNITS_MISC_FWD_H
#define PLAYER_UNITS_MISC_FWD_H

// Misc functions forward header. Necessary to avoid circular includes.

#include "../defaults.h"

#include "../grid.h"

struct listUnits;

// Specialized find_target() function for swordsmen
bool find_target_swordsman(int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Specialized find_target() function for archers
bool find_target_archer(int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Specialized find_target() function for pikemen
bool find_target_pikeman(int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Specialized find_target() function for knights
bool find_target_knight(int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Specialized find_target() function for rams
bool find_target_ram(int sId, const grid &map, listUnits &allies, listUnits &enemies);
// Specialized find_target() function for catapults
bool find_target_catapult(int sId, const grid &map, listUnits &allies, listUnits &enemies);

#endif