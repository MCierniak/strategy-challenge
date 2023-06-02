#include <iostream>
#include <fstream>
#include <random>

void generate_random_map();

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        /*do something*/
    }
    else
    {
        generate_random_map();
    }
    return 0;
}

void generate_random_map()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> len(1, 100), type(0, 8);

    int X = len(gen), Y = len(gen);

    std::uniform_int_distribution<> posx(0, X-1), posy(0, Y-1);

    char map[X][Y];

    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            int grid = type(gen);
            if (grid != 8)
            {
                map[i][j] = '0';
            }
            else
            {
                map[i][j] = '9';
            }
        }
    }

    map[posx(gen)][posy(gen)] = '1';
    map[posx(gen)][posy(gen)] = '2';

    std::ofstream file("data/mapa.txt");
    for (int j = 0; j < Y; j++)
    {
        file << map[0][j];
    }
    for (int i = 0; i < X; i++)
    {
        file << '\n';
        for (int j = 0; j < Y; j++)
        {
            file << map[i][j];
        }
    }
    file.close();
}