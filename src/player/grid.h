#ifndef GRID_H
#define GRID_H

#include "units.h"

#include <memory>
#include <vector>
#include <string>

#define grid_row std::vector<std::unique_ptr<gridObj>>
#define grid std::vector<grid_row>                      // call with grid[y coord][x coord]

class gridObj
{
private:
    bool isTraversable;
    unitRoster units;
    int value;
public:
    gridObj(int val, bool traversible);
    ~gridObj();

    virtual std::string print() = 0;
    
    bool checkTrav();
    int checkVal();

    void addUnit(std::unique_ptr<Unit> &newUnitPtr);
    void setTrav(bool newTrav);
    void removeUnit(int pos);
    void setVal(int newVal);
};

class emptySpace : public gridObj
{
public:
    emptySpace();
    ~emptySpace();

    std::string print();
};

class barrier : public gridObj
{
public:
    barrier();
    ~barrier();

    std::string print();
};

#endif