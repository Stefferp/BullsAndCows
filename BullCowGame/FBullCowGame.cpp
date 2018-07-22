#pragma once
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EResetStatus FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "donkey";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return EResetStatus::OK;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (IsIsogram(Guess) == false) {
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (IsLowercase(Guess) == false) {
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BCCount;
	for (int32 i = 0; i < GetHiddenWordLength(); i++) {
		for (int32 j = 0; j < GetHiddenWordLength(); j++) {
			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j) {
					BCCount.Bulls++;
				}
				else {
					BCCount.Cows++;
				}
			}
		}
	}
	if (BCCount.Bulls == GetHiddenWordLength()) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BCCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2) return true;
	TMap<char, bool> LetterSeen;
	for (char Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == true) 
			return false;
		else 
			LetterSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (char Letter : Word) {
		if (!islower(Letter))
			return false;
	}
	return true;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> MaxTriesPerLength {
		{ 3, 3 },
		{ 4, 5 },
		{ 5, 7 },
		{ 6, 8 }
	};
	return MaxTriesPerLength[GetHiddenWordLength()];
}