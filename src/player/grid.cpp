#include "grid.h"

bool gridObj::checkTrav()
{
    return isTraversable;
}

int gridObj::checkVal()
{
    return value;
}

void gridObj::addUnit(std::unique_ptr<Unit> &newUnitPtr)
{
    units.push_back(std::move(newUnitPtr));
}

void gridObj::setTrav(bool newTrav)
{
    isTraversable = newTrav;
}

void gridObj::removeUnit(int pos)
{
    if (pos < units.size())
    {
        if (pos != units.size() - 1)
        {
            units[pos] = std::move(units.back());
        }
        units.pop_back();
    }
}

void gridObj::setVal(int newVal)
{
    value = newVal;
}

std::string emptySpace::print()
{
    return std::string("empty");
}

std::string barrier::print()
{
    return std::string("barrier");
}

gridObj::gridObj(int val, bool traversible):
    value(val), isTraversable(traversible)
{}

gridObj::~gridObj(){}

emptySpace::emptySpace():
    gridObj(1, true)
{}

emptySpace::~emptySpace(){}

barrier::barrier():
    gridObj(1000000, false)
{}

barrier::~barrier(){}