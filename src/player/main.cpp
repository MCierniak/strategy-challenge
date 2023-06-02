#include <cstdlib>
#include <iostream>

char** parse_map();

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

char** parse_map()
{
    return nullptr;
}

void make_moves(char *argv[], int time_limit)
{

}
