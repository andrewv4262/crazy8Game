#include<iostream>
#include<sstream>
#include "Player.h"

using std::vector, std::string, std::size_t, std::cout, std::endl, std::cin;

Player::Player(bool isAI) : isAI(isAI), hand() {}

void Player::addToHand(Card* c){
    // TODO: Add the card c to the player's hand
    hand.push_back(c);
}

size_t Player::getHandSize(){
    // TODO: Implement getter
    return hand.size();
}

std::string Player::getHandString(){
    string handString = "";
    for (size_t i = 0; i < hand.size(); i++) {
        if (i != hand.size() - 1) 
        {
        handString += hand[i] -> getRank() + " " + hand[i] -> getSuit() + ", ";
        }
        else {
            handString += hand[i] -> getRank() + " " + hand[i] -> getSuit();
        }
    }
    return handString;

}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  string playerRank;
  string playerSuit;

  if (!isAI) {
    std::cout << "Your hand contains: " << getHandString() << std::endl;
    std::cout << "The next card played must be a " << currentRank << " or " << currentSuit << std::endl;
    std::cout << "What would you like to play? (enter \"draw card\" to draw a card)" << std::endl;
    while (true) {
      bool cardFound = false;
      std::cin >> playerRank;
      if (playerRank == "draw") {
        std::string temp;
        std::cin >> temp;
        return nullptr;
      }
      std::cin >> playerSuit;
      //find card in hand
      for (size_t i = 0; i < hand.size(); i++) {
        if (hand[i]->getRank() == playerRank && hand[i]->getSuit() == playerSuit) {
            cardFound = true;
          //check if card can be played
          if (hand[i]->getRank() == currentRank || hand[i]->getSuit() == currentSuit || hand[i]->getRank() == "8") {
            Card* playedCard = hand[i];
            hand.erase(hand.begin() + i);
            playedCard->play();
            if (playedCard->getRank() == "8") {
              std::cout << "What suit would you like to declare?" << endl;
              while (true) {
                std::cin >> currentSuit;
                bool validSuit = false;
                for (const string& s : suits) {
                  if (s == currentSuit) {
                    validSuit = true;
                    break;
                  }
                }
                if (validSuit) {
                  break;
                }
                std::cout << "That's not a suit in this deck. Try again." << std::endl;
              }
              currentRank = "8";
            } 
            else {
              currentRank = playedCard->getRank();
              currentSuit = playedCard->getSuit();
            }
            return playedCard;
          }
          else { //card is found but invalid
          std::cout << "You can't play that card. Try again." << std::endl;
          }
        }
      }
      if (!cardFound) { //card not found
      std::cout << "That's not a card you have. Try again." << std::endl;
      }
    }
  } else {
     for (size_t i = 0; i < hand.size(); i++) {
      if (hand[i]->getRank() == currentRank || hand[i]->getSuit() == currentSuit || hand[i]->getRank() == "8") {
        Card* playedCard = hand[i];
        hand.erase(hand.begin() + i);
        playedCard->play();
        if (playedCard->getRank() == "8") {
          currentRank = "8";
          currentSuit = playedCard->getSuit();
        } else {
          currentRank = playedCard->getRank();
          currentSuit = playedCard->getSuit();
        }
        return playedCard;
      }
    }
    return nullptr;
  }
}