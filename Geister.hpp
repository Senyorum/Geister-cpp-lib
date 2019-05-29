#include <array>
#include <vector>
#include <string>
#include "unit.hpp"
#include "hand.hpp"

#ifndef GEISTER
#define GEISTER

class Geister
{
    std::array<Unit, 16> units;

public:
    int takeBlue1st;
    int takeBlue2nd;
    int takeRed1st;
    int takeRed2nd;
    int turn;

    static std::vector<char> unitList;

    Geister();
    Geister(std::string info);
    Geister(std::string red1st, std::string red2nd);
    Geister(const Geister &geister);

    void setState(std::string state);

    void initialize();

    void printBoard() const;

    virtual std::array<Unit, 16>& allUnit();

    virtual bool canMove1st(Unit unit, char direct) const;

    virtual std::vector<Hand> getLegalMove1st() const;

    virtual bool canMove2nd(Unit unit, char direct) const;

    virtual std::vector<Hand> getLegalMove2nd() const;

    virtual std::string toString() const;

    virtual void take(Unit unit);

    virtual void move(char u, char direct);

    virtual double checkResult() const;

    virtual Unit* getUnitByPos(int x, int y);

    virtual Geister mask();

    virtual void changeSide();
};

#endif