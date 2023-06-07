#ifndef MEDIATOR_DEFAULTS_H
#define MEDIATOR_DEFAULTS_H

// Initial resource for each player
#define INITIAL_GOLD_1 2000
#define INITIAL_GOLD_2 2000
// Define chance for random map tile to be empty (val*10%)
#define EMPTY_CHANCE 7
// Define chance for random map tile to be RESOURCE (val*10%)
#define RESOURCE_CHANCE 1
// The chance for barrier tiles is 100% - EMPTY_CHANCE*10% - RESOURCE_CHANCE*10%

#define GRID_MIN 6
#define GRID_MAX 32

// Data file location
#define MAP_LOC "data/mapa.txt"
#define MEDIATOR_LOC "data/mediator.txt"
#define STATUS_P1_LOC "data/status1.txt"
#define STATUS_P2_LOC "data/status2.txt"
#define ORDERS_P1_LOC "data/rozkazy1.txt"
#define ORDERS_P2_LOC "data/rozkazy2.txt"

// Path to player scripts
#define P1_SCRIPT "bin/player"
#define P2_SCRIPT "bin/player"

#endif