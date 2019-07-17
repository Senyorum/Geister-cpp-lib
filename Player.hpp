#include "hand.hpp"
#include "Geister.hpp"
#include <string>
#include <vector>

#ifndef PLAYER
#define PLAYER

#ifndef PLAYER_NAME
#define PLAYER_NAME No_Name
#endif
#define STRING(str) STRING_(str)
#define STRING_(str) #str

class Player{
protected:
    Geister game;
    constexpr static std::array<char*, 70> pattern = {
        "ABCD", "ABCE", "ABCF", "ABCG", "ABCH", "ABDE", "ABDF",
        "ABDG", "ABDH", "ABEF", "ABEG", "ABEH", "ABFG", "ABFH",
        "ABGH", "ACDE", "ACDF", "ACDG", "ACDH", "ACEF", "ACEG",
        "ACEH", "ACFG", "ACFH", "ACGH", "ADEF", "ADEG", "ADEH",
        "ADFG", "ADFH", "ADGH", "AEFG", "AEFH", "AEGH", "AFGH",
        "BCDE", "BCDF", "BCDG", "BCDH", "BCEF", "BCEG", "BCEH",
        "BCFG", "BCFH", "BCGH", "BDEF", "BDEG", "BDEH", "BDFG",
        "BDFH", "BDGH", "BEFG", "BEFH", "BEGH", "BFGH", "CDEF",
        "CDEG", "CDEH", "CDFG", "CDFH", "CDGH", "CEFG", "CEFH",
        "CEGH", "CFGH", "DEFG", "DEFH", "DEGH", "DFGH", "EFGH"
    };
public:

    virtual std::string name(){
        return STRING(PLAYER_NAME);
    }

    virtual std::string decideHand(std::string res) = 0;
    virtual std::string decideRed() = 0;
    virtual std::vector<Hand> candidateHand(){
        return game.getLegalMove1st();
    }
};

#endif