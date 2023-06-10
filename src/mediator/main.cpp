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

// Macros for wall time monitoring
#define DURATION(x) std::chrono::duration_cast<MILLISECONDS>(x).count()
#define CURRENT_TIME std::chrono::high_resolution_clock::now()
#define MILLISECONDS std::chrono::milliseconds
#define SECONDS std::chrono::seconds

std::string exec(const char* cmd);

int main(int argc, char **argv)
{
    #ifndef TESTING_TRUE
        // Declare command line with stringstream
        std::stringstream ss;

        // Get custom timeout from arg, if nothing passed, assume 5s
        int timeout = 5;
        if (argc == 2)
        {
            timeout = std::stoi(argv[1]);
        }

        // If mediator file exists, continue previously started game
        if (file_exists(MEDIATOR_LOC))
        {

            std::ifstream file(MEDIATOR_LOC);
            std::string temp;
            getline(file, temp);
            int turn = stoi(temp);
            file.close();

            // Call player 1 script
            if (++turn; turn % 2 == 1)
            {
                std::cout << "(Mediator) Turn " << turn << ". Running player 1 script." << std::endl;
                if(timeout == 5) ss << "timeout " << timeout << " " << P1_SCRIPT << " " << MAP_LOC << " " << STATUS_P1_LOC << " " << ORDERS_P1_LOC;
                else ss << "timeout " << timeout << " " << P1_SCRIPT << " " << MAP_LOC << " " << STATUS_P1_LOC << " " << ORDERS_P1_LOC << " " << timeout;
                
                #ifndef DEBUG_TRUE // release call
                std::string ret = exec(ss.str().c_str());
                #else // debug call 
                std::string ret;
                auto start = CURRENT_TIME;
                system(ss.str().c_str());
                int duration = DURATION(CURRENT_TIME - start);
                std::cout << "(Mediator) Elapsed time " << duration << " ms" << std::endl; 
                #endif

                if (!(ret == std::string()))
                {
                    std::cout << "(Mediator) Player 1 timed out!" << std::endl;
                    std::cout << "(Mediator) Player 2 wins!" << std::endl;
                    return 0;
                }
                std::cout << "(Mediator) Player 1 submitted orders." << std::endl;
            }

            // Call player 2 script
            else
            {
                std::cout << "(Mediator) Turn " << turn << ". Running player 2 script." << std::endl;
                if(timeout == 5) ss << "timeout " << timeout << " " << P2_SCRIPT << " " << MAP_LOC << " " << STATUS_P2_LOC << " " << ORDERS_P2_LOC;
                else ss << "timeout " << timeout << " " << P2_SCRIPT << " " << MAP_LOC << " " << STATUS_P2_LOC << " " << ORDERS_P2_LOC << " " << timeout;
                
                #ifndef DEBUG_TRUE // release call
                std::string ret = exec(ss.str().c_str());
                #else // debug call 
                std::string ret;
                auto start = CURRENT_TIME;
                system(ss.str().c_str());
                int duration = DURATION(CURRENT_TIME - start);
                std::cout << "(Mediator) Elapsed time " << duration << " ms" << std::endl; 
                #endif

                if (!(ret == std::string()))
                {
                    std::cout << "(Mediator) Player 2 timed out!" << std::endl;
                    std::cout << "(Mediator) Player 1 wins!" << std::endl;
                    return 0;
                }
                std::cout << "(Mediator) Player 2 submitted orders." << std::endl;
            }

            // Prepare next turn states.
            bool player1Win = false, player2Win = false, draw = false;
            if(!prep_next_turn(turn, player1Win, player2Win, draw))
            {
                std::cerr << "(Mediator) prep_next_turn failed!" << std::endl;
                return 0;
            }
            if (player1Win)
            {
                std::cout << "(Mediator) Player 1 wins!" << std::endl;
                return 0;
            }
            if (player2Win)
            {
                std::cout << "(Mediator) Player 2 wins!" << std::endl;
                return 0;
            }
            if (draw)
            {
                std::cout << "(Mediator) Game ends in a draw!" << std::endl;
                return 0;
            }
            return 0;

        }

        // If mediator file not present, start a new game.
        else
        {
            int turn = 1;
            if(!start_game())
            {
                std::cerr << "(Mediator) start_game failed!" << std::endl;
                return 0;
            }
            std::cout << "(Mediator) Turn " << turn << ". Running player 1 script." << std::endl;

            // Call player 1 script
            if(timeout == 5) ss << "timeout " << timeout << " " << P1_SCRIPT << " " << MAP_LOC << " " << STATUS_P1_LOC << " " << ORDERS_P1_LOC;
            else ss << "timeout " << timeout << " " << P1_SCRIPT << " " << MAP_LOC << " " << STATUS_P1_LOC << " " << ORDERS_P1_LOC << " " << timeout;
            
            #ifndef DEBUG_TRUE // release call
            std::string ret = exec(ss.str().c_str());
            #else // debug call
            std::string ret;
            auto start = CURRENT_TIME;
            system(ss.str().c_str());
            int duration = DURATION(CURRENT_TIME - start);
            std::cout << "(Mediator) Elapsed time " << duration << " ms" << std::endl; 
            #endif
            
            if (!(ret == std::string()))
            {
                std::cout << "(Mediator) Player 1 timed out!" << std::endl;
                std::cout << "(Mediator) Player 2 wins!" << std::endl;
                return 0;
            }
            else
            {
                std::cout << "(Mediator) Player 1 submitted orders." << std::endl;
                bool player1Win = false, player2Win = false, draw = false;
                if(!prep_next_turn(turn, player1Win, player2Win, draw))
                {
                    std::cerr << "(Mediator) prep_next_turn failed!" << std::endl;
                    return 0;
                }
                if (player1Win)
                {
                    std::cout << "(Mediator) Player 1 wins!" << std::endl;
                    return 0;
                }
                if (player2Win)
                {
                    std::cout << "(Mediator) Player 2 wins!" << std::endl;
                    return 0;
                }
                if (draw)
                {
                    std::cout << "(Mediator) Game ends in a draw!" << std::endl;
                    return 0;
                }
                return 0;
            }
        }
    #else
        #include "tests.h"
        test_remove_dead_units();
        test_process_unit_orders();
    #endif
    return 0;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}