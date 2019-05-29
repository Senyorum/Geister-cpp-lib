#include "hand.hpp"
#include "Geister.hpp"
#include <string>

#ifndef PLAYER
#define PLAYER

class Player{
public:
    virtual std::string decideHand(std::string res) = 0;
    virtual std::string decideRed() = 0;
};

#endif