#include "card.h"
#include<string>
#include<iostream>

using namespace std;

card::card(int rank, string visual)
{
	cardRank = rank;
	cardStatus = "inDeck";
	cardVisRep = visual;
}

//destructor for the card
card::~card()
{

}

//changes the card status
void card::switchCardStatus(string status)
{
	cardStatus = status;
}

//prints the visual representation of the card
void card:: displayCardVisRep()
{
	cout << cardVisRep << endl;
}

//gets the status of the card
string card::getCardStatus()
{
	return cardStatus;
}

//returns the rank of the card
int card::returnCardRank()
{
	return cardRank;
}