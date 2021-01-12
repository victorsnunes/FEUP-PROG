#pragma once
#include <vector>
#include <Windows.h>
#define RED 4
#define BLACK 7

class Player
{
public:
	void addNewCharacter(char l);					//Adds a new character to the player's hand
	bool addScoringChips(int& points);				//This function adds points to the scoring chips of the player. If no points are added, if returns false, otherwise it returns true.
	int getScoringChips();							//Returns the scoring chips of the player
	void showHand();								//Shows the hand of the player
	int getHandLength();							//Returns the the length of the player's hand
	std::vector<char> getHand();					//Returns the vector of the player's hand
	void removeCharacter(int& index);				//Removes a letter from the player's hand in a certain index
	int checkCharacterInHand(char& characterChosen);	//Checks if a character is in the player's hand, and if it isn't, it keep asking until it gets a valid answer. Then it returns the index of that letter in the player's hand

private:
	int scoringChips = 0;			//The points of the player
	std::vector<char> hand;			//The player's hand
	int handLength = 0;				//The Length of the player's hand
};