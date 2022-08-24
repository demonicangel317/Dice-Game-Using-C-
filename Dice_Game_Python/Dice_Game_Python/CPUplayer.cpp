#include "CPUplayer.h"
#include "player.h"
#include <iostream>

using namespace std;

/*

To make the CPU  player more competitive i had to increase the chanes of the CPU making a Hit
As the more of a chance the cpu player takes at folding the game tends to end prematurely with CPU player always loosing
due ro folding so much

*/

//CPUplayer::CPUplayer(string name) : player(name)


//changes lowest card value
void CPUplayer::changelowestCardValue(int num)
{
	lowestValue = num;
}

//makes decision weather to hit or fold
string CPUplayer::makeDecision()
{
	//this part is responsible for getting the highest value in the plyers deck to make the decision
	int highest = playerCardDeck[0].returnCardRank();
	int iterRank = 0;
	for (vector<card>::iterator cardIter = playerCardDeck.begin(); cardIter != playerCardDeck.end(); cardIter++)
	{
		iterRank = cardIter->returnCardRank();
		if (iterRank > highest)
		{
			highest = iterRank;
		}
	}

	//highest value of the deck
	ownDeckHighestValue = highest;


	srand(unsigned(time(NULL)));
	cout << playerName << " is making Decision......." << endl;
	string decision = "";

	int randNum = 0;

	//had to decrease the chance of the cpu making a fold
	if (ownDeckHighestValue > 8)
	{
		if (lowestValue <= 4)
		{
			//if the lowest card value within all player decks is less than or equal to 4 then the player wiill have a 60 percent chnce of folding
			randNum = rand() % 10;
			if (randNum == 9 || randNum == 8 || randNum == 7 || randNum == 6 || randNum == 5 || randNum == 4)
			{
				decision = "FOLD";
			}
			else
			{
				decision = "HIT";
			}


		}


		//if the lowest card present in all player decks equal to five then the cpu makes a 50 50 decision to fold or hit
		if (lowestValue == 5)
		{
			randNum = rand() % 2;
			if (randNum == 0)
			{
				decision = "FOLD";

			}
			else
			{
				decision = "HIT";

			}

		}



		// if the lowest card present in all player deck is greater than or equal to 8 then a 80 percent chace of hitting
		if (lowestValue >= 8)
		{
			randNum = rand() % 10;
			if (randNum == 9 || randNum == 8)
			{
				decision = "FOLD";
			}
			else
			{
				decision = "HIT";
			}


		}

		// if the lowest card present in all player deck is greater than or equal to 6 then a 40 percent chace of hitting
		else if (lowestValue >= 6)
		{
			randNum = rand() % 10;
			if (randNum == 9 || randNum == 8 || randNum == 7 || randNum == 6)
			{
				decision = "FOLD";
			}
			else
			{
				decision = "HIT";
			}


		}

	}

	else
	{
		decision = "HIT";
	}

	return decision;
}