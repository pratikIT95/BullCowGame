/*This class is the game class which defines
the basic functionality of the game */
#pragma once
#include<string>
//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;
//all values initialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
class FBullCowGame {
public:
	FBullCowGame();
	FString GetIsogramFromDictionary();
	void Reset();//TODO add rich return type
	FBullCowCount SubmitValidGuess(FString);
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;//TODO add rich return type
	bool isGameWon() const;
	void PrintHiddenWord();
	//checks bulls and cows and increments current try
	
private:
	int32 MyCurrentTry;
	bool bGameIsWon;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};