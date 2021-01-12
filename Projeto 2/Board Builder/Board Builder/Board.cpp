#include<iostream>
#include "Board.h"
#include <Windows.h>
#include <fstream>
#include <string>
#define GREY 112
#define BLACK 7
using namespace std;

//Builds an empty board with the dimensions specified in the arguments
Board::Board(int& width, int& height) {

	this->width = width;
	this->height = height;

	//Setting all matrix elements to an empty space
	for (int i = 0; i < height; i++) {
		vector<string> v;
		matrix.push_back(v);
		for (int j = 0; j < width; j++) {
			matrix[i].push_back(" X");		//The standart element is a empty space as the letter and an 'X' for the orientation
		}
	}

	//Opening the dictionary file
	ifstream dictionaryFile;
	dictionaryFile.open("WORDS.TXT");

	//Tries to open de dictionary file again, if it didn't open in first place
	while (dictionaryFile.fail()) {
		cout << "\nOh, looks like you don't have the file 'WORDS.TXT', which is the dictionary of the available words, in the same folder of your executable file, so do it now to continue and then press ENTER!\n";
		cin.get();
		cin.clear();
		cin.ignore(10000, '\n');
		dictionaryFile.open("WORDS.TXT");
	}

	this->dictionaryLength = 0;

	//Adding all the words in the "WORDS.TXT" file to the dictionary vector
	string s = "--------------------";
	while (getline(dictionaryFile, s)) {
		(this->dictionary).push_back(s);
		this->dictionaryLength += 1;
	}
}

//Return the value of the width
int Board::getWidth() const{
	return this->width;
}

//Return the value of the height
int Board::getHeight() const{
	return this->height;
}

//Return the dictionary's length
int Board::getDictionaryLength() const {
	return this->dictionaryLength;
}

//Function to print the actual board on the screens
void Board::show() const 
{
	//Print the first line of the board
	cout << "  ";
	for (int i = 0; i < width; i++) {
		cout << char(97 + i) << " ";
	}
	cout << endl;

	//Print the rest of the board
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++) {
		SetConsoleTextAttribute(hConsole, BLACK);	//Printing the beginning of the line with black
		cout << char(65 + i) << " ";		
		for (int j = 0; j < width; j++) {
			SetConsoleTextAttribute(hConsole, GREY);		//And printing the rest of the line with grey
			if (j != 0)
				cout << " ";
			cout << matrix[i][j][0];
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, BLACK);	//Returning to the black color
}

//Fuction to check if the new word is in the dictionary
bool Board::checkValidNewWord(string& newWord){

	//Checking every word in the dictionary to see if it is equal to the word that the user wants to write
	for (int i = 0; i < this->dictionaryLength; i++) {
		if ((this->dictionary)[i] == newWord)
			return true;
	}
	return false;
}

//Function to add a new word to the board, return true if the operation is succeeded, or return false and doesn't add the word if it is an invalid operation
bool Board::addNewWord(string& newWord, char& orientation, char& x, char& y) {
	
	int xposition = int(x) - 97;	//Converting the char to an integer readable for the matrix
	int yposition = int(y) - 65;	//Converting the char to an integer readable for the matrix

	//Checking with the word isn't in the limits of the board's dimension (for the horizontal form)
	if (orientation == 'H') {
		if ((xposition + newWord.length()) > (this->width))
			return 0;
	}
	//Checking with the word isn't in the limits of the board's dimension (for the vertical form)
	else {
		if ((yposition + newWord.length()) > (this->height))
			return 0;
	}

	//Checking if with can write this word on the board, considering the other words already written
	for (int i = 0; i < newWord.length(); i++) {

		//For the case of horizontal letters
		if (orientation == 'H') {
			char actualBoardLetter = this->matrix[yposition][xposition + i][0];
			char actualBoardLetterOrientation = this->matrix[yposition][xposition + i][1];

			//Checking if the left side of the first letter is an empty space
			if (i == 0 && xposition != 0)
				if (matrix[yposition][xposition - 1][0] != ' ')
					return 0;

			//Checking if the right side of the last letter is an empty space
			if (i == (newWord.length() - 1) && (xposition + newWord.length()) != this->width)
				if (matrix[yposition][xposition + i + 1][0] != ' ')
					return 0;

			//In the case of having a letter in the way...
			if (actualBoardLetter != ' ') {

				//If it's different than the letter that we want to write, then we can't write the word. Also, it can't intercepts with another horizontal word.
				if (actualBoardLetter != newWord[i] || actualBoardLetterOrientation == 'H')
					return 0;

			}
			//In the case of written in empty spaces, we also should take care of some details
			else {

				//If the word isn't in the first line
				if (yposition != 0)
					//Check to see if all positions above our word are empty spaces
					//NOTE: The only case where it is acceptable is when the letter above is part of another word that intercepts our word. That's why this instruction isn't written in the case of an incertepted letter
					if (this->matrix[yposition - 1][xposition + i][0] != ' ')
						return 0;

				//If the word isn't in the last line
				if (yposition != (this->height - 1))
					//Check to see if all positions below our word are empty spaces
					//NOTE: The only case where it is acceptable is when the letter below is part of another word that intercepts our word. That's why this instruction isn't written in the case of an incertepted letter
					if (this->matrix[yposition + 1][xposition + i][0] != ' ')
						return 0;
			}
		}

		//For the case of vertical letters
		else {
			char actualBoardLetter = this->matrix[yposition + i][xposition][0];
			char actualBoardLetterOrientation = this->matrix[yposition + i][xposition][1];

			//Checking if the up side of the first letter is an empty space
			if (i == 0 && yposition != 0)
				if (matrix[yposition - 1][xposition][0] != ' ')
					return 0;

			//Checking if the down side of the last letter is an empty space
			if (i == (newWord.length() - 1) && (yposition + newWord.length()) != this->height)
				if (matrix[yposition + i + 1][xposition][0] != ' ')
					return 0;

			//In the case of having a letter in the way...
			if (actualBoardLetter != ' ') {

				//If it's different than the letter that we want to write, then we can't write the word. Also, it can't intercepts with another vertical word.
				if (actualBoardLetter != newWord[i] || actualBoardLetterOrientation == 'V')
					return 0;

			}
			//In the case of written in empty spaces, we also should take care of some details
			else {

				//If the word isn't in the first column
				if (xposition != 0)
					//Check to see if all positions at the left of our word are empty spaces
					//NOTE: The only case where it is acceptable is when the letter at the left is part of another word that intercepts our word. That's why this instruction isn't written in the case of an incertepted letter
					if (this->matrix[yposition + i][xposition - 1][0] != ' ')
						return 0;

				//If the word isn't in the last column
				if (xposition != (this->width - 1))
					//Check to see if all positions at the right our word are empty spaces
					//NOTE: The only case where it is acceptable is when the letter at the right is part of another word that intercepts our word. That's why this instruction isn't written in the case of an incertepted letter
					if (this->matrix[yposition + i][xposition + 1][0] != ' ')
						return 0;

			}
		}
	}

	//After passing through all these tests, now the word can be written
	for (int i = 0; i < newWord.length(); i++) {

		//In the case of a horizontal word
		if (orientation == 'H') {
			this->matrix[yposition][xposition + i][0] = newWord[i];			//Writing the character
			this->matrix[yposition][xposition + i][1] = orientation;		//Writing its orientation
		}
		//In the case of a vertical word
		else {
			this->matrix[yposition + i][xposition][0] = newWord[i];			//Writing the character
			this->matrix[yposition + i][xposition][1] = orientation;		//Writing its orientation
		}
	}

	return 1;	//This means that the word was written
}