#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <vector>

#define gridline std::vector<char>
#define grid std::vector<gridline> // call with grid[y coord][x coord]

grid parse_map(char map_path[], int &X, int &Y);
grid parse_status(char status_path[]);

void test_parse_map();

#endif