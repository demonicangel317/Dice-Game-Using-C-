//all header file inclusions
#include <fstream>
#include <iostream>
#include<sstream>
#include "card.h"
#include "player.h"
#include "pairs.h"

using namespace std;

//function list

void playContinuousPairs();
void setNumPlayer(vector<player>* vectorList, int* score);
void createCardDeck(vector<card>* vectorList);
void assignPlayerCards(vector<player>& playerList, vector<card>& cardList);
void breakTies(vector<player>& playerList, vector<card>& cardList, int lowest);
void checkTies(vector<player>& playerList, vector<card>& cardList);
void beginRound(vector<player>& playerList, vector<card>& cardList, int score);
void displayTitle(int score, vector<player>& playerList);
void beginPlayerRotation(vector<player>& playerList, vector<card> cardList, int score, int endIndex);
void changeAllCardStatus(vector<card>& cardList);
void clearPlayerDecks(vector<player>& playerList);
bool checkGameOver(vector<player>& playerList, int targetScore);
void gameOver(int targetScore, vector<player>& playerList);
int beginFirstRound(vector<player>& playerList, vector<card> cardList, int score);






//Main Game Loop
void playContinuousPairs()
{

	vector<player> players;
	vector<card> cardDeck;
	int targetScore = 0;
	bool isGameOver = false;

	//makes the card deck required
	createCardDeck(&cardDeck);

	//For the first step I set the number of players and set their names
	setNumPlayer(&players, &targetScore);

	beginRound(players, cardDeck, targetScore);

	//displayTitle(targetScore, players);

	//cout << cardDeck[1].displayCardVisRep();
	/*
	for (int i = 0; i < size(players); i++)
	{
		string name = players[i].getName();
		cout << name << endl;
	}
	*/
	gameOver(targetScore, players);

}

//Used to set the number of players in the vecotr and set the target score
void setNumPlayer(vector<player>* vectorList, int* score)
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

	(*score) = (60 / numPlayers) + 1;


	//Now to get the name of all the players
	for (int i = 0; i < numPlayers; i++)
	{
		string tempName = "";
		cout << "Enter name of player " << (i + 1) << " : ";
		cin >> tempName;
		vectorList->push_back(player(tempName));
	}

	waitForPlayer();




}

//display the title for each turn
void displayTitle(int score, vector<player>& playerList)
{
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "                           Pairs                               " << endl;
	cout << "                      Target Score is " << score << "          " << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

	string name = "";
	int playerScore = 0;

	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end(); playerIter++)
	{

		name = playerIter->getName();
		playerScore = playerIter->getScore();

		cout << "Name : " << name << "\tScore : " << playerScore << endl;
		cout << "Hand : ";
		playerIter->displayPlayerDeck();

		cout << endl << endl;
	}
}


//starts round and assigns each player a card
void assignPlayerCards(vector<player>& playerList, vector<card>& cardList)//gets the references of player and crad vectors
{
	//seeds random values
	srand(unsigned(time(NULL)));
	int randNum = 0;
	string status = "";

	system("CLS");
	cout << "Assigning New Cards" << endl;
	system("pause");
	system("CLS");


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

		
}


//checks if players are tied to the lowest card
void checkTies(vector<player>& playerList, vector<card>& cardList)
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

	//checks if more than one player has the lowest card
	if (checkNumLowest > 1)
	{
		//if more than one players are tied then the program jumps to break the ties
		breakTies(playerList, cardList, lowest);
	}

}

//if the players are tied for the lowest card then this fuction is called to break the ties
void breakTies(vector<player>& playerList, vector<card>& cardList, int lowest)
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

	checkTies(playerList, cardList);
}

//begins the round by calling other functions
void beginRound(vector<player>& playerList, vector<card>& cardList, int score)
{

	//assigns the players the cards
	assignPlayerCards(playerList, cardList);

	//checks if the assigned cards are tied and breaks an ties
	checkTies(playerList, cardList);

	int endIndex = beginFirstRound(playerList, cardList, score);

	while (checkGameOver(playerList, score))
	{
			
		//start rotating turns of the player starting from the lowest

		beginPlayerRotation(playerList, cardList, score, endIndex);
	}




}

