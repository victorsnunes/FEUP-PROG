#include "Letter.h"
#include <iostream>
using namespace std;

//That's the constructor for the empty spaces
Letter::Letter(char character) {
	this->character = character;
	this->placed = true;
}

Letter::Letter(char character, char orientation, int index, int max){
	this->character = character;

	//Storing the index of the letter in the word and the total of letters in the word
	//In the case of  a horizontal
	if (orientation == 'H') {
		this->indexH = index;
		this->maxH = max;
		if (index == 0)
			this->isValid = true;
	}
	//In the case of  a vertical
	else {
		this->indexV = index;
		this->maxV = max;
		if (index == 0)
			this->isValid = true;
	}

	//Stores the orientation
	this->orientation = orientation;

}

//Returns the character of the letter
char Letter::getCharacter() const {
	return this->character;
}

//Returns the orientation of the letter
char Letter::getOrientation() const {
	return this->orientation;
}

//Returns the isValid of the letter
bool Letter::getIsValid() const {
	return this->isValid;
}

//Returns the placed of the letter
bool Letter::getPlaced() const {
	return this->placed;
}

//Returns the indexH of the letter
int Letter::getIndexH() const {
	return this->indexH;
}

//Returns the indexV of the letter
int Letter::getIndexV() const {
	return this->indexV;
}

//Returns the getMaxH of the letter
int Letter::getMaxH() const {
	return this->maxH;
}

//Returns the getMaxV of the letter
int Letter::getMaxV() const {
	return this->maxV;
}

//Returns the recommended of the letter
bool Letter::getRecommended() const {
	return this->recommended;
}

//Change the orientation to 'B'
void Letter::changeOrientation() {
	this->orientation = 'B';
}

//Change the value of isValid
void Letter::setIsValid(bool v) {
	this->isValid = v;
}

//Change the value of indexH
void Letter::setIndexH(int index) {
	this->indexH = index;
}

//Change the value of indexV
void Letter::setIndexV(int index) {
	this->indexV = index;
}

//Change the value of setMaxH
void Letter::setMaxH(int max) {
	this->maxH = max;
}

//Change the value of setMaxV
void Letter::setMaxV(int max) {
	this->maxV = max;
}

// Change the value of recommended
void Letter::setRecommended(bool recommended) {
	this->recommended = recommended;
}

//Change placed to true
void Letter::changePlaced() {
	this->placed = true;
	this->isValid = false;
}