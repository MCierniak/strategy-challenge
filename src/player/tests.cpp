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

#include "tests.h"

void test_io_get_map()
{
    // Test wrong input address.
    // Desired result is an empty grid object and false return.
    grid test;
    int X, Y;
    bool testReturn = get_map("wrong address", test, X, Y);
    std::cout << RESET << "(Player) io.h get_map() wrong address false return test ";
    if (!testReturn)
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
    std::cout << RESET << "(Player) io.h get_map() wrong address empty grid test ";
    if (test == grid())
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
}

void test_io_get_status()
{
    // Test wrong input address.
    // Desired result will have unmodified objects and false return.
    listUnits test1, test2;
    grid testMap;
    long testGold = 0;
    bool testReturn = get_status("wrong address", testMap, testGold, test1, test2);
    std::cout << RESET << "(Player) io.h get_status() wrong address false return test ";
    if (!testReturn)
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
    std::cout << "(Player) io.h get_status() wrong address unmodified gold test ";
    if (testGold == 0)
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
    std::cout << "(Player) io.h get_status() wrong address unmodified listUnit test 1 ";
    if (
        test1.qArcher == 0 && \
        test1.qCatapult == 0 && \
        test1.qKnight == 0 && \
        test1.qPikeman == 0 && \
        test1.qRam == 0 && \
        test1.qSwordsman == 0 &&
        test1.qWorker == 0
    )
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
    std::cout << "(Player) io.h get_status() wrong address unmodified listUnit test 2 ";
    if (
        test2.qArcher == 0 && \
        test2.qCatapult == 0 && \
        test2.qKnight == 0 && \
        test2.qPikeman == 0 && \
        test2.qRam == 0 && \
        test2.qSwordsman == 0 &&
        test2.qWorker == 0
    )
    {
        std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    }
    else
    {
        std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    }
}

