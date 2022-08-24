#ifndef CPUPLAYER_H
#define CPUPLAYER_H

#include "player.h"
#include <iostream>
#include <string>

using namespace std;


/*

To make the CPU  player more competitive i had to increase the chanes of the CPU making a Hit
As the more of a chance the cpu player takes at folding the game tends to end prematurely with CPU player always loosing 
due ro folding so much

*/



class CPUplayer: public player
{
private:
	int lowestValue = 0;
	int ownDeckHighestValue = 0;

public:

	CPUplayer(string name) : player(name)
	{

	}

	//changes lowest card value
	void changelowestCardValue(int num);
	
	//makes decision weather to hit or fold
	string makeDecision();
};


#endif CPUPLAYER_H
