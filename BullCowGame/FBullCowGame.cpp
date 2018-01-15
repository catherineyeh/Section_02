#pragma once
#include "FBullCowGame.h"
#include <map>

//unreal friendly syntax
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame(){Reset();}//default constructor

//getters

int32 FBullCowGame::GetCurrentTry()const{return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon()const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,5}, {5,5}, {6,7}, {7, 10} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "eat";//must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{
	if (!IsIsogram(Guess)) //if guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if guess has the wrong word length
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();//assume same length as guess
	
	//loop through all letters in the hiddenword
	for (int32 MyHWChar = 0; MyHWChar < HiddenWordLength; MyHWChar++) {
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			//compare each letter against the guess
			if (Guess[GChar] == MyHiddenWord[MyHWChar]) {//if they match then
				if (MyHWChar == GChar) {//if same place
					BullCowCount.Bulls++;//increment bulls
				}
				else {
					BullCowCount.Cows++;//must be a cow
				}	
			}		
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	TMap <char, bool> LetterSeen;//setup map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) { //if letter is in the map
			return false; //we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; //add the letter to the map
		}
		return true; //for instance in cases where /0 is entered
	}
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	//loop through letters
	for (auto Letter : Word) {
//check if it is lowercase
		if (!islower(Letter)) {
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}
