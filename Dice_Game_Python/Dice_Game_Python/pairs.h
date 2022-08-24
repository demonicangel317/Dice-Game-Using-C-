#pragma once
#include <fstream>
#include <iostream>
#include<sstream>
#include "card.h"
#include "player.h"
#include "CPUplayer.h"

using namespace std;

//function list
void waitForPlayer();
void readFromFile(string myFile);
void playPairs();
void setNumPlayer(vector<player>* vectorList, int* score, vector<CPUplayer>& cpuplayers);
void setNumPlayer(vector<player>* vectorList, int* score);
string askForString(string name, string question);
char askForChar(string question);
void createCardDeck(vector<card>* vectorList);
void assignPlayerCards(vector<player>& playerList, vector<card>& cardList, vector<CPUplayer>& cpuplayers);
void breakTies(vector<player>& playerList, vector<card>& cardList, int lowest, vector<CPUplayer>& cpuplayers);
void checkTies(vector<player>& playerList, vector<card>& cardList, vector<CPUplayer>& cpuplayers);
void beginRound(vector<player>& playerList, vector<card>& cardList, int score, vector<CPUplayer>& cpuplayers);
void displayTitle(int score, vector<player>& playerList, vector<CPUplayer>& cpuplayers);
void beginPlayerRotation(vector<player>& playerList, vector<card> cardList, int score, vector<CPUplayer>& cpuplayers);
void changeAllCardStatus(vector<card>& cardList);
void clearPlayerDecks(vector<player>& playerList);
void clearCPUPlayerDecks(vector<CPUplayer>& CPUPlayerList);
bool checkGameOver(vector<player>& playerList, int targetScore, vector<CPUplayer>& cpuplayers);
void gameOver(int targetScore, vector<player>& playerList, vector<CPUplayer>& cpuplayers);
void createCPUPlayers(int num, vector<CPUplayer>& cpuplayers);

//wialts for player input and clears the screen
void waitForPlayer()
{
	system("pause");
	system("CLS");

}

//Takes in a file and reads it then prints it out line by line
void readFromFile(string myFile)
{
	ifstream fileToRead;
	fileToRead.open(myFile);
	if (fileToRead.is_open())
	{
		string line = "";
		while (!fileToRead.eof())
		{
			getline(fileToRead, line);
			cout << line << endl;;

		}
	}

	else
	{
		cout << "File could not be read" << endl;
	}

}

//Main Game Loop
void playPairs()
{

	vector<player> players;
	vector<card> cardDeck;
	vector<CPUplayer> CPUplayers;
	int targetScore = 0;
	bool isGameOver = false;

	//makes the card deck required
	createCardDeck(&cardDeck);

	//For the first step I set the number of players and set their names
	setNumPlayer(&players, &targetScore, CPUplayers);

	//begins the round
	beginRound(players, cardDeck, targetScore, CPUplayers);

	//play continuous pairs
	gameOver(targetScore, players, CPUplayers);

}

//Used to set the number of players in the vecotr and set the target score
void setNumPlayer(vector<player>* vectorList, int* score, vector<CPUplayer>& cpuplayers)
{

	//get the number of players
	cout << "Please eneter the number of players that will be in the game (2 to 8:) inclusive : " << endl;
	int numPlayers = 0;
	cin >> numPlayers;

	//this checks if the entered int is in the valid range
	while (numPlayers < 2 || numPlayers > 8)
	{
		cout << "Enter a number between 2 and 8 inclusive: ";
		cin >> numPlayers;
	}

	//sets the amount of avaialble spots for cpu players
	int availablePlayerSpots = 8 - numPlayers;

	cout << "Please eneter the number of CPU players that will be in the game (0 to " << availablePlayerSpots << ":) inclusive : " << endl;
	int numCPUPlayers = 0;
	cin >> numCPUPlayers;

	while (availablePlayerSpots < 0 || availablePlayerSpots > 8)
	{
		cout << "Enter a number between 2 and " << availablePlayerSpots << " inclusive: ";
		cin >> numCPUPlayers;
	}



	//Now to get the name of all the players
	for (int i = 0; i < numPlayers; i++)
	{
		string tempName = "";
		cout << "Enter name of player " << (i + 1) << " : ";
		cin >> tempName;
		vectorList->push_back(player(tempName));
	}

	numPlayers += numCPUPlayers;

	//Sets the target score accoreding to number of players
	if (numPlayers < 7)
	{
		*score = 60 / numPlayers + 1;
	}
	else
	{
		*score = 11;
	}

	createCPUPlayers(numCPUPlayers, cpuplayers);

	waitForPlayer();




}

//display the title for each turn
void displayTitle(int score, vector<player>& playerList, vector<CPUplayer>& cpuplayers)
{
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "                           Pairs                               " << endl;
	cout << "                      Target Score is " << score << "          " << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

	string name = "";
	int playerScore = 0;

	//Iterates through each player and their score and prints them out
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{

		name = playerIter->getName();
		playerScore = playerIter->getScore();

		cout << "Name : " << name << "\tScore : " << playerScore << endl;
		cout << "Hand : ";
		playerIter->displayPlayerDeck();

		cout << endl << endl;
	}


	//Iterates through each CPU player and their score and prints them out
	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{

		name = CPUIter->getName();
		playerScore = CPUIter->getScore();

		cout << "Name : " << name << "\tScore : " << playerScore << endl;
		cout << "Hand : ";
		CPUIter->displayPlayerDeck();

		cout << endl << endl;
	}
}

