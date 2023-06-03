#ifndef UNITS_H
#define UNITS_H

#define unitRoster std::vector<std::unique_ptr<Unit>>

class Unit
{
private:
    /* data */
public:
    Unit(/* args */);
    ~Unit();
};

// class object
// {
// protected:
//     int y, x;
// public:
//     object(int y_coord, int x_coord);
//     object(object &other);
//     ~object();
//     virtual std::string print() = 0;
// };

// class emptySpace : public object
// {
// private:
//     /* data */
// public:
//     emptySpace(int y_coord, int x_coord);
//     emptySpace(emptySpace &other);
//     ~emptySpace();
//     std::string print();
// };

// class obstacle : public object
// {
// private:
//     /* data */
// public:
//     obstacle(int y_coord, int x_coord);
//     ~obstacle();
// };

// obstacle::obstacle(int y_coord, int x_coord)
// {
// }

// obstacle::~obstacle()
// {
// }


#endif