//begins rotating turns 
int beginFirstRound(vector<player>& playerList, vector<card> cardList, int score)
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
	//iterartes through the player list indefinitly till a pair is formed
	int endIndex = 0;
	for (int iter = startIndex; iter <= size(playerList); iter++)
	{
		if (iter == (size(playerList)))
		{
			iter = 0;
		}


		waitForPlayer();
		displayTitle(score, playerList);
		playerName = playerList[iter].getName();
		userInput = askForString(playerName, "Will you [H]it, [F]old or [Q]uit:");

		if (playerList[iter].getNumCards() == 0)
		{
			userInput = "H";
		}
		
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
			int randNum = 0;
			string status = "";
			int newCardRank = 0;
			bool isPairformed = false;
			while (true)
			{
				randNum = rand() % 54;
				status = cardList[randNum].getCardStatus();
				if (status == "inDeck")
				{
					cardList[randNum].displayCardVisRep();
					playerList[iter].addCardToDeck(cardList[randNum]);
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
				displayTitle(score, playerList);
				string pName = playerList[iter].getName();
				cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
				playerList[iter].changeDeckCardStatus();
				playerList[iter].clearPlayerDeck();
				endIndex = iter;
				break;
			}



		}

		//if the player chhoses to fold
		if (userInput == "F" || userInput == "f")
		{
			cout << "Choose which card you want to select from other players deck (Enter card rank) : " << endl;
			int playerChoice = 0;
			cin >> playerChoice;

			bool iswithinDeck;
			//iterates through every player in the ector
			while (true)
			{
				int iterLowestRank = 0;
				for (int iter2 = 0; iter2 < size(playerList); iter2++)
				{
					if (iter == iter2)
					{
						continue;
					}

					iswithinDeck = playerList[iter2].withinPlayerDeck(playerChoice);
					if (iswithinDeck)
					{
						break;
					}

				}

				if (!iswithinDeck)
				{
					cout << "Please enter a card that is valid :";
					cin >> playerChoice;
				}
				else 
				{
					break;
				}

				
			}

			string pName = playerList[iter].getName();
			cout << pName << " has ended this round by FOLDING and scoring " << playerChoice << " points!" << endl;
			playerList[iter].updateScore(playerChoice);
			playerList[iter].changeDeckCardStatus();
			playerList[iter].clearPlayerDeck();
			endIndex = iter;
			break;
			
		}


	}

	return endIndex;
	
}

//checks if target score has been reached
bool checkGameOver(vector<player>& playerList, int targetScore)
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

	return true;

}

//displays game over details
void gameOver(int targetScore, vector<player>& playerList)
{
	system("CLS");
	displayTitle(targetScore, playerList);
	waitForPlayer();
	int playerScore = 0;
	string name = "";
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
}

//gets end index and iterates through players until target score is reached
void beginPlayerRotation(vector<player>& playerList, vector<card> cardList, int score, int endIndex)
{
	for (int iter = endIndex; iter <= size(playerList); iter++)
	{
		if (iter == (size(playerList)))
		{
			iter = 0;
		}


		waitForPlayer();
		displayTitle(score, playerList);
		string playerName = playerList[iter].getName();
		string userInput = "";

		if (playerList[iter].getNumCards() == 0)
		{
			cout << "As " << playerList[iter].getName() << " currently has no card  will by default take a hit"<< endl;
			userInput = "H";
		}
		else
		{
			userInput = askForString(playerName, "Will you [H]it, [F]old or [Q]uit:");
		}

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
			int randNum = 0;
			string status = "";
			int newCardRank = 0;
			bool isPairformed = false;
			while (true)
			{
				randNum = rand() % 54;
				status = cardList[randNum].getCardStatus();
				if (status == "inDeck")
				{
					cardList[randNum].displayCardVisRep();
					playerList[iter].addCardToDeck(cardList[randNum]);
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
				displayTitle(score, playerList);
				string pName = playerList[iter].getName();
				cout << pName << " ended this round with a Pair scoring " << newCardRank << " points!" << endl;
				playerList[iter].changeDeckCardStatus();
				playerList[iter].clearPlayerDeck();
				endIndex = iter;
				break;
			}



		}

		//if the player chhoses to fold
		if (userInput == "F" || userInput == "f")
		{
			cout << "Choose which card you want to select from other players deck (Enter card rank) : " << endl;
			int playerChoice = 0;
			cin >> playerChoice;

			bool iswithinDeck;
			//iterates through every player in the ector
			while (true)
			{
				int iterLowestRank = 0;
				for (int iter2 = 0; iter2 < size(playerList); iter2++)
				{
					if (iter == iter2)
					{
						continue;
					}

					iswithinDeck = playerList[iter2].withinPlayerDeck(playerChoice);
					if (iswithinDeck)
					{
						break;
					}

				}

				if (!iswithinDeck)
				{
					cout << "Please enter a card that is valid :";
					cin >> playerChoice;
				}
				else
				{
					break;
				}


			}

			string pName = playerList[iter].getName();
			cout << pName << " has ended this round by FOLDING and scoring " << playerChoice << " points!" << endl;
			playerList[iter].updateScore(playerChoice);
			playerList[iter].changeDeckCardStatus();
			playerList[iter].clearPlayerDeck();
			endIndex = iter;
			break;

		}


	}
}


