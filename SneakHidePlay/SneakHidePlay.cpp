#include <iostream>
#include <cTime>
#include <Windows.h>

#pragma region Global variables
HANDLE coutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int levelDiffuclty = 1;
char codeName[20];
int age;
#pragma endregion


int CheckIfNumber(int number, const char* question)
{
	std::cin >> number;
	while (!(number))
	{
		if (number == 0) return 0;
		std::cout << "\nNot a valid number";
		std::cout << "\n" << question << ": ";
		std::cin.clear();
		std::cin.ignore();	
		std::cin >> number;
	}
	return number;
}

void PrintIntro()
{
	
	SetConsoleTextAttribute(coutHandle, 15);
	std::cout << R"(
      .......
  .:::::::::::::.  
 .::'  '''''  '::.				
 :::           :::		Agent Welcome!
 :::           ::: 
 ::'           ':: 
: : /~~~' '~~~\ : :
:(    *  |  *    ):			
'.:     / \     :.'
 ':    (. .)    :' 
  '.  .:::::.  .'
   :  <----->  :   
   '.  ~:::~  .'
     '.  '  .'     
       '''''
)" << "\n";
	// Print welcome statement	
	std::cout << "\nWe've heard great things about you. Let me introduce myself.\nI'm General Friedchicken.\n"
		"We called you here because we need your help to unlock our server rooms.\n"
		"To make a long story short, an ex-employee changed all 5 server room codes.\n"
		"He also left a set of hints for each server room to give us a chance to unlock these doors.\nThis is where you come in.\n"
		"We heard you were really good with numbers and I hope you really are for all our sakes.\n"
		"You will only have 3 chances per lock or else the data will delete from all the servers.\n";
	SetConsoleTextAttribute(coutHandle, 12);
	std::cout << "Remember only 3 chances...\n";
	SetConsoleTextAttribute(coutHandle, 15);
	std::cout << "First things first we need to get you your badge. Lets get some information to put into our database and get you going.\n";
	SetConsoleTextAttribute(coutHandle, 14);
	std::cout << "Code name of choice: ";
	std::cin >> codeName;
	std::cout << "\nYour age: ";
	age = CheckIfNumber(age, "Age: ");
	std::cout << codeName;
	SetConsoleTextAttribute(coutHandle, 15);
	std::cout << ", lets get started with server room " << levelDiffuclty << "\n";
	std::cout << "From the mission files we know:\n";
}

void GameComplete()
{
	std::cout << "\Finally we have all these damn doors unlocked. Thanks for your service " << codeName << "!";
}

bool IsPlayerAnswerCorrect(int playerSum, int playerProduct, int answerSum, int answerProduct, int maxLevel)
{	
	// Check if player's code is correct
	if (playerSum == answerSum && playerProduct == answerProduct)
	{
		levelDiffuclty++;
		if (levelDiffuclty <= maxLevel)
		{
			SetConsoleTextAttribute(coutHandle, 10);
			std::cout << "The code you've entered was correct. The server lock door opens...\n"
				"Lets move on to server room " << levelDiffuclty << "\n\n";
		}
		return true;
	}
	SetConsoleTextAttribute(coutHandle, 12);
	std::cout << "The code you've entered was incorrect.\n";
	return false;
}

void GameHints(int codeSum, int codeProduct)
{
	//Print the hints
	std::cout << "* There are three numbers in the code.\n"
		<< "* If you where to multiple all the number you would get a total of " << codeProduct << ".\n"
		<< "* The sum of the numbers in the code equals " << codeSum << "\n";
	std::cout << "Input the correct code to enter the server room and continue...\n";
}

void PlayGame()
{
	bool isLevelComplete;
	int playerGuessA = 0; 
	int playerGuessB = 0;
	int playerGuessC = 0;
	const int maxLevel = 5;

	PrintIntro();
	

	while (levelDiffuclty <= maxLevel)
	{
		//Secret code 3 number code
		int codeA = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
		int codeB = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
		int codeC = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
		int codeSum = codeA + codeB + codeC;
		int codeProduct = codeA * codeB * codeC;

		GameHints(codeSum, codeProduct);
		SetConsoleTextAttribute(coutHandle, 11);
		std::cout << "First code: ";
		playerGuessA = CheckIfNumber(playerGuessA, "First code: ");
		std::cout << "Second code: ";
		playerGuessB = CheckIfNumber(playerGuessB, "Second code: ");
		std::cout << "Third code: ";
		playerGuessC = CheckIfNumber(playerGuessC, "Third code: ");

		std::cout << "\nCode entered: " << playerGuessA << playerGuessB << playerGuessC << std::endl;

		int playerGuessSum = playerGuessA + playerGuessB + playerGuessC;
		int playerGuessProduct = playerGuessA * playerGuessB * playerGuessC;

		std::cout << "Player guess sum: " << playerGuessSum << std::endl;
		std::cout << "Player guess product: " << playerGuessProduct << std::endl;

		//std::cout << "Code Sum " << codeSum << std::endl;
		//std::cout << "Code Product " << codeProduct << std::endl;

		isLevelComplete = IsPlayerAnswerCorrect(playerGuessSum, playerGuessProduct, codeSum, codeProduct, maxLevel);

		std::cin.clear();
		std::cin.ignore();
	}
	GameComplete(); // Game has been beaten
}


int main()
{
	srand(time(NULL)); // Randomize rand()
	PlayGame();

	return 0;
}

