//all header file inclusions
#include "pairs.h"
#include "continuousPairs.h"

//Main function
int main()
{

	//display the game rules
	readFromFile("howToPlayPairs.txt");

	//seed numbers
	srand(unsigned(time(NULL)));

	//wait for the player and clear the screen
	waitForPlayer();

	string slectGametype = askForString("Please enter if you want to play [O]riginal players or [C]ontinuous players:");

	while (slectGametype != "O" && slectGametype != "o" && slectGametype != "C" && slectGametype != "c")	
	{
		slectGametype = askForString("Please enter O (Original) or C (Continuous)");
	}
	
	waitForPlayer();
	if (slectGametype == "O" || slectGametype == "o")
	{
		playPairs();
	}
	else 
	{
		playContinuousPairs();
	}

	//play the pairs game
	

	return 0;
}


