#include "Geister.hpp"
#include "unit.hpp"
#include "Simulator.hpp"
#include <array>
#include <algorithm>
#include <map>


Simulator::Simulator(): geister(), mt(rd()){
    depth = 0;
    setColorRandom();
    initBoard();
}

Simulator::Simulator(const Geister& g): geister(g), mt(rd()){
    depth = 0;
    initBoard();
    setColorRandom();
}

Simulator::Simulator(const Geister& g, std::string ptn): geister(g), mt(rd()){
    depth = 0;
    constexpr int l2s = 'a' - 'A';
    if(ptn.size() == 4){
        for(int u = 8; u < 16; ++u){
            for(int c = 0; c < ptn.size(); ++c){
                if((ptn[c] + l2s) == geister.allUnit()[u].name){
                    geister.allUnit()[u].color = UnitColor(3);
                    break;
                }
            }
            if(geister.allUnit()[u].color.toInt() != 3)
                geister.allUnit()[u].color = UnitColor(1);
        }
    }
    else{
        setColorRandom();
    }
    initBoard();
}

void Simulator::init(const Geister& g){
    geister = g;
    mt = std::mt19937(rd());
    depth = 0;
    setColorRandom();
    initBoard();
}

void Simulator::init(const Geister& g, std::string ptn){
    geister = g;
    mt = std::mt19937(rd());
    depth = 0;
    for(int u = 0; u < 8; ++u){
        if(ptn.find(std::toupper(geister.allUnit()[u+8].name)) != std::string::npos)
            geister.allUnit()[u+8].color = UnitColor::red;
        else
            geister.allUnit()[u+8].color = UnitColor::blue;
    }
    if(ptn.size() < 4){
        setColorRandom();
    }

    initBoard();
}
    
// 未判明の相手駒色を適当に仮定
void Simulator::setColorRandom(){
    std::uniform_int_distribution<int> BorR(0,1);
    int assumeTakeBlue = 4;
    int assumeTakeRed = 4;
    for(int i = 8; i < 16; ++i){
        auto color = geister.allUnit()[i].color;
        if(color == UnitColor::blue)
            assumeTakeBlue -= 1;
        if(color == UnitColor::red)
            assumeTakeRed -= 1;
    }
    for(int i = 8; i < 16; ++i){
        if(geister.allUnit()[i].color == UnitColor::unknown){
            if(assumeTakeRed == 0){
                geister.allUnit()[i].color = UnitColor::blue;
                assumeTakeBlue -= 1;
            }
            else if(assumeTakeBlue == 0){
                geister.allUnit()[i].color = UnitColor::red;
                assumeTakeRed -= 1;
            }
            else{
                if(BorR(mt)){
                    geister.allUnit()[i].color = UnitColor::blue;
                    assumeTakeBlue -= 1;
                }
                else{
                    geister.allUnit()[i].color = UnitColor::red;
                    assumeTakeRed -= 1;
                }
            }
        }
    }
}
    
double Simulator::playout(){
    while(true){
        if(geister.checkResult() != 0)
            break;
        // 相手の手番
        auto lm = geister.getLegalMove2nd();
        std::uniform_int_distribution<int> selector1(0, lm.size() - 1);
        auto m = lm[selector1(mt)];
        geister.move(m);
        if(geister.checkResult() != 0)
            break;
        // 自分の手番
        lm = geister.getLegalMove1st();
        std::uniform_int_distribution<int> selector2(0, lm.size() - 1);
        m = lm[selector2(mt)];
        geister.move(m);
    }
    return evaluate();
}

double Simulator::run(){
    Geister root = geister;
    double result = playout();
    geister = root;
    return result;
}

double Simulator::run(int count){
    Geister root = geister;
    double result = 0.0;
    for(int i = 0; i < count; ++i){
        result += playout();
        geister = root;
    }
    return result;
}

void Simulator::initBoard(){
    geister.takeBlue1st = 0;
    geister.takeRed1st = 0;
    geister.takeBlue2nd = 0;
    geister.takeRed2nd = 0;

    for(auto u: geister.allUnit()){
        if(u.isTaken()){
            if(u.color == UnitColor::Blue) geister.takeBlue1st += 1;
            else if(u.color == UnitColor::blue) geister.takeBlue2nd += 1;
            else if(u.color == UnitColor::Red) geister.takeRed1st += 1;
            else if(u.color == UnitColor::red) geister.takeRed2nd += 1;
        }
    }
}
