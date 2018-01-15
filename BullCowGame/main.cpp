/* this is the console executable, that makes use of the Bull Cow Class
This acts as the view in a MVC patter and is responsible for all user interaction. For game logic see the FBullCowGame
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly 
using FText = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game, which we replace across plays

int main(){
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;
}

void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "()___()" << std::endl;
	std::cout << "< @ @ >" << std::endl;
	std::cout << " |   |" << std::endl;
	std::cout << " {o_o}" << std::endl;
	std::cout << "  (| )" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << "-word isogram?" << std::endl;
	return;
}
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop asking for guesses while the game 
	//is NOT won and there are still tries left
	while ( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ) {
		FText Guess = GetValidGuess();
		
		//Submit valid guess and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n"; 
	}
	PrintGameSummary();
	return;	
}

//loop continually until user gets valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<" of "<<BCGame.GetMaxTries();
		std::cout << ". Enter your guess: \n";
		
		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			//assume valid guess
			break;
		}
		
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word(y/n)? \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return(Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well done - You won!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}
