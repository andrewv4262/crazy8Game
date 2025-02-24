#include<iostream>
#include<fstream>
#include<string>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using std::string;
using std::cout;
using std::endl;
using std::cin;

bool loadDeck(Game& g){
    string filename;
    std::cout << "Choose a file to load the deck from:" << std::endl;
    std::cin >> filename;
    try{
        g.loadDeckFromFile(filename);
    }
    catch(std::runtime_error const&){
        std::cout << "The file was invalid. Aborting." << std::endl;
        return false;
    }
    return true;
}

int getPlayerCount(){
    std::cout << "Enter number of players:" << std::endl;
    int numPlayers;
    while(true){
        if((!(std::cin >> numPlayers)) || numPlayers <= 0){
            if(std::cin.fail()){
                //clear fail flag
                std::cin.clear();
                //remove non int data from any leftover outputstream
                string garbage;
                std::cin >> garbage;
            }
            std::cout << "Please enter a positive number" << std::endl;
        }
        else{
            //break out of the loop once we've read a valid number
            break;
        }
    }
    return numPlayers;
}

void setupPlayers(Game& g, int numPlayers) {
    for (int i = 0; i < numPlayers; i++) {
        std::cout << "Is player " << i << " an AI? (y/n)";
        string answer;
        cin >> answer;
        cout << endl;
        while (answer != "y" && answer != "n") {
            cout << "Please enter y or n " << endl;
            cin >> answer;
        }
        bool isAI = (answer == "y");
        g.addPlayer(isAI);
    }
}

void setupGame(Game& g){
    // TODO: Determine how many cards to deal, deal the cards, and
    // print the initial discard
    cout << "How many cards should each player start with?" << endl;
    int numCards;
    while (true) {
        if ((!(cin >> numCards)) || numCards <= 0) {
            if(cin.fail()){
                //clear fail flag
                cin.clear();
                //remove non int data from any leftover outputstream
                string garbage;
                std::cin >> garbage;
            }
        cout << "Please enter a positive number" << endl;
        }
        else {
            break; //once receive valid input
        }
    }
    Card* discardCard = g.deal(numCards);
    cout << "The initial discard is " << discardCard -> getRank() << " " << discardCard -> getSuit() << endl;
}

int main(){
    Game g;
    if(!loadDeck(g)){
        return 1;
    }
    int numPlayers = getPlayerCount();
    setupPlayers(g,numPlayers);
    setupGame(g);
    int winner = g.runGame();
    if(winner != -1){
        std::cout << "Player " << winner << " wins!" << std::endl;
    }
    else{
        std::cout << "The game is a draw!" << std::endl;
    }
    std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;
    return 0;
}