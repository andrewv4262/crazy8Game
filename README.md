Introduction

This is a command-line card game implemented in C++. The game follows a turn-based structure where players attempt to play cards based on rank or suit, with a special rule for '8' cards. The game supports both human and AI players.

Files Overview

Card.h & Card.cpp: Defines the Card class, which represents a playing card. Includes properties such as rank, suit, and times played.

Player.h & Player.cpp: Implements the Player class, which represents a game participant. It manages the player's hand and gameplay actions.

Game.cpp: Implements the game logic, handling deck loading, player turns, drawing, and winning conditions.

Deck Files (colorfulDeck.txt, smallDeck.txt, standardDeck.txt): Contains pre-defined decks for gameplay, defining suits and ranks.

How to Play

The game initializes by loading a deck from a file.

Players take turns playing a card that matches the current rank or suit of the top discard pile card.

If a player cannot play a card, they must draw from the draw pile.

Special Rule: Playing an '8' allows the player to choose the next suit.

The game continues until a player runs out of cards, making them the winner.

Running the Game

To compile and run the game, use the following commands:

 g++ -o game Card.cpp Player.cpp Game.cpp -std=c++11
 ./game

Features

Turn-based gameplay

AI opponents

Different deck options

Special mechanics for '8' cards

Future Improvements

More advanced AI decision-making

Enhanced user interface

Additional game variations

Author

[Your Name]

