#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) {
    bool rankAlpha = true;
    bool suitAlpha = true;
    for (char c : rank) {
        if (!isalnum(c)) {
            rankAlpha = false;
            break;
        }
    }
    for (char c : suit) {
        if (!isalnum(c)) {
            suitAlpha = false;
                break;
            }
        }
    if (rank.length() == 0 || suit.length() == 0 || !rankAlpha || !suitAlpha) {
        throw std::invalid_argument("rank/suit is either empty or invalid");
    }
}

string Card::getRank(){
    return rank;
}

string Card::getSuit(){
    return suit;
}

int Card::getTimesPlayed(){
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    if ((rank == currentRank || suit == currentSuit) || rank == "8") {
        return true;
    }
    else {
        return false;
    }
    // TODO: return whether or not the card can legally be played
}

void Card::play(){
    timesPlayed++;
}