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

int main()
{
    if (file_exists(MEDIATOR_LOC))
    {
        bool player1Win, player2Win;
        if(!prep_next_turn(player1Win, player2Win))
        {
            std::cerr << "prep_next_turn failed!" << std::endl;
            return 0;
        }
        if (player1Win)
        {
            std::cout << "Player 1 wins!" << std::endl;
            return 0;
        }
        if (player2Win)
        {
            std::cout << "Player 2 wins!" << std::endl;
            return 0;
        }
        // call next player script
    }
    else
    {
        if(!start_game())
        {
            std::cerr << "start_game failed!" << std::endl;
            return 0;
        }
        // call player 1 script
    }
    return 0;
}