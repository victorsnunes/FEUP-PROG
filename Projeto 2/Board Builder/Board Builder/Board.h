#pragma once
#include <vector>
#include <string>

class Board
{
public:
	Board(int& width, int& height);		//Builds an empty board with the dimensions specified in the arguments
	int getWidth() const;				//Return the value of the width
	int getHeight() const;				//Return the value of the height
	int getDictionaryLength() const;	//Return the dictionary's length
	void show() const;					//Function to print the actual board on the screens
	bool addNewWord(std::string& newWord, char& orientation, char& xposition, char& yposition);		//Function to add a new word to the board, return true if the operation is succeeded, or return false and doesn't add the word if it is an invalid operation
	bool checkValidNewWord(std::string& newWord);												//Fuction to check if the new word is in the dictionary

private:
	int width, height;							//The values of the width and height of the board
	std::vector<std::string> dictionary;		//A vector with all valid words to play, it's like a dictionary
	std::vector <std::vector<std::string>> matrix;		//Matrix of the board elements. Each element will be a 2 character string, the first character is the letter itself, and the second is the orientation
	int dictionaryLength;						//The length of the vector dictionary
};