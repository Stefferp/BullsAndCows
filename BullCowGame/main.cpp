#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain() == true);
	return 0;
}

//The main loop that plays the game
void PlayGame()
{
	BCGame.Reset();
	while (BCGame.IsGameWon() == false && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();
		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "You got " << BCCount.Bulls << " bulls and ";
		std::cout << BCCount.Cows << " cows." << std::endl << std::endl;
	}
}

//Get guesses from the player through keyboard input
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Status_Not_Set;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "That's not an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only enter lower case letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "That's not the right length, please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

//Ask if the player wants to play again at the end of the game
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline( std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

//Introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

//Prints a summary after a game (player won or lost)
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WON!\n";
	}
	else { std::cout << "You lost the game...\n"; }
	return;
}