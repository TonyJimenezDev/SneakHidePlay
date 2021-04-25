#include <iostream>
#include <cTime>
#include <Windows.h>
#include <string>

#pragma region Global variables
HANDLE coutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int levelDiffuclty = 1;
char codeName[20];
int age;
int playerGuesses = 0;
#pragma endregion

#pragma region Utilities
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

void SlowDownText(const std::string str, int delayTime)
{
	for (int i = 0; i != str.size(); i++)
	{
		std::cout << str[i];
		Sleep(delayTime);
	}
}

void ClearScreen(int delayTime)
{
	Sleep(delayTime);
	std::cout << "\x1B[2J\x1B[H";
}
#pragma endregion

void Animation()
{
	std::string speakingFace = R"end(
      .......
  .:::::::::::::.
 .::'  '''''  '::.
 :::           :::		Welcome Agent!
 :::           :::					Hopefully your day is going well.
 ::'           '::					Unfortunately we can't say the same...
: : /~~~' '~~~\ : :
:(    *  |  *    ):
'.:     / \     :.'
 ':    (. .)    :'
  '.  .:::::.  .'
   :  <[   ]>  :
   '.  ~:::~  .'
     '.  '  .'
       '''''
)end";
	std::string blinkingFace = R"end(
      .......
  .:::::::::::::.
 .::'  '''''  '::.
 :::           :::		Welcome Agent!
 :::           :::					Hopefully your day is going well.
 ::'           '::					Unfortunately we can't say the same...
: : /~~~' '~~~\ : :
:(    -  |  -    ):
'.:     / \     :.'
 ':    (. .)    :'
  '.  .:::::.  .'
   :  <----->  :
   '.  ~:::~  .'
     '.  '  .'
       '''''
)end";

	std::string face = R"end(
      .......          
  .:::::::::::::.      
 .::'  '''''  '::.     
 :::           :::     
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
)end";
	const char* newLine = "\n"; // used to keep the placing of string

	// Resets the screen and cursor. while pasting a new substring
	for (int i = 1; i <= 35;i++)
	{
		if (i % 3 == 0) std::cout << blinkingFace;
		else std::cout << speakingFace;
		ClearScreen(250);
	}

	std::cout << face;
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			std::cout << newLine;
		}
		std::cout << face.substr(24 * i, 363);
		ClearScreen(10);
	}
}

void PrintIntro()
{
	Animation();
	SetConsoleTextAttribute(coutHandle, 15);

	// Print welcome statement	
	SlowDownText("\nWe've heard great things about you. Let me introduce myself.\nI'm General Friedchicken.\n"
		"We called you here because we need your help to unlock our server rooms.\n"
		"To make a long story short, an ex-employee changed all 5 server room codes.\n"
		"He also left a set of hints for each server room to give us a chance to unlock these doors.\nThis is where you come in.\n"
		"We heard you were really good with numbers and I hope you really are for all our sakes.\n"
		"You will only have 5 chances per lock or else the data will delete from all the servers.\n", 2);
	SetConsoleTextAttribute(coutHandle, 12);
	SlowDownText("Remember only 5 chances...\n", 100);
	SetConsoleTextAttribute(coutHandle, 15);
	SlowDownText("First things first we need to get you your badge. Lets get some information to put into our database and get you going.\n", 2);
	SetConsoleTextAttribute(coutHandle, 14);
	SlowDownText("Code name of choice: ", 2);
	std::cin >> codeName;
	SlowDownText("\nYour age: ", 2);
	age = CheckIfNumber(age, "Age: ");
	SlowDownText(codeName, 2);
	SetConsoleTextAttribute(coutHandle, 15);
	SlowDownText(", lets get started with server room ", 2);
	SlowDownText(std::to_string(levelDiffuclty), 2);
	SlowDownText("\nFrom the mission files we know:\n", 2);
}
void GameOver() 
{
	// ASCII Art needed and more 
	SetConsoleTextAttribute(coutHandle, 12);
	SlowDownText("\nYou have failed to enter the correct code in less than 5 turns. All data in the server room has been wiped. GAME OVER", 2);
}

void GameWon()
{
	// ASCII Art needed and more 
	SlowDownText("\nFinally we have all these damn doors unlocked. Thanks for your service ", 2); 
	SlowDownText(codeName, 2); 
	std::cout << "!";
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
			SlowDownText("The code you've entered was correct. The server lock door opens...\n"
				"Lets move on to server room ", 2);
			SlowDownText(std::to_string(levelDiffuclty), 2);
			std::cout << "\n\n";
		}
		return true;
	}
	SetConsoleTextAttribute(coutHandle, 12);
	std::cout << "The code you've entered was incorrect.\n";
	playerGuesses++;
	return false;
}

void GameHints(int codeSum, int codeProduct)
{
	//Print the hints
	SlowDownText("* There are three numbers in the code.\n* The sum of the numbers in the code equals ", 2);
	SlowDownText(std::to_string(codeSum), 2);
	SlowDownText("\n* If you where to multiple all the number you would get a total of ", 2);
	SlowDownText(std::to_string(codeProduct), 2);
	SlowDownText("\nInput the correct code to enter the server room and continue...\n", 2);
}

void PlayGame()
{
	bool isLevelComplete = true;
	int playerGuessA = 0, playerGuessB = 0, playerGuessC = 0;
	int codeA = 0, codeB = 0, codeC = 0;
	int codeSum = 0, codeProduct = 0;
	const int maxLevel = 5;
	
	PrintIntro();

	while (levelDiffuclty <= maxLevel)
	{
		if (isLevelComplete)
		{
			srand(int(NULL)); // Randomize rand()
			//Secret code 3 number code
			codeA = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
			codeB = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
			codeC = rand() % ((4 + levelDiffuclty) * levelDiffuclty);
			codeSum = codeA + codeB + codeC;
			codeProduct = codeA * codeB * codeC;
			GameHints(codeSum, codeProduct);
		}

		SetConsoleTextAttribute(coutHandle, 11);
		std::cout << "First code: ";
		playerGuessA = CheckIfNumber(playerGuessA, "First code: ");
		std::cout << "Second code: ";
		playerGuessB = CheckIfNumber(playerGuessB, "Second code: ");
		std::cout << "Third code: ";
		playerGuessC = CheckIfNumber(playerGuessC, "Third code: ");

		SlowDownText("\nCode entered: ", 2);
		std::cout << playerGuessA << playerGuessB << playerGuessC << std::endl;

		int playerGuessSum = playerGuessA + playerGuessB + playerGuessC;
		int playerGuessProduct = playerGuessA * playerGuessB * playerGuessC;

		SlowDownText("Player guess sum: ", 2);
		std::cout << playerGuessSum << std::endl;
		SlowDownText("Player guess product: ", 2); 
		std::cout << playerGuessProduct << std::endl;

		isLevelComplete = IsPlayerAnswerCorrect(playerGuessSum, playerGuessProduct, codeSum, codeProduct, maxLevel);
		SetConsoleTextAttribute(coutHandle, 15);
		if (playerGuesses >= 5) break;
		std::cin.clear();
		std::cin.ignore();
	}
	if (playerGuesses >= 5) GameOver(); 
	else GameWon(); 
}


int main()
{
	PlayGame();

	return 0;
}

