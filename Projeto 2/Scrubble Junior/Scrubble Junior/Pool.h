#pragma once
#include <vector>

class Pool {
public:
	int getLenght();									//Returns the length of the pool
	void addNewCharacter(char newCharacter);			//Adds a new character to the pool
	void sufflePool();									//Suffles the pool
	char popOutWord();									//It removes the first letter of the pool and returns it

private:
	std::vector<char> remainingCharacters;				//The vector of the characters of the pool
	int lenght = 0;										//The pool's length
};