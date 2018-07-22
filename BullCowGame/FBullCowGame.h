#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

//Struct that counts Bulls & Cows. Defaults to 0.
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Status_Not_Set
};

enum class EResetStatus {
	OK,
	No_Word_Found
};

//Class that contains all game logic.
class FBullCowGame {
public:
	FBullCowGame();
	bool IsGameWon() const;
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	EResetStatus Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyWordLength;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};