# Strategy Challenge Project

This is a challenge project, where two players compete in a 2d turn-based strategy game. Each player has a base where they can produce units. The goal of the game is to destroy the other player's base within 2000 turns (1000 turns per player) using pre-compiled player scripts.

Each turn a player script is called by a mediator. The script has to be pre-compiled and no user input is allowed once the game starts. The script passes commands to the mediator via plaintext files, the mediator interprets these commands and updates the game state accordingly. Passing invalid commands, outputting anything to stdout or timing out disqualifies the player.

A detailed project description (in Polish) is available [here](https://github.com/MCierniak/strategy-challenge/blob/master/docs/instrukcja.pdf).

## Configuration

Before building the script, the game parameters need to be set in the mediator header file `src/mediator/defaults.h`

```cpp
// Initial resource for each player
#define INITIAL_GOLD_1 2000
#define INITIAL_GOLD_2 2000
// Define chance for random map tile to be empty (val*10%)
#define EMPTY_CHANCE 7
// Define chance for random map tile to be RESOURCE (val*10%)
#define RESOURCE_CHANCE 1
// The chance for barrier tiles is 100% - EMPTY_CHANCE*10% - RESOURCE_CHANCE*10%

// Minimum and maximum possible size of the map
#define GRID_MIN 16
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
```

In addition, the player script can be configured to allow more "safety" when avoiding timeout disqualification. For that purpose modify in `src/player/defaults.h`

```cpp
// Time (in microseconds) needed for final cleanup
#define CLEANUP_TIME 10000
```

## Installation

The scripts were written and tested on Ubuntu 22.04 . A makefile, provided in the repo, will perform a clean build of the mediator and player binaries when called with ```make```. 

In addition, the player and mediator executables can be compiled separately using

```bash
make player
make mediator
```

## Usage

The player script will do nothing unless called with 3 or 4 arguments

```bash
./player path_to_map path_to_status path_to_orders [optional_timeout]
```

If valid map and status files are provided and the script can write in the desired order file location, it will output a text file with orders for the mediator. The script will do its best to avoid timeout disqualification and might even forfeit its own output if necessary.

The player script is not meant to be called directly (outside of test mode). Instead, each game turn progresses when calling

```bash
./mediator [optional_timeout]
```

If not provided, the timeout parameter for the latest turn will be set to 5 seconds. On first run, the mediator script will randomly generate the map geography and the corresponding status files. Aferwards it will immediately call the first player script and parse its orders.

```bash
usr@host:~$ ./bin/mediator
(Mediator) Starting new game
(Mediator) Turn 1. Running player 1 script.
(Mediator) Player 1 submitted orders.
(Mediator) Unit with id 0 (base) received order to build A.
```

The mediator will monitor and update the game state with a certain level of verbosity. If a win condition is met, the winner will be declared and the game ends. Otherwise, each call will advance the game to the next turn.

```bash
usr@host:~$ ./bin/mediator
(Mediator) Turn 29. Running player 1 script.
(Mediator) Player 1 submitted orders.
(Mediator) Unit with id 2 (archer) received order to move from 17 7 to 17 9 (distance 2)
(Mediator) Unit with id 6 (catapult) received order to move from 12 3 to 13 4 (distance 2)
(Mediator) Unit with id 4 (worker) mined gold at 9 0 for Player 1
usr@host:~$ ./bin/mediator
(Mediator) Turn 30. Running player 2 script.
(Mediator) Player 2 submitted orders.
(Mediator) Unit with id 3 (archer) received order to attack unit with id 2 (archer, distance 5)
(Mediator) Unit with id 7 (catapult) received order to attack unit with id 2 (archer, distance 5)
(Mediator) Unit with id 5 (worker) mined gold at 17 18 for Player 2
(Mediator) Unit with id 2 died.
```

In order to restart the game on a new map, you need to manually delete the mediator.txt file. A subsequent mediator call will start a new game.

## Makeshift GUI :grin:

Instead of writing a GUI for the mediator I have temporarily turned [VS Code](https://code.visualstudio.com/) into a game window. A sample game is shown below. The text coloring can be achieved using [TODO Highlight](https://marketplace.visualstudio.com/items?itemName=wayou.vscode-todo-highlight).

![](https://github.com/MCierniak/strategy-challenge/blob/master/docs/gameplay.gif)

## Debug mode

The mediator debug mode can be engaged to allow execution of a verbose player script. The game progresses normally, but timeout disqualification is suppressed. The player script will now explain its decision making process.

```bash
usr@host:~$ ./bin/mediator
(Mediator) Turn 7. Running player 1 script.
(Player) (Base) I will build worker, because it is turn 2.
(Player) I am making decisions for unit id 2
(Player) (Archer) Looking for targets in attack range...
(Player) (Archer) No targets in attack range. Lookign for targets in move-attack range...
(Player) (Archer) No targets in move-attack range. Looking for distant enemy workers...
(Player) (Archer) Did not find workers. Looking for other targets...
(Player) (Archer) Found target. Calculating path...
(Player) Consulting BFS
(Player) BFS-directed move.
(Player) I am finished.
(Mediator) Elapsed time 7 ms
(Mediator) Player 1 submitted orders.
(Mediator) Unit with id 0 (base) received order to build W.
(Mediator) Unit with id 2 (archer) received order to move from 1 24 to 1 22 (distance 2)
```

To enable debug mode, modify `src/mediator/defaults.h` and add

```cpp
#define DEBUG_TRUE
```

To enable player verbosity, modify `src/player/defaults.h` and add

```cpp
#define VERBOSE_TRUE
```

## Testing

Both mediator and player scripts contain some unit tests.

```bash
usr@host:~$ ./bin/player
(Player) io.h get_map() wrong address false return test PASSED
(Player) io.h get_map() wrong address empty grid test PASSED
(Player) io.h get_status() wrong address false return test PASSED
(Player) io.h get_status() wrong address unmodified gold test PASSED
(Player) io.h get_status() wrong address unmodified listUnit test 1 PASSED
(Player) io.h get_status() wrong address unmodified listUnit test 2 PASSED
...
```

Their results can be inspected by adding in the respective `defaults.h` file

```cpp
#define TESTING_TRUE
```

## License

[GPL3](https://www.gnu.org/licenses/gpl-3.0.html)