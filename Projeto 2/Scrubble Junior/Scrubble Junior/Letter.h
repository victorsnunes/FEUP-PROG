#pragma once
#include <fstream>

class Letter {
public:
	Letter(char character);
	Letter(char character, char orientation, int index, int max);
	char getCharacter() const;				//Returns the character of the letter
	char getOrientation() const;			//Returns the orientation of the letter
	bool getIsValid() const;				//Returns the isValid of the letter
	bool getPlaced() const;					//Returns the placed of the letter
	int getIndexH() const;					//Returns the indexH of the letter
	int getIndexV() const;					//Returns the indexV of the letter
	int getMaxH() const;					//Returns the getMaxH of the letter
	int getMaxV() const;					//Returns the getMaxV of the letter
	bool getRecommended() const;			//Returns the recommended of the letter
	void changeOrientation();				//Change the orientation to 'B'
	void setIsValid(bool v);				//Change the value of isValid
	void setIndexH(int index);				//Change the value of indexH
	void setIndexV(int index);				//Change the value of indexV
	void setMaxH(int max);					//Change the value of setMaxH
	void setMaxV(int max);					//Change the value of setMaxV
	void setRecommended(bool recommended);	// Change the value of recommended
	void changePlaced();					//Change placed to true

private:
	char character = ' ';
	bool isValid = false;			//isValid determinates if the player can make a play in this letter of the board, so it's says if this letter is valid to be chosen
	char orientation = 'X';			//V for vertical, H for horizontal, B for both, X for none
	int maxH = 0;					//The total letters of the word horizontally
	int indexH = 0;					//The index of this letter in the word horizontally
	int maxV = 0;					//The total letters of the word vertically
	int indexV = 0;					//The index of this letter in the word vertically
	bool placed = false;			//Checks if the letter is already placed or not
	bool recommended = false;		//Shows that this letter is a possible, a recommended, choice of the actual player
};