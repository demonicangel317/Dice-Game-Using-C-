#ifndef CARD_H
#define CARD_H

#include<string>

using namespace std;

class card
{
protected:
	//list of variables
	int cardRank;
	string cardVisRep;
	string cardStatus;

public:

	//constructor for the card
	card(int rank, string visual);

	//destructor for the card
	~card();

	//changes the card status
	void switchCardStatus(string status);

	//prints the visual representation of the card
	void displayCardVisRep();

	//gets the status of the card
	string getCardStatus();

	//returns the rank of the card
	int returnCardRank();
};



#endif