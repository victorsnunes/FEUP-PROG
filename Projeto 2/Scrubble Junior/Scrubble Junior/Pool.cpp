#include "Pool.h"
#include <iostream>
using namespace std;

//Returns the length of the pool
int Pool::getLenght() {
	return this->lenght;
}

//Adds a new character to the pool
void Pool::addNewCharacter(char newLetter) {
	(this->remainingCharacters).push_back(newLetter);
	this->lenght += 1;
}

//Suffles the pool
void Pool::sufflePool() {
	for (int i = 0; i < lenght; i++) {
		int randomIndex = rand() % lenght;
		char temp = remainingCharacters[randomIndex];
		remainingCharacters[randomIndex] = remainingCharacters[i];
		remainingCharacters[i] = temp;
	}
}

//It removes the first letter of the pool and returns it
char Pool::popOutWord() {
	char l = remainingCharacters[0];
	remainingCharacters.erase(remainingCharacters.begin());
	this->lenght -= 1;
	return l;
}