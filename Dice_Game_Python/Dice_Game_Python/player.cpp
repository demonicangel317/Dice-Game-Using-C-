#include <string>
#include <vector>
#include <iostream>
#include "card.h"
#include "player.h"

using namespace std;

player:: player()
{
	playerName = " ";
	playerScore = 0;
	playerStatus = false;
}

player::player(string name)
{
	playerName = name;
	playerScore = 0;
	playerStatus = false;
}

player::~player()
{

}


//adds a card to the player deck
void player::addCardToDeck(card deckCard)
{
	playerCardDeck.push_back(deckCard);
}

//clears the player card deck
void player::clearPlayerDeck()
{
	playerCardDeck.clear();
}

//returns the name of the player
string player::getName()
{
	return playerName;
}

//returns score of the player
int player::getScore()
{
	return playerScore;
}

//returns latest card value in player deck
int player::returnLatestPlayerCardValue()
{
	int latestCardInDeck = size(playerCardDeck);
	int rank = playerCardDeck[latestCardInDeck - 1].returnCardRank();
	return rank;
}

//return one card before the latest card
int player::returnBeforeLatestCardValue()
{
	int latestCardInDeck = size(playerCardDeck);
	int rank = playerCardDeck[latestCardInDeck - 2].returnCardRank();
	return rank;
}

//returns the lowest card in player deck
int player::returnLowest()
{
	int lowest = playerCardDeck[0].returnCardRank();
	int cardRank = 0;
	for (vector<card>::iterator cardIter = playerCardDeck.begin(); cardIter != playerCardDeck.end(); cardIter++)
	{
		cardRank = cardIter->returnCardRank();
		if (cardRank < lowest)
		{
			lowest = cardRank;
		}
	}

	return lowest;
}

//outputs the deck of players
void player::displayPlayerDeck()
{
	for (vector<card>::iterator cardIter = playerCardDeck.begin(); cardIter != playerCardDeck.end(); cardIter++)
	{
		int cardRank = cardIter->returnCardRank();
		cout << "[" << cardRank << "]";
	}
}

//changes player score
void player::updateScore(int num)
{
	playerScore += num;
}

//checks if the player deck has any pairs
bool player::checkPairs(int num)
{
	int rank = 0;

	for (int cardIter = 0; cardIter < size(playerCardDeck) - 1; cardIter++)
	{
		rank = playerCardDeck[cardIter].returnCardRank();
		if (rank == num)
		{
			return true;
		}

	}

	return false;

	}

//changes status of all the cards in the player deck to "inDeck"
void player::changeDeckCardStatus()
{
	for (vector<card>::iterator cardIter = playerCardDeck.begin(); cardIter != playerCardDeck.end(); cardIter++)
	{
		cardIter->switchCardStatus("inDeck");
	}
}

//checks if the cards are within the deck
bool player::withinPlayerDeck(int num)
{
	bool condition = false;
	int cardRank = 0;
	for (vector<card>::iterator cardIter = playerCardDeck.begin(); cardIter != playerCardDeck.end(); cardIter++)
	{
		cardRank = cardIter->returnCardRank();
		if (cardRank == num)
		{
			condition = true;
		}

	}

	return condition;
}

//returns the number of cards in the player deck
int player::getNumCards()
{
	return(size(playerCardDeck));
}