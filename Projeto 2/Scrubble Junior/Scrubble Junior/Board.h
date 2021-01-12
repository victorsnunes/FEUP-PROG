#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include "Letter.h"

//The board class builds a board which stores, in the form of a matrix, another class called Letter, which contains much more important information than just a standart 'char'
class Board
{
public:
	Board(std::string &filename);		//Constructor of the board that receives a string, which is the filename that is going to open to create the board
	int getWidth() const;				//Returns the width of the matrix
	int getHeight() const;				//Returns the height of the matrix
	void show() const;					//Prints the board, as it is at this moment, in the screen
	Letter getLetter(int yposition, int xposition);								//Returns the Letter (not simply the char) stored in that position in the matrix
	bool play(char& character, char& yposition, char& xposition);					//This function will make a play for the player. It will return true and make the play if it's valid, or it won't do anything and return false if it's invalid
	int checkCompletedWord(char& yposition, char& xposition);						//This fuction, based in the position of the letter just played, will check if none or one or two words were completed, and return the quantity of points. It also turns to valid the letters that should be valid, based in the letter just played, updating the board
	void recommendLetter(int& yposition, int& xposition, bool recommended);		//This function will change the recommended state the board letter in that position
private:
	int width, height;								//The width and the height of the board
	std::vector <std::vector<Letter>> matrix;		//The matrix itself that stores the letters
};