//returns a string value afte inputting necesary question
string askForString(string name, string question)
{
	cout << "\n" << name << ", " << question;
	string userInput = "";
	//cin.ignore();
	while (userInput == "")
	{
		cin >> userInput;
	}

	return userInput;
}

//gets char value from the user
char askForChar(string question)
{
	cout << "\n" << question << endl;
	char userInput = '`';
	cin.ignore();
	cin >> userInput;

	return userInput;
}

//gets it value from user
int askForInt(string question)
{
	cout << "\n" << question << endl;
	int userInput = NULL;
	while (userInput == NULL)
	{
		cin >> userInput;
	}

	return userInput;
}

//make the card deck
void createCardDeck(vector<card>* vectorList)
{


	stringstream oneVisRepp;

	oneVisRepp << "\n------------";
	oneVisRepp << "\n--1111111---";
	oneVisRepp << "\n-1::::::1---";
	oneVisRepp << "\n1:::::::1---";
	oneVisRepp << "\n111:::::1---";
	oneVisRepp << "\n---1::::1---";
	oneVisRepp << "\n---1::::1---";
	oneVisRepp << "\n---1::::1---";
	oneVisRepp << "\n---1::::l---";
	oneVisRepp << "\n---1::::l---";
	oneVisRepp << "\n---1::::l---";
	oneVisRepp << "\n---1::::l---";
	oneVisRepp << "\n---1::::l---";
	oneVisRepp << "\n111::::::111";
	oneVisRepp << "\n1::::::::::1";
	oneVisRepp << "\n1::::::::::1";
	oneVisRepp << "\n111111111111";
	oneVisRepp << "\n------------";




	stringstream twoVisRep;
	twoVisRep << "\n--------------------";
	twoVisRep << "\n-222222222222222----";
	twoVisRep << "\n2:::::::::::::::22--";
	twoVisRep << "\n2::::::222222:::::2-";
	twoVisRep << "\n2222222-----2:::::2-";
	twoVisRep << "\n------------2:::::2-";
	twoVisRep << "\n------------2:::::2-";
	twoVisRep << "\n---------2222::::2--";
	twoVisRep << "\n----22222::::::22---";
	twoVisRep << "\n--22::::::::222-----";
	twoVisRep << "\n-2:::::22222--------";
	twoVisRep << "\n2:::::2-------------";
	twoVisRep << "\n2:::::2-------------";
	twoVisRep << "\n2:::::2-------222222";
	twoVisRep << "\n2::::::2222222:::::2";
	twoVisRep << "\n2::::::::::::::::::2";
	twoVisRep << "\n22222222222222222222";
	twoVisRep << "\n--------------------";

	//string twoVisrepS = string(twoVisRep);

	stringstream threeVisRep;
	threeVisRep << "\n-------------------";
	threeVisRep << "\n-333333333333333---";
	threeVisRep << "\n3:::::::::::::::33-";
	threeVisRep << "\n3::::::33333::::::3";
	threeVisRep << "\n3333333-----3:::::3";
	threeVisRep << "\n------------3:::::3";
	threeVisRep << "\n------------3:::::3";
	threeVisRep << "\n----33333333:::::3-";
	threeVisRep << "\n----3:::::::::::3--";
	threeVisRep << "\n----33333333:::::3-";
	threeVisRep << "\n------------3:::::3";
	threeVisRep << "\n------------3:::::3";
	threeVisRep << "\n------------3:::::3";
	threeVisRep << "\n3333333-----3:::::3";
	threeVisRep << "\n3::::::33333::::::3";
	threeVisRep << "\n3:::::::::::::::33-";
	threeVisRep << "\n-333333333333333---";
	threeVisRep << "\n-------------------";

	stringstream fourVisRep;

	fourVisRep << "\n------------------";
	fourVisRep << "\n-------444444444--";
	fourVisRep << "\n------4::::::::4--";
	fourVisRep << "\n-----4:::::::::4--";
	fourVisRep << "\n----4::::44::::4--";
	fourVisRep << "\n---4::::4-4::::4--";
	fourVisRep << "\n--4::::4--4::::4--";
	fourVisRep << "\n-4::::4---4::::4--";
	fourVisRep << "\n4::::444444::::444";
	fourVisRep << "\n4::::::::::::::::4";
	fourVisRep << "\n4444444444:::::444";
	fourVisRep << "\n----------4::::4--";
	fourVisRep << "\n----------4::::4--";
	fourVisRep << "\n----------4::::4--";
	fourVisRep << "\n--------44::::::44";
	fourVisRep << "\n--------4::::::::4";
	fourVisRep << "\n--------4444444444";
	fourVisRep << "\n------------------";

	stringstream fiveVisRep;
	fiveVisRep << "\n-------------------";
	fiveVisRep << "\n555555555555555555-";
	fiveVisRep << "\n5::::::::::::::::5-";
	fiveVisRep << "\n5::::::::::::::::5-";
	fiveVisRep << "\n5:::::555555555555-";
	fiveVisRep << "\n5:::::5------------";
	fiveVisRep << "\n5:::::5------------";
	fiveVisRep << "\n5:::::5555555555---";
	fiveVisRep << "\n5:::::::::::::::5--";
	fiveVisRep << "\n555555555555:::::5-";
	fiveVisRep << "\n------------5:::::5";
	fiveVisRep << "\n------------5:::::5";
	fiveVisRep << "\n5555555-----5:::::5";
	fiveVisRep << "\n5::::::55555::::::5";
	fiveVisRep << "\n-55:::::::::::::55-";
	fiveVisRep << "\n---55:::::::::55---";
	fiveVisRep << "\n-----555555555-----";
	fiveVisRep << "\n-------------------";

	stringstream sixVisRep;
	sixVisRep << "\n-------------------";
	sixVisRep << "\n--------66666666---";
	sixVisRep << "\n-------6::::::6----";
	sixVisRep << "\n------6::::::6-----";
	sixVisRep << "\n-----6::::::6------";
	sixVisRep << "\n----6::::::6-------";
	sixVisRep << "\n---6::::::6--------";
	sixVisRep << "\n--6::::::6---------";
	sixVisRep << "\n-6::::::::66666----";
	sixVisRep << "\n6::::::::::::::66--";
	sixVisRep << "\n6::::::66666:::::6-";
	sixVisRep << "\n6:::::6-----6:::::6";
	sixVisRep << "\n6:::::6-----6:::::6";
	sixVisRep << "\n6::::::66666::::::6";
	sixVisRep << "\n-66:::::::::::::66-";
	sixVisRep << "\n---66:::::::::66---";
	sixVisRep << "\n-----666666666-----";
	sixVisRep << "\n-------------------";

	stringstream sevenVisRep;
	sevenVisRep << "\n--------------------";
	sevenVisRep << "\n77777777777777777777";
	sevenVisRep << "\n7::::::::::::::::::7";
	sevenVisRep << "\n7::::::::::::::::::7";
	sevenVisRep << "\n777777777777:::::::7";
	sevenVisRep << "\n-----------7::::::7-";
	sevenVisRep << "\n----------7::::::7--";
	sevenVisRep << "\n---------7::::::7---";
	sevenVisRep << "\n--------7::::::7----";
	sevenVisRep << "\n-------7::::::7-----";
	sevenVisRep << "\n------7::::::7------";
	sevenVisRep << "\n-----7::::::7-------";
	sevenVisRep << "\n----7::::::7--------";
	sevenVisRep << "\n---7::::::7---------";
	sevenVisRep << "\n--7::::::7----------";
	sevenVisRep << "\n-7::::::7-----------";
	sevenVisRep << "\n77777777------------";
	sevenVisRep << "\n--------------------";

	stringstream eightVisRep;
	eightVisRep << "\n-------------------";
	eightVisRep << "\n-----888888888-----";
	eightVisRep << "\n---88:::::::::88---";
	eightVisRep << "\n-88:::::::::::::88-";
	eightVisRep << "\n8::::::88888::::::8";
	eightVisRep << "\n8:::::8-----8:::::8";
	eightVisRep << "\n8:::::8-----8:::::8";
	eightVisRep << "\n-8:::::88888:::::8-";
	eightVisRep << "\n--8:::::::::::::8--";
	eightVisRep << "\n-8:::::88888:::::8-";
	eightVisRep << "\n8:::::8-----8:::::8";
	eightVisRep << "\n8:::::8-----8:::::8";
	eightVisRep << "\n8:::::8-----8:::::8";
	eightVisRep << "\n8::::::88888::::::8";
	eightVisRep << "\n-88:::::::::::::88-";
	eightVisRep << "\n---88:::::::::88---";
	eightVisRep << "\n-----888888888-----";
	eightVisRep << "\n-------------------";


	stringstream nineVisRep;
	nineVisRep << "\n-------------------";
	nineVisRep << "\n-----999999999-----";
	nineVisRep << "\n---99:::::::::99---";
	nineVisRep << "\n-99:::::::::::::99-";
	nineVisRep << "\n9::::::99999::::::9";
	nineVisRep << "\n9:::::9-----9:::::9";
	nineVisRep << "\n9:::::9-----9:::::9";
	nineVisRep << "\n-9:::::99999::::::9";
	nineVisRep << "\n--99::::::::::::::9";
	nineVisRep << "\n----99999::::::::9-";
	nineVisRep << "\n---------9::::::9--";
	nineVisRep << "\n--------9::::::9---";
	nineVisRep << "\n-------9::::::9----";
	nineVisRep << "\n------9::::::9-----";
	nineVisRep << "\n-----9::::::9------";
	nineVisRep << "\n----9::::::9-------";
	nineVisRep << "\n---99999999--------";
	nineVisRep << "\n-------------------";


	stringstream tenVisRep;
	tenVisRep << "\n-------------------------------";
	tenVisRep << "\n--1111111--------000000000-----";
	tenVisRep << "\n-1::::::1------00:::::::::00---";
	tenVisRep << "\n1:::::::1----00:::::::::::::00-";
	tenVisRep << "\n111:::::1---0:::::::000:::::::0";
	tenVisRep << "\n---1::::1---0::::::0---0::::::0";
	tenVisRep << "\n---1::::1---0:::::0-----0:::::0";
	tenVisRep << "\n---1::::1---0:::::0-----0:::::0";
	tenVisRep << "\n---1::::l---0:::::0-000-0:::::0";
	tenVisRep << "\n---1::::l---0:::::0-000-0:::::0";
	tenVisRep << "\n---1::::l---0:::::0-----0:::::0";
	tenVisRep << "\n---1::::l---0:::::0-----0:::::0";
	tenVisRep << "\n---1::::l---0::::::0---0::::::0";
	tenVisRep << "\n111::::::1110:::::::000:::::::0";
	tenVisRep << "\n1::::::::::1-00:::::::::::::00-";
	tenVisRep << "\n1::::::::::1---00:::::::::00---";
	tenVisRep << "\n111111111111-----000000000-----";
	tenVisRep << "\n-------------------------------";


	vectorList->push_back(card(1, oneVisRepp.str()));

	//Add the twos to the card deck
	for (int i = 0; i < 2; i++)
	{
		vectorList->push_back(card(2, twoVisRep.str()));
	}

	//Add the threes to the card deck
	for (int i = 0; i < 3; i++)
	{
		vectorList->push_back(card(3, threeVisRep.str()));
	}

	//Add the fours to the card deck
	for (int i = 0; i < 4; i++)
	{
		vectorList->push_back(card(4, fourVisRep.str()));
	}

	//Add the fives to the card deck
	for (int i = 0; i < 5; i++)
	{
		vectorList->push_back(card(5, fiveVisRep.str()));
	}

	//Add the sixes to the card deck
	for (int i = 0; i < 6; i++)
	{
		vectorList->push_back(card(6, sixVisRep.str()));
	}

	//Add the sevens to the card deck
	for (int i = 0; i < 7; i++)
	{
		vectorList->push_back(card(7, sevenVisRep.str()));
	}

	//Add the eights to the card deck
	for (int i = 0; i < 8; i++)
	{
		vectorList->push_back(card(8, eightVisRep.str()));
	}

	//Add the nines to the card deck
	for (int i = 0; i < 9; i++)
	{
		vectorList->push_back(card(9, nineVisRep.str()));
	}

	//Add the tens to the card deck
	for (int i = 0; i < 10; i++)
	{
		vectorList->push_back(card(10, tenVisRep.str()));
	}



}

