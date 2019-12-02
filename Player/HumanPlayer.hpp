#ifndef HUMANPLAYER
#define HUMANPLAYER
#include <string>
#include <iostream>
#include "Player.hpp"
#include "random.hpp"


class HumanPlayer: public Player{
public:
    virtual std::string decideRed(){
        std::cout << "Please Input Red Pattern. (Ex. ABCD)" << std::endl;
        std::string res;
        std::cin >> res;
        return res;
    }

    virtual std::string decideHand(std::string res){
        game.setState(res);
        game.printBoard();
        std::string ret;
        Unit unit;
        char direct;

        while(true){
            std::cin >> ret;
            unit = game.allUnit()[ret[0] - 'A'];
            direct = ret[1];
            if(game.canMove1st(unit, Direction(direct))){
                break;
            }
            std::cout << "It's Illegal Move! " << Hand(unit, direct).toString() << std::endl;
        }

        return Hand(unit, direct);
    }
};

#endif