void test_units_units_worker_find_target()
{
    // Test worker behavior when looking for resource nodes
    listUnits oneWorker, zeroEnemies;
    grid_row temp;
    grid map;

    // Define a 3x3 grid with a central resource node
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));
    temp = grid_row();
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<resource>(1, 1));
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));
    temp = grid_row();
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));

    // Add a worker on top fo the resource node
    oneWorker.addUnit('W', 0, 20, 1, 1);
    map[1][1]->addWorkerId(0);

    // The find_target() method should return false with worker trgtX/trgtY variables pointing at (1,1)
    std::cout << RESET << "(Player) units/units.h Worker::find_target() resource in place return test ";
    if(!(oneWorker.units[0]->find_target(map, oneWorker, zeroEnemies))) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    std::cout << "(Player) units/units.h Worker::find_target() resource in place location test ";
    if (oneWorker.units[0]->trgtX == 1 && oneWorker.units[0]->trgtY == 1) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Reset grid
    map = grid();
    temp = grid_row();

    // Define a 3x3 grid with a resource node at one side
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<resource>(1, 0));
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));
    temp = grid_row();
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));
    temp = grid_row();
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    temp.push_back(std::make_unique<emptySpace>());
    map.push_back(std::move(temp));
    map[1][1]->addWorkerId(0);

    // The find_target() method should return true with worker trgtX/trgtY variables pointing at (1,0)
    std::cout << RESET << "(Player) units/units.h Worker::find_target() resource in range return test ";
    if(!(oneWorker.units[0]->find_target(map, oneWorker, zeroEnemies))) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    std::cout << "(Player) units/units.h Worker::find_target() resource in range location test ";
    if (oneWorker.units[0]->trgtX == 1 && oneWorker.units[0]->trgtY == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_units_actions_action_unit()
{
    // Test unit behavior when enemies are nearby
    listUnits oneSwordsman, oneEnemy;
    grid_row temp;
    grid map;

    // Define a 5x5 empty grid
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    // Add own base at (0,0) and a swordsman at (1,1)
    oneSwordsman.addBase(0, 200, 0, 0, '0');
    oneSwordsman.addUnit('S', 2, 100, 1, 1);

    // Add enemy base at (4,4) and swordsman at (3,1), within move-attack range
    oneEnemy.addBase(1, 200, 4, 4, '0');
    map[4][4]->addEnemyId(1);
    oneEnemy.addSwordsman(3, 100, 3, 1);
    map[1][3]->addEnemyId(3);

    // Sort the enemy hitList
    oneEnemy.hitList.sort(
        [&oneSwordsman, &oneEnemy](const int &a, const int &b)
        {
            int base_posx = oneSwordsman.base.posx;
            int base_posy = oneSwordsman.base.posy;

            int unita_posx, unita_posy, unitb_posx, unitb_posy;
            if (oneEnemy.id2type[a] == 'B')
            {
                unita_posx = oneEnemy.base.posx;
                unita_posy = oneEnemy.base.posy;
            }
            else
            {
                unita_posx = oneEnemy.units[a]->posx;
                unita_posy = oneEnemy.units[a]->posy;
            }
            if (oneEnemy.id2type[b] == 'B')
            {
                unitb_posx = oneEnemy.base.posx;
                unitb_posy = oneEnemy.base.posy;
            }
            else
            {
                unitb_posx = oneEnemy.units[b]->posx;
                unitb_posy = oneEnemy.units[b]->posy;
            }
            return (Dist(base_posx, base_posy, unita_posx, unita_posy) < Dist(base_posx, base_posy, unitb_posx, unitb_posy));
        }
    );

    // Test if the swordsman will attempt a move-attack combination (return should be true)
    std::string payload;
    std::cout << RESET << "(Player) units/actions.h action_unit() Swordsman move attack return test ";
    if (!action_unit(payload, 2, map, oneSwordsman, oneEnemy)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;

    // Test if the swordsman will attempt a move-attack combination (order should be to move to (2,1) and attack)
    std::cout << RESET << "(Player) units/actions.h action_unit() Swordsman move attack command test ";
    std::string correct_order("2 M 2 1\n2 A 3\n");
    if (payload == correct_order) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Move the swordsman back to starting point, make tile (2,1) a barrier
    oneSwordsman.units[2]->posx = 1;
    oneSwordsman.units[2]->posy = 1;
    map[1][2] = std::make_unique<barrier>();
    payload = std::string();

    // Test if the swordsman will attempt to move arround the obstackle.
    std::cout << RESET << "(Player) units/actions.h action_unit() Swordsman move attack blocked command test ";
    if (!action_unit(payload, 2, map, oneSwordsman, oneEnemy)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else if (payload == std::string("2 M 1 0\n") || payload == std::string("2 M 3 0\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Move the swordsman back to starting point, add an extra swordsman at (1,3), within move-attack in a different direction. Do not sort the hitList!
    oneSwordsman.units[2]->posx = 1;
    oneSwordsman.units[2]->posy = 1;
    oneEnemy.addSwordsman(4, 100, 1, 3);
    map[3][1]->addEnemyId(4);
    payload = std::string();

    // Test if the swordsman will skip hitList order to attack an enemy in move-attack range
    std::cout << RESET << "(Player) units/actions.h action_unit() Swordsman move attack 2 blocked command test ";
    if (!action_unit(payload, 2, map, oneSwordsman, oneEnemy)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else if (payload == std::string("2 M 1 2\n2 A 4\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Move the swordsman back to starting point, add an extra dead enemy swordsman next tile over
    oneSwordsman.units[2]->posx = 1;
    oneSwordsman.units[2]->posy = 1;
    oneEnemy.addSwordsman(5, 0, 1, 0);
    map[3][1]->addEnemyId(5);
    payload = std::string();

    // Test if swordsman will ignore the dead enemy
    std::cout << RESET << "(Player) units/actions.h action_unit() Swordsman move attack 3 dead command test ";
    if (!action_unit(payload, 2, map, oneSwordsman, oneEnemy)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else if (payload == std::string("2 M 1 2\n2 A 4\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    temp = grid_row();
    map = grid();
}

void test_main_resNodeList_sort()
{
    // Test if resNodeList is correctly sorted by distance to base
    listUnits justBase;
    justBase.addBase(0, 200, 0, 0, '0');

    grid_row temp;
    grid map;

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if (i == 0 && j == 0) temp.push_back(std::make_unique<emptySpace>());
            else temp.push_back(std::make_unique<resource>(j, i));
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    resource::resNodeList.sort(
        [&justBase](const std::vector<int> &first, const std::vector<int> &second)
        { 
            int baseX = justBase.base.posx, baseY = justBase.base.posy;
            return (Dist(baseX, baseY, first[1], first[0]) < Dist(baseX, baseY, second[1], second[0]));
        }
    );
    std::vector<int> first = resource::resNodeList.front(), last = resource::resNodeList.back();
    bool test = (((first[0] == 0) && (first[1] == 1)) || ((first[0] == 1) && (first[1] == 0))) && (last[0] == 4) && (last[1] == 4);

    std::cout << RESET << "(Player) grid.h resource::resNodeList sort test ";
    if (test) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_units_misc_listUnits()
{
    // test listUnits struct behavior
    listUnits justBase, lotsOfEnemies;

    // Add a lot of enemies
    justBase.addBase(0, 200, 0, 0, '0');
    lotsOfEnemies.addBase(1, 200, 4, 4, '0');
    lotsOfEnemies.addUnit('S', 2, 100, 0, 1);
    lotsOfEnemies.addUnit('S', 3, 100, 1, 0);
    lotsOfEnemies.addUnit('S', 4, 100, 1, 1);
    lotsOfEnemies.addUnit('S', 5, 100, 1, 2);
    lotsOfEnemies.addUnit('S', 6, 100, 2, 1);
    lotsOfEnemies.addUnit('S', 7, 100, 2, 2);
    lotsOfEnemies.addUnit('S', 8, 100, 2, 3);
    lotsOfEnemies.addUnit('S', 9, 100, 3, 2);
    lotsOfEnemies.addUnit('S', 10, 100, 3, 3);
    lotsOfEnemies.addUnit('S', 11, 100, 3, 4);
    lotsOfEnemies.addUnit('S', 12, 100, 4, 3);

    // Sort the enemy hitList
    lotsOfEnemies.hitList.sort(
        [&justBase, &lotsOfEnemies](const int &a, const int &b)
        {
            int base_posx = justBase.base.posx;
            int base_posy = justBase.base.posy;

            int unita_posx, unita_posy, unitb_posx, unitb_posy;
            if (lotsOfEnemies.id2type[a] == 'B')
            {
                unita_posx = lotsOfEnemies.base.posx;
                unita_posy = lotsOfEnemies.base.posy;
            }
            else
            {
                unita_posx = lotsOfEnemies.units[a]->posx;
                unita_posy = lotsOfEnemies.units[a]->posy;
            }
            if (lotsOfEnemies.id2type[b] == 'B')
            {
                unitb_posx = lotsOfEnemies.base.posx;
                unitb_posy = lotsOfEnemies.base.posy;
            }
            else
            {
                unitb_posx = lotsOfEnemies.units[b]->posx;
                unitb_posy = lotsOfEnemies.units[b]->posy;
            }
            return (Dist(base_posx, base_posy, unita_posx, unita_posy) < Dist(base_posx, base_posy, unitb_posx, unitb_posy));
        }
    );

    int first = lotsOfEnemies.hitList.front(), last = lotsOfEnemies.hitList.back();
    bool test = ((lotsOfEnemies.units[first]->posx == 0 && lotsOfEnemies.units[first]->posy == 1) ||
                (lotsOfEnemies.units[first]->posx == 1 && lotsOfEnemies.units[first]->posy == 0)) &&
                lotsOfEnemies.id2type[last] == 'B';

    // Test if hitList is correctly sorted
    std::cout << RESET << "(Player) units/misc.h listUnits.hitList sort test ";
    if (test) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Test if struct ensures id uniqness
    std::cout << RESET << "(Player) units/misc.h listUnits.units unique id test ";
    if(!lotsOfEnemies.addUnit('S', 2, 100, 0, 1)) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_units_actions_evade()
{
    // Test the behavior of evade() strategy for workers
    evade_queue eQ;
    eQ.push(evade_queue_item(5, coord(1, 4)));
    eQ.push(evade_queue_item(4, coord(2, 5)));
    eQ.push(evade_queue_item(1, coord(5, 3)));
    eQ.push(evade_queue_item(2, coord(4, 2)));
    eQ.push(evade_queue_item(3, coord(3, 1)));

    // Check if evade_queue sorts correctly
    std::cout << RESET << "(Player) units/actions.h evade_queue sort test ";
    if(eQ.top().first == 1 && eQ.top().second.first == 5 && eQ.top().second.second == 3) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    // Add an evasive worker
    listUnits evasiveWorker;
    evasiveWorker.addBase(0, 200, 0, 0, '0');
    evasiveWorker.addUnit('W', 1, 20, 4, 4);

    grid map;
    grid_row temp;

    // Build a grid with incremented damage flags
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
            temp.back()->addDmg('W', 1 + i*j);
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    // Test if the worker tries to evade towards lower damage flags
    std::cout << RESET << "(Player) units/actions.h evade() return test ";
    std::string payload;
    if(!evade(payload, 1, map, evasiveWorker)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;

    std::cout << RESET << "(Player) units/actions.h evade() target test ";
    if (payload == std::string("1 M 4 2\n") || payload == std::string("1 M 2 4\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    // Test if worker will stay in place if standing at lowest dmg grid point
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
            if (i == 4 && j == 4) temp.back()->addDmg('W', 1);
            else temp.back()->addDmg('W', 2);
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    payload = std::string();
    evasiveWorker.units[1]->posx = 4;
    evasiveWorker.units[1]->posy = 4;
    std::cout << RESET << "(Player) units/actions.h evade() in place test ";
    if (evade(payload, 1, map, evasiveWorker)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
}

void test_units_actions_attack()
{
    // Test the behavior of attack() strategy
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> hpSort;
    hpSort.push(std::pair<int, int>(20, 0));
    hpSort.push(std::pair<int, int>(10, 1));
    hpSort.push(std::pair<int, int>(30, 2));
    hpSort.push(std::pair<int, int>(20, 3));
    hpSort.push(std::pair<int, int>(5, 4));
    hpSort.push(std::pair<int, int>(120, 5));
    hpSort.push(std::pair<int, int>(220, 6));
    hpSort.push(std::pair<int, int>(320, 7));

    // Test if the attack priority_queue works as expected
    std::cout << RESET << "(Player) units/actions.h attack() sort test ";
    if (hpSort.top().first == 5 && hpSort.top().second == 4) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    grid map;
    grid_row temp;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    listUnits mySwordsman, enemies;
    mySwordsman.addBase(0, 200, 1, 1, '0');
    mySwordsman.addUnit('S', 1, 10, 1, 1);
    enemies.addBase(2, 10, 2, 1, '0');
    map[1][2]->addEnemyId(2);
    enemies.addUnit('W', 3, 11, 2, 1);
    map[1][2]->addEnemyId(3);
    enemies.addUnit('W', 4, 20, 1, 2);
    map[2][1]->addEnemyId(4);
    enemies.addUnit('W', 5, 30, 0, 1);
    map[1][0]->addEnemyId(5);
    enemies.addUnit('W', 6, 25, 1, 0);
    map[0][1]->addEnemyId(6);

    // Test if the unit will attack the enemy base
    std::cout << RESET << "(Player) units/actions.h attack() target base return test ";
    std::string payload;
    if (!attack(payload, 1, map, mySwordsman, enemies)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;

    std::cout << RESET << "(Player) units/actions.h attack() target base test ";
    if (payload == std::string("1 A 2\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    mySwordsman = listUnits();
    enemies = listUnits();
    mySwordsman.addBase(0, 200, 1, 1, '0');
    mySwordsman.addUnit('S', 1, 10, 1, 1);
    enemies.addBase(2, 200, 2, 1, '0');
    map[1][2]->addEnemyId(2);
    enemies.addUnit('W', 3, 11, 2, 1);
    map[1][2]->addEnemyId(3);
    enemies.addUnit('W', 4, 20, 1, 2);
    map[2][1]->addEnemyId(4);
    enemies.addUnit('W', 5, 30, 0, 1);
    map[1][0]->addEnemyId(5);
    enemies.addUnit('W', 6, 25, 1, 0);
    map[0][1]->addEnemyId(6);

    // Test if the unit will attack the enemy unit
    std::cout << RESET << "(Player) units/actions.h attack() target unit return test ";
    payload = std::string();
    if (!attack(payload, 1, map, mySwordsman, enemies)) std::cout << BOLDRED << "FAILED" << RESET << std::endl;
    else std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;

    std::cout << RESET << "(Player) units/actions.h attack() target unit test ";
    if (payload == std::string("1 A 3\n")) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_grid_addId()
{
    // Test the behavior of gridObj method addEnemyId() and addWorkerId()
    grid map;
    grid_row temp;

    // Create a grid with 1 element, add multiple enemies with the same id
    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[0][0]->addEnemyId(i);
        }
    }

    // Check if only unique ids are added by addEnemyId()
    std::cout << RESET << "(Player) grid.h gridObj::addEnemyId() uniqness test ";
    if (map[0][0]->getEnemyId() == std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} && !(map[0][0]->checkTrav())) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            temp.push_back(std::make_unique<emptySpace>());
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[0][0]->addWorkerId(i);
        }
    }

    // Check if only unique ids are added by addWorkerId()
    std::cout << RESET << "(Player) grid.h gridObj::addWorkerId() uniqness test ";
    if (map[0][0]->getWorkerId() == std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            temp.push_back(std::make_unique<resource>(i, j));
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[0][0]->addEnemyId(i);
        }
    }

    // Repeat above tests for resource class implementation of addEnemyId() and addWorkerId()
    std::cout << RESET << "(Player) grid.h resource::addEnemyId() uniqness test ";
    if (
        map[0][0]->getEnemyId() == std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} && 
        resource::getUnusedResourceCount() == 0 && !(map[0][0]->checkTrav())
    ) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 1; i++)
    {
        for(int j = 0; j < 1; j++)
        {
            temp.push_back(std::make_unique<resource>(i, j));
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[0][0]->addWorkerId(i);
        }
    }

    std::cout << RESET << "(Player) grid.h resource::addWorkerId() uniqness test ";
    if (
        map[0][0]->getWorkerId() == std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} &&
        resource::getUnusedResourceCount() == 0
    ) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            temp.push_back(std::make_unique<resource>(i, j));
        }
        map.push_back(std::move(temp));
        temp = grid_row();
    }

    int unique_id = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j]->addWorkerId(unique_id);
            unique_id++;
        }
    }

    // Test the behavior of the static variable resource::unusedResourceCount
    std::cout << RESET << "(Player) grid.h resource::unusedResourceCount value test ";
    if (resource::getUnusedResourceCount() == 10) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_grid_resource_resNodeList()
{
    // Test the behavior of the static variable resource::resNodeList
    grid map;
    grid_row temp;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) temp.push_back(std::make_unique<resource>(i, j));
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) map[i][j] = std::make_unique<emptySpace>();
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    std::cout << RESET << "(Player) grid.h resource::resNodeList deallocation test 1 ";
    if (resource::resNodeList.size() == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) temp.push_back(std::make_unique<resource>(i, j));
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    map[1][1]->addWorkerId(0);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) map[i][j] = std::make_unique<emptySpace>();
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    std::cout << RESET << "(Player) grid.h resource::resNodeList deallocation test 2 ";
    if (resource::resNodeList.size() == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) temp.push_back(std::make_unique<resource>(i, j));
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    map[1][1]->addEnemyId(1);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) map[i][j] = std::make_unique<emptySpace>();
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    std::cout << RESET << "(Player) grid.h resource::resNodeList deallocation test 2 ";
    if (resource::resNodeList.size() == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;

    map = grid();
    temp = grid_row();

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) temp.push_back(std::make_unique<resource>(i, j));
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    map[1][1]->addWorkerId(2);
    map[1][1]->removeWorkerId(2);
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) map[i][j] = std::make_unique<emptySpace>();
        map.push_back(std::move(temp));
        temp = grid_row();
    }
    std::cout << RESET << "(Player) grid.h resource::resNodeList deallocation test 3 ";
    if (resource::resNodeList.size() == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}

void test_path_dijkstra_priority_queue()
{
    // Test the behavior of the priority_queue used in dijkstra algorithm.
    // Not important, the dijkstra algorithm is not used due to speed problems
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator> gridQ;
    gridQ.push(std::vector<int>{1, 5, 5});
    gridQ.push(std::vector<int>{2, 4, 4});
    gridQ.push(std::vector<int>{3, 3, 0});
    gridQ.push(std::vector<int>{4, 2, 1});
    gridQ.push(std::vector<int>{5, 1, 2});

    std::cout << RESET << "(Player) path/dijkstra.h priority_queue sort test ";
    if (gridQ.top()[0] == 3 && gridQ.top()[1] == 3 && gridQ.top()[2] == 0) std::cout << BOLDGREEN << "PASSED" << RESET << std::endl;
    else std::cout << BOLDRED << "FAILED" << RESET << std::endl;
}