//starts round and assigns each player a card
void assignPlayerCards(vector<player>& playerList, vector<card>& cardList, vector<CPUplayer>& cpuplayers)//gets the references of player and crad vectors
{
	//seeds random values
	srand(unsigned(time(NULL)));
	int randNum = 0;
	string status = "";

	//adds a random card that is within the deck to the players
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		while (true)
		{
			randNum = rand() % 54;
			status = cardList[randNum].getCardStatus();
			if (status == "inDeck")
			{
				playerIter->addCardToDeck(cardList[randNum]);
				cardList[randNum].switchCardStatus("withPlayer");
				break;
			}
		}
	}

	//adds a card to the cpu players
	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{
		while (true)
		{
			//selects a random card and looks if its within the deck and adds it to player deck
			randNum = rand() % 55;
			status = cardList[randNum].getCardStatus();
			if (status == "inDeck")
			{
				CPUIter->addCardToDeck(cardList[randNum]);
				cardList[randNum].switchCardStatus("withPlayer");
				break;
			}
		}
	}


}

//checks if players are tied to the lowest card
void checkTies(vector<player>& playerList, vector<card>& cardList, vector<CPUplayer>& cpuplayers)
{
	//defaults sets the lowest value to first player deck card
	int lowest = playerList[0].returnLatestPlayerCardValue();


	int playerCardValue = 0;

	//iterates through each player
	for (vector<player>::iterator iter = playerList.begin(); iter != playerList.end(); iter++)
	{
		//gets the rank of the latest card in the player deck
		playerCardValue = iter->returnLatestPlayerCardValue();

		//if the rank is lower then make it the new lowest
		if (playerCardValue < lowest)
		{
			lowest = playerCardValue;

		}
	}

	//iterates through each CPU player
	for (vector<CPUplayer>::iterator iter = cpuplayers.begin(); iter != cpuplayers.end(); iter++)
	{
		//gets the rank of the latest card in the player deck
		playerCardValue = iter->returnLatestPlayerCardValue();

		//if the rank is lower then make it the new lowest
		if (playerCardValue < lowest)
		{
			lowest = playerCardValue;

		}
	}


	//variable used to count how mnany cards are tied to lowest
	int checkNumLowest = 0;


	//this loop iterates through each of the latest cards in the player deck and assigns them new cards
	for (vector<player>::iterator iter = playerList.begin(); iter != playerList.end(); iter++)
	{
		playerCardValue = iter->returnLatestPlayerCardValue();
		if (playerCardValue == lowest)
		{
			checkNumLowest++;

		}
	}

	//this loop iterates through each of the latest cards in the CPU player deck and assigns them new cards
	for (vector<CPUplayer>::iterator iter = cpuplayers.begin(); iter != cpuplayers.end(); iter++)
	{
		playerCardValue = iter->returnLatestPlayerCardValue();
		if (playerCardValue == lowest)
		{
			checkNumLowest++;

		}
	}

	//checks if more than one player has the lowest card
	if (checkNumLowest > 1)
	{
		//if more than one players are tied then the program jumps to break the ties
		breakTies(playerList, cardList, lowest, cpuplayers);
	}

}

