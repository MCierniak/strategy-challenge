#include "io.h"
#include "grid.h"
#include "units.h"

#include <chrono>

#define MICROSECONDS std::chrono::microseconds
#define SECONDS std::chrono::seconds
#define CURRENT_TIME std::chrono::high_resolution_clock::now()
#define DURATION(x) std::chrono::duration_cast<MICROSECONDS>(x).count()
#define CLEANUP_TIME 1000

void make_moves(char* argv[], int time_limit);

int main(int argc, char* argv[])
{
    if (argc > 4)
    {
        make_moves(argv, atoi(argv[4]));
    }
    else if (argc > 1)
    {
        make_moves(argv, 5);
    }
    return 0;
}

void make_moves(char *argv[], int time_limit)
{
    auto start = CURRENT_TIME;
    int time_limit_us = MICROSECONDS(SECONDS(time_limit)).count();

    int X, Y;
    grid map = parse_map(argv[1], X, Y);

    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            std::cout << map[i][j] -> print() << " ";
        }
        std::cout << '\n';
    }
    

    // int duration = DURATION(CURRENT_TIME - start);
    // while (duration < time_limit_us - CLEANUP_TIME)
    // {
    //     // this is where the magic happens
    //     duration = DURATION(CURRENT_TIME - start);
    // }
    // // cleanup
}
