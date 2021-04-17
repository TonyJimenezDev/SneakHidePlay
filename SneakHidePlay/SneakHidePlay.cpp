#include <iostream>

#pragma region Global variables
char codeName[50];
int age;
#pragma endregion

void PrintIntro()
{

	std::cout << "Welcome agent!\nWe've heard great things about you. Let me introduce myself.\nI'm General Friedchicken.\n" <<
		"We need your help to unlock our server rooms. To cut a long story short, an ex-employee changed all our codes.\n" <<
		"He also left a set of hints for each level to give us a chance to unlock these doors.\nThis is where you come in\n" <<
		"First lets get some information to put into our database.\n" <<
		"Code name of choice: ";
	std::cin >> codeName;
	std::cout << "\nAge: ";
	std::cin >> age;

	std::cout << "\nCode name test: " << codeName;
}

void PlayGame()
{
	//Declare 3 number code
	int codeA = 9;
	int codeB = 1;
	int codeC = 3;
	int playerGuessA, playerGuessB, playerGuessC;

	int codeSum = codeA + codeB + codeC;
	int codeProduct = codeA * codeB * codeC;

	PrintIntro();
	// Print welcome statement
	std::cout << "You're an agent breaking into a server room that is protected by a secret code\n";
	std::cout << "From the mission files you, you know:\n";
	//Print the hints
	std::cout << "* There are three numbers in the code.\n"
		<< "* If you where to multiple all the number you would get a total of 27.\n"
		<< "* The sum of the numbers in the code equals 13.\n";

	std::cout << "Input the correct code to enter the server room and continue...\n";
	std::cout << "First code: ";
	std::cin >> playerGuessA;
	std::cout << "Second code: ";
	std::cin >> playerGuessB;
	std::cout << "Third code: ";
	std::cin >> playerGuessC;
	std::cout << "\nCode entered: " << playerGuessA << playerGuessB << playerGuessC << std::endl;
	// Player's guess = Sum and product
	int playerGuessSum = playerGuessA + playerGuessB + playerGuessC;
	int playerguessProduct = playerGuessA * playerGuessB * playerGuessC;

	std::cout << "Player guess sum: " << playerGuessSum << std::endl;
	std::cout << "Player guess product: " << playerguessProduct << std::endl;

	//std::cout << "Code Sum " << codeSum << std::endl;
	//std::cout << "Code Product " << codeProduct << std::endl;

	// Check if player's code is correct
	if (playerGuessSum == codeSum && playerguessProduct == codeSum)
	{
		std::cout << "The code you've entered was correct. The server lock door opens...\n";
	}
	else {
		std::cout << "The code you've entered was incorrect.\n";
	}
}


int main()
{
	PlayGame();

	return 0;
}