//if the players are tied for the lowest card then this fuction is called to break the ties
void breakTies(vector<player>& playerList, vector<card>& cardList, int lowest, vector<CPUplayer>& cpuplayers)
{
	int playerCardValue = 0;
	string status = "";
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		int randNum = 0;
		playerCardValue = playerIter->returnLatestPlayerCardValue();

		if (playerCardValue == lowest)
		{
			while (true)
			{
				randNum = rand() % 54;
				status = cardList[randNum].getCardStatus();
				if (status == "inDeck")
				{
					playerIter->addCardToDeck(cardList[randNum]);
					cardList[randNum].switchCardStatus("withPlayer");
					break;
				}
			}

		}
	}


	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{
		int randNum = 0;
		playerCardValue = CPUIter->returnLatestPlayerCardValue();

		if (playerCardValue == lowest)
		{
			while (true)
			{
				randNum = rand() % 54;
				status = cardList[randNum].getCardStatus();
				if (status == "inDeck")
				{
					CPUIter->addCardToDeck(cardList[randNum]);
					cardList[randNum].switchCardStatus("withPlayer");
					break;
				}
			}

		}
	}

	checkTies(playerList, cardList, cpuplayers);
}

//begins the round by calling other functions
void beginRound(vector<player>& playerList, vector<card>& cardList, int score, vector<CPUplayer>& cpuplayers)
{

	while (checkGameOver(playerList, score, cpuplayers))
	{
		//assigns the players the cards
		assignPlayerCards(playerList, cardList, cpuplayers);

		//checks if the assigned cards are tied and breaks an ties
		checkTies(playerList, cardList, cpuplayers);

		//start rotating turns of the player starting from the lowest
		beginPlayerRotation(playerList, cardList, score, cpuplayers);
	}




}

