#ifndef IO_H
#define IO_H

#include "grid.h"

#include <iostream>
#include <fstream>

grid parse_map(char map_path[], int &X, int &Y);
grid parse_status(char status_path[]);

void test_parse_map();

#endif