/*
	This is the main executable file, which acts as a view in the MVC architecture
*/
#include<iostream>
#include<string>
#include"FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//function prototype outside a class
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;//instantiate the game

//entry point for application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
		BCGame.Reset();
	}
	while (AskToPlayAgain());
	
	return 0;//exit the application
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//loop asking for guesses while the
	//game is NOT won
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();
		//submit the validated guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print out bulls and cows
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl << "Cows: " << BullCowCount.Cows;
		std::cout << "\n\n";
	}
	PrintGameSummary();
}
//ask the player to guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<" of "<<BCGame.GetMaxTries()<< " .Enter your guess:";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters!\n";
			break;
		default:
			//assuming correct guess
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);//keep looping until valid input is received
	return Guess;
}
//introduce the game
void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cow\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter ";
	std::cout << "word I'm thinking of?\n\n";
	return;
}
bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you want to play again?(y/n)" << std::endl;
	std::getline(std::cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y')
		return true;
	else
		return false;
}
void PrintGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "\n\nWELL DONE! YOU'VE WON THE GAME!\n\n";
	}
	else
	{
		std::cout << "\n\nToo bad! Better luck next time!\n\nThe word was:";
		BCGame.PrintHiddenWord();
	}
}