//begins rotating turns 
void beginPlayerRotation(vector<player>& playerList, vector<card> cardList, int score, vector<CPUplayer>& cpuplayers)
{
	//sets default value of lowest 
	int lowest = playerList[0].returnLatestPlayerCardValue();
	//place holder variable for latest player card
	int playerHand = 0;
	//iterates through the vector of players to find the lowest card among them
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		playerHand = playerIter->returnLatestPlayerCardValue();
		if (playerHand < lowest)
		{
			lowest = playerHand;
		}
	}


	int CPUlowest = 11;
	if (size(cpuplayers) != 0)
	{
		CPUlowest = cpuplayers[0].returnLatestPlayerCardValue();
	}


	//iterates through the vector of CPU players to find the lowest card among them
	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{
		playerHand = CPUIter->returnLatestPlayerCardValue();
		if (playerHand < lowest)
		{
			CPUlowest = playerHand;
		}
	}


	//creating the below two comparisons was essential to start from the player with the lowest deck value

	if (lowest < CPUlowest)
	{
		//intialize the start index
		int startIndex = 0;
		int cardValue = 0;
		//iterates through the vector again until lowest card value is found and makes that the start index

		for (int iter = 0; iter < size(playerList); iter++)
		{
			cardValue = playerList[iter].returnLatestPlayerCardValue();
			if (cardValue == lowest)
			{
				startIndex = iter;
				break;
			}
		}

		//ininitialize the sting values required
		string userInput = "";
		string playerName = "";
		string CPUplayerName = "";

		//iterartes through the player list indefinitly till a pair is formed
		for (int iter = startIndex; iter <= size(playerList); iter++)
		{
			bool breakLoop = false;

			//this step was essential to make sure that to continue the rotation and make sure vector index is not passed
			if (iter == (size(playerList)))
			{
				for (int CPUIter = 0; CPUIter < size(cpuplayers); CPUIter++)
				{
					waitForPlayer();
					displayTitle(score, playerList, cpuplayers);

					if (CPUIter == size(cpuplayers) - 1)
					{
						iter = 0;
					}

					///////////////////////////////////////////////////////////////////////////////////////////////////////////
					int iterLowestRank = 0;
					int CPUlowest = 100;
					for (int CPUiter2 = 0; CPUiter2 < size(cpuplayers); CPUiter2++)
					{
						if (CPUIter == CPUiter2)
						{
							continue;
						}

						iterLowestRank = cpuplayers[CPUiter2].returnLowest();
						if (iterLowestRank < CPUlowest)
						{
							CPUlowest = iterLowestRank;
						}


					}

					int playerlowest = playerList[0].returnLatestPlayerCardValue();

					//iterates through the vector of CPU players to find the lowest card among them
					int playerHand2 = 0;
					for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
					{
						playerHand2 = playerIter->returnLowest();
						if (playerHand2 < playerlowest)
						{
							playerlowest = playerHand2;
						}
					}

					if (CPUlowest > playerlowest)
					{
						CPUlowest = playerlowest;
					}

					////////////////////////////////////////////////////////////////////////////////////////////////////////////

					cpuplayers[CPUIter].changelowestCardValue(CPUlowest);
					string decision = cpuplayers[CPUIter].makeDecision();


					//if the CPU chooses to hit
					if (decision == "HIT")
					{
						string pName = cpuplayers[CPUIter].getName();
						cout << pName << " has decided to Hit." << endl;
						int randNum = 0;
						string status = "";
						int newCardRank = 0;
						bool isPairformed = false;
						while (true)
						{
							randNum = rand() % 54;
							status = cardList[randNum].getCardStatus();
							//string visRep;
							if (status == "inDeck")
							{
								cpuplayers[CPUIter].addCardToDeck(cardList[randNum]);
								cardList[randNum].displayCardVisRep();
								cardList[randNum].switchCardStatus("withPlayer");
								newCardRank = cardList[randNum].returnCardRank();
								break;
							}
						}

						bool isAPairFormed = cpuplayers[CPUIter].checkPairs(newCardRank);
						if (isAPairFormed)
						{

							cpuplayers[CPUIter].updateScore(newCardRank);
							waitForPlayer();
							displayTitle(score, playerList, cpuplayers);
							string pName = cpuplayers[CPUIter].getName();
							cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
							changeAllCardStatus(cardList);

							clearPlayerDecks(playerList);
							clearCPUPlayerDecks(cpuplayers);
							breakLoop = true;
							break;
						}



					}

					//if the CPU chhoses to fold
					if (decision == "FOLD")
					{
						string pName = cpuplayers[CPUIter].getName();
						cout << pName << " has decided to fold." << endl;
						//iterates through every player in the ector
						CPUlowest = 11;
						if (size(cpuplayers) != 1)
						{
							CPUlowest = 100;
							iterLowestRank = 0;
							for (int CPUiter2 = 0; CPUiter2 < size(cpuplayers); CPUiter2++)
							{
								if (CPUIter == CPUiter2)
								{
									continue;
								}

								iterLowestRank = cpuplayers[CPUiter2].returnLowest();
								if (iterLowestRank < CPUlowest)
								{
									CPUlowest = iterLowestRank;
								}


							}
		
						}
						

						int playerlowest = playerList[0].returnLatestPlayerCardValue();

						//iterates through the vector of CPU players to find the lowest card among them
						int playerHand2 = 0;
						for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
						{
							playerHand2 = playerIter->returnLowest();
							if (playerHand2 < playerlowest)
							{
								playerlowest = playerHand2;
							}
						}

						if (CPUlowest > playerlowest)
						{
							CPUlowest = playerlowest;
						}

						string CPUName = cpuplayers[CPUIter].getName();
						cout << CPUName << " has ended this round by FOLDING and scoring " << CPUlowest << " points!" << endl;
						cpuplayers[CPUIter].updateScore(CPUlowest);
						changeAllCardStatus(cardList);
						clearPlayerDecks(playerList);
						clearCPUPlayerDecks(cpuplayers);
						breakLoop = true;
						break;
					}
				}

				iter = 0;
			}

			if (breakLoop)
			{
				break;
			}


			waitForPlayer();
			displayTitle(score, playerList, cpuplayers);
			playerName = playerList[iter].getName();
			userInput = askForString(playerName, "Will you [H]it, [F]old or [Q]uit:");

			while (userInput != "H" && userInput != "h" && userInput != "F" && userInput != "f" && userInput != "Q" && userInput != "q")
			{
				cout << "Please enter [H] or [F] or [Q]" << endl;
				cin >> userInput;
			}

			if (userInput == "Q" || userInput == "q")
			{
				if (size(playerList) != 1)
				{
					playerList.erase(playerList.begin() + iter);
					break;
				}
				else
				{
					cout << "Cant quit as there is only one user" << endl;
					break;
				}


			}

			//if the player chooses to hit
			if (userInput == "H" || userInput == "h")
			{
				string pName = playerList[iter].getName();
				cout << pName << " has decided to Hit." << endl;
				int randNum = 0;
				string status = "";
				int newCardRank = 0;
				bool isPairformed = false;
				while (true)
				{
					randNum = rand() % 54;
					status = cardList[randNum].getCardStatus();
					//string visRep =" ";
					if (status == "inDeck")
					{
						playerList[iter].addCardToDeck(cardList[randNum]);
						cardList[randNum].displayCardVisRep();
						cardList[randNum].switchCardStatus("withPlayer");
						newCardRank = cardList[randNum].returnCardRank();
						break;
					}
				}

				bool isAPairFormed = playerList[iter].checkPairs(newCardRank);
				if (isAPairFormed)
				{

					playerList[iter].updateScore(newCardRank);
					waitForPlayer();
					displayTitle(score, playerList, cpuplayers);
					//string pName = playerList[iter].getName();
					cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
					changeAllCardStatus(cardList);
					clearPlayerDecks(playerList);
					clearCPUPlayerDecks(cpuplayers);
					breakLoop = true;
					break;
				}



			}

			//if the player chhoses to fold
			if (userInput == "F" || userInput == "f")
			{
				string pName = playerList[iter].getName();
				cout << pName << " has decided to fold." << endl;
				//iterates through every player in the ector
				int lowest = 100;
				int iterLowestRank = 100;
				for (int iter2 = 0; iter2 < size(playerList); iter2++)
				{
					if (iter == iter2)
					{
						continue;
					}

					iterLowestRank = playerList[iter2].returnLowest();
					if (iterLowestRank < lowest)
					{
						lowest = iterLowestRank;
					}


				}

				int CPUlowest = 11;

				if (size(cpuplayers) != 0)
				{
					CPUlowest = cpuplayers[0].returnLowest();
				}



				//iterates through the vector of CPU players to find the lowest card among them
				for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
				{
					playerHand = CPUIter->returnLowest();
					if (playerHand < lowest)
					{
						CPUlowest = playerHand;
					}
				}

				if (iterLowestRank > CPUlowest)
				{
					iterLowestRank = CPUlowest;
				}


				cout << pName << " has ended this round by FOLDING and scoring " << iterLowestRank << " points!" << endl;
				playerList[iter].updateScore(lowest);
				changeAllCardStatus(cardList);
				clearPlayerDecks(playerList);
				clearCPUPlayerDecks(cpuplayers);
				breakLoop = true;
				break;
			}

			if (breakLoop)
			{
				break;
			}


		}


	}

	if (CPUlowest < lowest)
	{
		//intialize the start index
		int startIndex = 0;
		int cardValue = 0;


		for (int iter = 0; iter < size(cpuplayers); iter++)
		{
			cardValue = cpuplayers[iter].returnLatestPlayerCardValue();
			if (cardValue == CPUlowest)
			{
				startIndex = iter;
				break;
			}
		}

		//ininitialize the sting values required
		string userInput = "";
		string playerName = "";
		string CPUplayerName = "";

		//iterartes through the player list indefinitly till a pair is formed
		for (int iter = startIndex; iter <= size(cpuplayers); iter++)
		{
			bool breakLoop = false;

			//this step was essential to make sure that to continue the rotation and make sure vector index is not passed
			if (iter == (size(cpuplayers)))
			{
				for (int playerIter = 0; playerIter < size(cpuplayers); playerIter++)
				{
					iter = 0;
					waitForPlayer();
					displayTitle(score, playerList, cpuplayers);
					playerName = playerList[playerIter].getName(); ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					userInput = askForString(playerName, "Will you [H]it, [F]old or [Q]uit:");

					while (userInput != "H" && userInput != "h" && userInput != "F" && userInput != "f" && userInput != "Q" && userInput != "q")
					{
						cout << "Please enter [H] or [F] or [Q]" << endl;
						cin >> userInput;
					}


					if (userInput == "Q" || userInput == "q")
					{
						if (size(playerList) != 1)
						{
							playerList.erase(playerList.begin() + iter);
							break;
						}
						else
						{
							cout << "Cant quit as there is only one user" << endl;;
							break;
						}


					}

					//if the player chooses to hit
					if (userInput == "H" || userInput == "h")
					{
						string pName = playerList[playerIter].getName();
						cout << pName << " has decided to Hit." << endl;
						int randNum = 0;
						string status = "";
						int newCardRank = 0;
						bool isPairformed = false;
						while (true)
						{
							randNum = rand() % 54;
							status = cardList[randNum].getCardStatus();
							//string visRep =" ";
							if (status == "inDeck")
							{
								playerList[playerIter].addCardToDeck(cardList[randNum]);
								cardList[randNum].displayCardVisRep();
								cardList[randNum].switchCardStatus("withPlayer");
								newCardRank = cardList[randNum].returnCardRank();
								break;
							}
						}

						bool isAPairFormed = playerList[playerIter].checkPairs(newCardRank);
						if (isAPairFormed)
						{

							playerList[playerIter].updateScore(newCardRank);
							waitForPlayer();
							displayTitle(score, playerList, cpuplayers);
							//string pName = playerList[iter].getName();
							cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
							changeAllCardStatus(cardList);
							clearPlayerDecks(playerList);
							clearCPUPlayerDecks(cpuplayers);
							breakLoop = true;
							break;
						}



					}

					//if the player chhoses to fold
					if (userInput == "F" || userInput == "f")
					{
						string pName = playerList[playerIter].getName();
						cout << pName << " has decided to fold." << endl;
						//iterates through every player in the ector
						int lowest = 100;
						int iterLowestRank = 100;
						for (int iter2 = 0; iter2 < size(playerList); iter2++)
						{
							if (playerIter == iter2)
							{
								continue;
							}

							iterLowestRank = playerList[iter2].returnLowest();
							if (iterLowestRank < lowest)
							{
								lowest = iterLowestRank;
							}


						}

						int CPUlowest = cpuplayers[0].returnLowest();

						//iterates through the vector of CPU players to find the lowest card among them
						for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
						{
							playerHand = CPUIter->returnLowest();
							if (playerHand < lowest)
							{
								CPUlowest = playerHand;
							}
						}

						if (iterLowestRank > CPUlowest)
						{
							iterLowestRank = CPUlowest;
						}


						cout << pName << " has ended this round by FOLDING and scoring " << iterLowestRank << " points!" << endl;
						playerList[playerIter].updateScore(lowest);
						changeAllCardStatus(cardList);
						clearPlayerDecks(playerList);
						clearCPUPlayerDecks(cpuplayers);
						breakLoop = true;
						break;
					}


				}


				iter = 0;
			}

			/////////////////////////////////////////////////////////
		
			if (breakLoop)
			{
				break;
			}


			waitForPlayer();
			displayTitle(score, playerList, cpuplayers);
			playerName = cpuplayers[iter].getName();
			string decision = cpuplayers[iter].makeDecision();

			//if the player chooses to hit
			if (decision == "HIT")
			{
				string pName = cpuplayers[iter].getName();
				cout << pName << " has decided to Hit." << endl;
				int randNum = 0;
				string status = "";
				int newCardRank = 0;
				bool isPairformed = false;
				while (true)
				{
					randNum = rand() % 54;
					status = cardList[randNum].getCardStatus();
					//string visRep =" ";
					if (status == "inDeck")
					{
						cpuplayers[iter].addCardToDeck(cardList[randNum]);
						cardList[randNum].displayCardVisRep();
						cardList[randNum].switchCardStatus("withPlayer");
						newCardRank = cardList[randNum].returnCardRank();
						break;
					}
				}

				bool isAPairFormed = cpuplayers[iter].checkPairs(newCardRank);

				//checks if a pair is formed
				if (isAPairFormed)
				{

					cpuplayers[iter].updateScore(newCardRank);
					waitForPlayer();
					displayTitle(score, playerList, cpuplayers);
					//string pName = playerList[iter].getName();
					cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
					changeAllCardStatus(cardList);
					clearPlayerDecks(playerList);
					clearCPUPlayerDecks(cpuplayers);
					waitForPlayer();
					breakLoop = true;
					break;
				}



			}

			//if the player chhoses to fold
			if (decision == "FOLD")
			{
				string pName = cpuplayers[iter].getName();
				cout << pName << " has decided to fold." << endl;
				//iterates through every player in the ector
				int lowest = 100;
				int iterLowestRank = 100;

				if (size(cpuplayers) != 1)
				{
					for (int iter2 = 0; iter2 < size(cpuplayers); iter2++)
					{
						if (iter == iter2)
						{
							continue;
						}

						iterLowestRank = cpuplayers[iter2].returnLowest();
						if (iterLowestRank < lowest)
						{
							lowest = iterLowestRank;
						}


					}
				}
				
				int playerLowest = playerList[0].returnLowest();

				//iterates through the vector of CPU players to find the lowest card among them
				for (vector<player>::iterator CPUIter = playerList.begin(); CPUIter != playerList.end(); CPUIter++)
				{
					playerHand = CPUIter->returnLowest();
					if (playerHand < lowest)
					{
						playerLowest = playerHand;
					}
				}

				if (iterLowestRank > playerLowest)
				{
					iterLowestRank = playerLowest;
				}


				cout << pName << " has ended this round by FOLDING and scoring " << iterLowestRank << " points!" << endl;
				cpuplayers[iter].updateScore(lowest);
				changeAllCardStatus(cardList);
				clearPlayerDecks(playerList);
				clearCPUPlayerDecks(cpuplayers);
				waitForPlayer();
				breakLoop = true;
				break;
			}

			//if cpu player gets a pair of folds break loop will be set to true
			if (breakLoop)
			{
				break;
			}

		}
	}


}

