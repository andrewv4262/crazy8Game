#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector, std::ifstream, std::istringstream, std::cout, std::endl, std::cin;

Game::Game(): players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    string line;
    getline(file, line);
    istringstream suitStream(line);
    string suit;
    while (suitStream >> suit) {
        suits.push_back(suit);
    }
    getline(file, line);
    istringstream rankStream(line);
    string rank;
    while (rankStream >> rank) {
        ranks.push_back(rank);
    }
    while (getline(file, line)) {
        istringstream cardStream(line);
        string cardRank, cardSuit;
        
        if (!(cardStream >> cardRank >> cardSuit) || cardStream >> suit) {
            throw std::runtime_error("Invalid card format");
        }
        bool validRank = false, validSuit = false;
        for (string& rank : ranks) {
            if (rank == cardRank) {
                validRank = true;
        }
        }
        for (string& suit : suits) {
            if (suit == cardSuit) {
                validSuit = true;
            }
        }
        if (!validRank || !validSuit) {
            throw std::runtime_error("Invalid rank or suit");
        }
        try { //try catch invalid arg as doc specifies
            Card* card = new Card(cardRank, cardSuit);
            deck.push_back(card);
            drawPile.insert(drawPile.begin(), card);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error("Invalid card");
        }
    }
}

void Game::addPlayer(bool isAI) { // add the playa to the game
    Player* player = new Player(isAI);
    players.push_back(player);
}

void Game::drawCard(Player* p) {
    if (drawPile.empty()) {
        if (discardPile.size() <= 1) {
            throw std::runtime_error("No cards to draw");
        }
        std::cout << "Draw pile, empty, flipping the discard pile." << std::endl;
        Card* topCard = discardPile.back();
        //move all but top card to draw pile in reverse order
        for (int i = discardPile.size() - 2; i >= 0; i--) {
            drawPile.push_back(discardPile[i]);
        }
        
        discardPile.clear();
        discardPile.push_back(topCard);
    }
    Card* card = drawPile.back();
    drawPile.pop_back();
    p->addToHand(card);
}

Card* Game::deal(int numCards) {
    Card* discardCard = drawPile.back();
    drawPile.pop_back();
    discardPile.push_back(discardCard);
    for (int i = 0; i < numCards; i++) {
        for (Player* player : players) {
            drawCard(player);
        }
    }
    return discardCard;
}

string Game::mostPlayedSuit() {
    vector<int> suitCounter(suits.size(), 0);
    for (size_t i = 0; i < suits.size(); i++) {
        for (Card* card : deck) {
            if (card->getSuit() == suits[i]) {
                suitCounter[i] += card->getTimesPlayed();
            }
        }
    }
    int maxCount = 0;
    size_t maxIndex = 0;
    for (size_t i = 0; i < suitCounter.size(); i++) {
        if (suitCounter[i] > maxCount) {
            maxCount = suitCounter[i];
            maxIndex = i;
        }
    }
    return suits[maxIndex];
}

int Game::runGame() {
     string currentRank = discardPile.back()->getRank();
     string currentSuit = discardPile.back()->getSuit();
    while (true) {
        for (size_t i = 0; i < players.size(); i++) {
            std::cout << "Player " << i << "'s turn!" << std::endl;
            Card* playedCard = players[i]->playCard(suits, currentRank, currentSuit);
            if (playedCard == nullptr) {
                try {
                    drawCard(players[i]);
                    std::cout << "Player " << i << " draws a card." << std::endl;
                } catch (const std::runtime_error&) {
                    std::cout << "Player " << i << " cannot draw a card." << std::endl;
                    return -1; //exit program
                }
            } else {
                 if (playedCard->getRank() == "8") {
                    std::cout << "Player " << i << " plays " << playedCard->getRank()  << " " << playedCard->getSuit() << " and changes the suit to " << currentSuit << "." << endl;
                }
                else {
                    std::cout << "Player " << i << " plays " << playedCard->getRank()  << " " << playedCard->getSuit() << "." << std::endl;
                }
               
                discardPile.push_back(playedCard);
                if (players[i]->getHandSize() == 0) {
                    return i;
                }
            }
        }
    }
}
//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}