#pragma once
#include <string>

using FString = std::string; 
using int32 = int;

//struct is a "class"
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0; 
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame {
//methods are public
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon()const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO make a more rich return value
	
	void Reset();//TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString);//counts bulls and cows, and increases try numbers, assuming valid guess 

//variables are private
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};