//checks if any of the players or cpu players have reached the target score
bool checkGameOver(vector<player>& playerList, int targetScore, vector<CPUplayer>& cpuplayers)
{
	int pScore = 0;
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		pScore = playerIter->getScore();
		if (pScore >= targetScore)
		{
			return false;
		}

	}

	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{
		pScore = CPUIter->getScore();
		if (pScore >= targetScore)
		{
			return false;
		}

	}


	return true;

}

//after each round this changes all the card status to "inDeck"
void changeAllCardStatus(vector<card>& cardList)
{
	for (vector<card>::iterator cardIter = cardList.begin(); cardIter != cardList.end(); cardIter++)
	{
		cardIter->switchCardStatus("inDeck");
	}
}

//empties all the player cards
void clearPlayerDecks(vector<player>& playerList)
{
	//iterates through each of the players
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		//clears the player card deck
		playerIter->clearPlayerDeck();
	}
}

//clears all the cpu players decks
void clearCPUPlayerDecks(vector<CPUplayer>& CPUPlayerList)
{
	//iterates through each of the players
	for (vector<CPUplayer>::iterator CPUIter = CPUPlayerList.begin(); CPUIter != CPUPlayerList.end(); CPUIter++)
	{
		//clears the player card deck
		CPUIter->clearPlayerDeck();
	}
}

