#pragma once
#include "FBullCowGame.h"
#include<map>
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;
FBullCowGame::FBullCowGame()
{
	Reset();
}

FString FBullCowGame::GetIsogramFromDictionary()
{
	int32 index;
	FString s;
	std::vector <FString> Isograms;
	std::ifstream in("Isograms.txt");
	if (!in) 
	{
		std::cout << "Cannot open input file.\n";
		return FString("isogram");
	}
	while (in>>s)
	{
		Isograms.push_back(s);
	}
	srand(time(NULL));
	index = rand() % Isograms.size();
	return Isograms.at(index);
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD=GetIsogramFromDictionary();
	bGameIsWon = false;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,4} , {4,7} , {5,10}, {6,15} , {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}
//Receives a VALID guess and returns number of bulls and cows, incrementing guess
int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

void FBullCowGame::PrintHiddenWord()
{
	std::cout << MyHiddenWord << std::endl;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//consider 0 or 1 letter words as isogram
	if (Guess.length() <= 1) { return true; }

	//setup map 
	TMap <char, bool> LetterSeen;

	for (auto Letter : Guess)//loop through all letters
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])//if letter is in the map
		{
			return false;//it is NOT an isogram
		}
		//otherwise
		{
			LetterSeen[Letter] = true;//add letter to the map
		}
			
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (Guess.length()<=1)
	{
		return false;
	}
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if word isn't isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	//if word isn't in lowercase
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	//if word length is incorrect
	else if (Guess.length()!=GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//otherwise
	else
	{
		return EGuessStatus::OK;
	}	
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all the letters
	int32 WordLength = GetHiddenWordLength();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//check for bulls and cows by comparing with hidden words
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (MyHiddenWord[MHWChar] == Guess[GChar]) {
				//if they are in the same place 
				if (MHWChar == GChar)
				{
					//increment bulls
					BullCowCount.Bulls++;
				}	
				//else
				else
				{
					//increment cows
					BullCowCount.Cows++;
				}		
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}
