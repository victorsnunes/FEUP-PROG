#include<iostream>
#include "Board.h"
#include <fstream>
#include <string>
#define GREY 112
#define BLACK 7
#define RED 124
#define GREEN 122
using namespace std;

//Constructor of the board that receives a string, which is the filename that is going to open to create the board
Board::Board(string& filename) {

	//Opening the file
	ifstream boardFile;
	boardFile.open(filename);

	//If it fails to open, try to type the name again
	while (boardFile.fail()) {
		cout << "\nNo file was found with this name, try to type it again (remember to write '.txt' at the end):\n\n";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> filename;
		boardFile.open(filename);
	}

	//get the first line of the board file, which is the dimensions of the board
	string dimensions;
	getline(boardFile, dimensions);

	//This is the case which the width is a 1 digit number
	if (dimensions[1] == ' ') {

		this->width = int(dimensions[0]) - 48;		//We should subtract 48 because "int(dimensions[0])" will return the ASCII code of the digit number, and not the number itself. 48 is the ASCII code of '0', so doing "int(dimensions[0]) - 48" will give as the result wanted

		//This is the case height the width is a 1 digit number
		if (dimensions[5] == '\0')
			this->height = int(dimensions[4]) - 48;

		//This is the case height the width is a 2 digit number
		else
			this->height = 10 + int(dimensions[5]) - 48;
	}

	//This is the case which the width is a 2 digit number
	else {

		this->width = 10 + int(dimensions[1]) - 48;

		//This is the case height the width is a 1 digit number
		if (dimensions[6] == '\0')
			this->height = int(dimensions[5]) - 48;

		//This is the case height the width is a 2 digit number
		else
			this->height = 10 + int(dimensions[6]) - 48;
	}

	//Setting all matrix elements to an empty space
	for (int i = 0; i < height; i++) {
		vector<Letter> v;
		matrix.push_back(v);
		for (int j = 0; j < width; j++) {
			matrix[i].push_back(' ');		//Remeber that the class Letter has a constructor that receives only a character, especifically for the situation of the empty spaces
		}
	}

	//This string will store the word, position and orientation as "Yx O WORD" form
	string position;

	//Repeat this cycle to read all the words
	while (getline(boardFile, position)) {

		//Store the Xposition, and coverting it from char to an integer readable for the matrix
		int yposition = int(position[0]) - 65;

		//Store the Yposition, and coverting it from char to an integer readable for the matrix
		int xposition = int(position[1]) - 97;

		//Store the word itself
		string word = position.substr(5, 20);	//20 is the maximum size of a word
		
		//If the orientation is 'H', write the word on the board horizontally
		if (position[3] == 'H') {

			for (int i = 0; i < word.length(); i++) {

				Letter l(word[i], position[3], i, word.length());	//Remember that the constructor structure of the class Letter is "Letter(char character, char orientation, int index, int max)"

				//This is the case which it already have a letter written in that position. Of course it's the same character but it has some diferent attributes
				if (matrix[yposition][xposition + i].getOrientation() != 'X') {

					//So, if we're writting a new word horizontally and we step into a letter in the way, this letter should necessarily be part of a previous VERTICAL word
					//Therefore, this letter will now be an 'B' orientation, and we're going to write the horizontal attributes (indexH, maxH) in it, and we know it already has the vertical atrtributes.
					//See that the 'B' (Both) orientation has vertical and horizontal attributes

					matrix[yposition][xposition + i].changeOrientation();
					matrix[yposition][xposition + i].setIndexH(i);
					matrix[yposition][xposition + i].setMaxH(word.length());
					if (i == 0)		//And if it's the beginning of a word, turn this letter into valid
						matrix[yposition][xposition + i].setIsValid(true);
				}
				//This is the standart case which the letter is going to be written over an empty space
				else
					matrix[yposition][xposition + i] = l;
			}
		}
		//If the orientation is 'V', write the word on the board vertically
		else {

			for (int i = 0; i < word.length(); i++) {

				Letter l(word[i], position[3], i, word.length());

				//This is the case which it already have a letter written in that position. Of course it's the same character but it has some diferent attributes
				if (matrix[yposition + i][xposition].getOrientation() != 'X') {

					//So, if we're writting a new word vertically and we step into a letter in the way, this letter should necessarily be part of a previous HORIZONTAL word
					//Therefore, this letter will now be an 'B' orientation, and we're going to write the vertical attributes (indexV, maxV) in it, and we know it already has the horizontal atrtributes.
					//See that the 'B' (Both) orientation has vertical and horizontal attributes

					matrix[yposition + i][xposition].changeOrientation();
					matrix[yposition + i][xposition].setIndexV(i);
					matrix[yposition + i][xposition].setMaxV(word.length());
					if (i == 0)		//And if it's the beginning of a word, turn this letter into valid
						matrix[yposition + i][xposition].setIsValid(true);
				}
				//This is the standart case which the letter is going to be written over an empty space
				else
					matrix[yposition + i][xposition] = l;
			}
		}
	}

	//Finally, closing the board file
	boardFile.close();
}