//shows game over menu after target score has been reached
void gameOver(int targetScore, vector<player>& playerList, vector<CPUplayer>& cpuplayers)
{
	//clears th screen and displays the title
	system("CLS");
	displayTitle(targetScore, playerList, cpuplayers);
	waitForPlayer();

	//players score is initialized
	int playerScore = 0;
	string name = "";

	//itersates to check if player has target score and prints out message
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{
		playerScore = playerIter->getScore();
		if (playerScore >= targetScore)
		{
			name = playerIter->getName();
			cout << name << ", It’s game over man!!!" << endl;
			cout << name << " is buying the drinks gentleman!!" << endl;
			break;
		}
	}


	//iterates through cpu playes to chrck if any  has target score and prints out message
	for (vector<CPUplayer>::iterator CPUIter = cpuplayers.begin(); CPUIter != cpuplayers.end(); CPUIter++)
	{
		playerScore = CPUIter->getScore();
		if (playerScore >= targetScore)
		{
			name = CPUIter->getName();
			cout << name << ", Has Lost The Game" << endl;
			break;
		}
	}

}

//makes all the cpu players
void createCPUPlayers(int num, vector<CPUplayer>& cpuplayers)
{
	//checks if the any cpu players are required
	if (num != 0)
	{
		// gets number of players enters and iterates and adds them to the
		for (int i = 0; i < num; i++)
		{
			string name = "CPU" + to_string(i + 1);
			cpuplayers.push_back(CPUplayer(name));
		}
	}

}

string askForString( string question)
{
	cout << "\n" <<   question;
	string userInput = "";
	//cin.ignore();
	while (userInput == "")
	{
		cin >> userInput;
	}

	return userInput;
}
