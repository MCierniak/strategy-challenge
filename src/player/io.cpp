#include "io.h"

grid parse_map(char map_path[], int &X, int &Y)
{
    grid map;
    X = 0;
    Y = 0;

    std::ifstream file(map_path);

    std::string line;
    while(getline(file, line))
    {
        grid_row temp;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '0')
            {
                temp.push_back(
                    std::make_unique<emptySpace>()
                );
            }
            else if (line[i] == '1')
            {
                temp.push_back(
                    std::make_unique<emptySpace>()
                );
            }
            else if (line[i] == '2')
            {
                temp.push_back(
                    std::make_unique<emptySpace>()
                );
            }
            else
            {
                temp.push_back(
                    std::make_unique<barrier>()
                );
            }
        }
        
        map.push_back(std::move(temp));
        X = line.length();
        Y += 1;
    }
    file.close();
    return map;
}

grid parse_status(char status_path[])
{
    return grid();
}

void test_parse_map()
{
    grid test;
    int X, Y;
    try
    {
        if (test == parse_map("wrong address", X, Y))
        {
            std::cout << "pars_map() test passed" << std::endl;
        }
        else
        {
            std::cout << "pars_map() test failed" << std::endl;
        }
    }
    catch (...)
    {
        std::cout << "pars_map() test failed" << std::endl;
    }
}