#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <vector>
#include "card.h"

using namespace std;

class player
{
protected:
	//list of player variables
	string playerName;
	int playerScore;
	vector <card> playerCardDeck;
	bool playerStatus;
	

public:

	//default constructor
	player();
	
	player(string name);
	

	~player();


	//adds a card to the player deck
	void addCardToDeck(card deckCard);

	//clears the player card deck
	void clearPlayerDeck();

	//returns the name of the player
	string getName();

	//returns score of the player
	int getScore();

	//returns latest card value in player deck
	int returnLatestPlayerCardValue();

	//return one card before the latest card
	int returnBeforeLatestCardValue();

	//returns the lowest card in player deck
	int returnLowest();

	//outputs the deck of players
	void displayPlayerDeck();
	
	//changes player score
	void updateScore(int num);

	//checks if the player deck has any pairs
	bool checkPairs(int num);

	//changes status of all the cards in the player deck to "inDeck"
	void changeDeckCardStatus();

	//checks if the cards are within the deck
	bool withinPlayerDeck(int num);

	//returns the number of cards in the player deck
	int getNumCards();
};




#endif