//Returns the Letter (not simply the char) stored in that position in the matrix
Letter Board::getLetter(int yposition, int xposition) {
	return this->matrix[yposition][xposition];
}

//Return the value of the width
int Board::getWidth() const{
	return this->width;
}

//Return the value of the height
int Board::getHeight() const{
	return this->height;
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

		SetConsoleTextAttribute(hConsole, BLACK);
		cout << char(65 + i) << " ";	//prints the beginning letter of the line, in other words, the Y column

		for (int j = 0; j < width; j++) {
			SetConsoleTextAttribute(hConsole, GREY);		//Changing the color of the board to grey 
			if (this->matrix[i][j].getPlaced())
				SetConsoleTextAttribute(hConsole, RED);		//Changing to red the color of the letters placed on the board
			if (this->matrix[i][j].getRecommended())
				SetConsoleTextAttribute(hConsole, GREEN);	//Changing to green the color of the letters recommended on the board
			if (j != 0)		//The first letter of each line don't have an addicional empty space before it, for visual purposes
				cout << " ";
			cout << (this->matrix[i][j]).getCharacter();
			
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, BLACK);		// Returning the color back to black again
}

//This function will make a play for the player. It will return true and make the play if it's valid, or it won't do anything and return false if it's invalid
bool Board::play(char& character, char& y, char& x) {

	int yposition = int(y) - 65;		//Converting the character to a readble integer for the matrix
	int xposition = int(x) - 97;		//Converting the character to a readble integer for the matrix
	Letter boardLetter = matrix[yposition][xposition];

	/*Don't make the play if:
	- The character of the player isn't the same as the board position requires.
	OR
	- The letter in the that position on the board isn't valid yet*/
	if (boardLetter.getCharacter() != character || !boardLetter.getIsValid())
		return false;

	//Make the play
	matrix[yposition][xposition].changePlaced();
	return 1;
}

//This fuction, based in the position of the letter just played, will check if none or one or two words were completed, and return the quantity of points. It also turns to valid the letters that should be valid, based in the letter just played, updating the board
int Board::checkCompletedWord(char& y, char& x) {

	int points = 0;
	int yposition = int(y) - 65;	//Converting the character to a readble integer for the matrix
	int xposition = int(x) - 97;	//Converting the character to a readble integer for the matrix
	Letter boardLetter = matrix[yposition][xposition];

	//If the letter has an orientation of 'H' or 'B', we're going to check the horizontal word is now completed
	if (boardLetter.getOrientation() == 'H' || boardLetter.getOrientation() == 'B') {
		
		bool wordCompleted = true;

		//This loop will see all the letters of the word to check if it is complete and to validate the letters that should be valid
		for (int i = 0; i < boardLetter.getMaxH(); i++) {

			//Check if the actual letter is placed in the board. If it isn't, then the word isn't completd and we break the loop
			if (!matrix[yposition][xposition - boardLetter.getIndexH() + i].getPlaced()) {
				wordCompleted = false;
				break;
			}

			//If this loop didn't break so far, it means that all the letters of this horizontal words are placed correctly, so we can change the status of the next one to valid (unless it's the end of the word or the following is already placed)
			if ((i >= boardLetter.getIndexH()) && (i != boardLetter.getMaxH() - 1) && !matrix[yposition][xposition - boardLetter.getIndexH() + i + 1].getPlaced())
				this->matrix[yposition][xposition - boardLetter.getIndexH() + i + 1].setIsValid(true);
			
		}

		if (wordCompleted)	//If the word is completed, add 1 point
			points += 1;
	}
	//NOTE: There's no ELSE statement, only two IFs, for the case of 'B', which requises to check both the horizontal and the vertical word

	//If the letter has an orientation of 'H' or 'B', we're going to check the vertical word is now completed
	if (boardLetter.getOrientation() == 'V' || boardLetter.getOrientation() == 'B') {

		bool wordCompleted = true;

		//This loop will see all the letters of the word to check if it is complete and to validate the letters that should be valid
		for (int i = 0; i < boardLetter.getMaxV(); i++) {

			//Check if the actual letter is placed in the board. If it isn't, then the word isn't completd and we break the loop
			if (!matrix[yposition - boardLetter.getIndexV() + i][xposition].getPlaced()) {
				wordCompleted = false;
				break;
			}

			//If this loop didn't break so far, it means that all the letters of this vertical words are placed correctly, so we can change the status of the next one to valid (unless it's the end of the word or the following is already placed)
			if ((i >= boardLetter.getIndexV()) && (i != boardLetter.getMaxV() - 1) && !matrix[yposition - boardLetter.getIndexV() + i + 1][xposition].getPlaced())
				this->matrix[yposition - boardLetter.getIndexV() + i + 1][xposition].setIsValid(true);
		}

		if (wordCompleted)	//If the word is completed, add 1 point
			points += 1;
	}

	return points;
}

//This function will change the recommended state the board letter in that position
void Board::recommendLetter(int& yposition, int& xposition, bool recommended) {
	this->matrix[yposition][xposition].setRecommended(recommended);
}