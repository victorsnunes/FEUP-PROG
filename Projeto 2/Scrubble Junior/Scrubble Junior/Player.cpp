#include <iostream>
#include "Player.h"
using namespace std;

//Adds a new character to the player's hand
void Player::addNewCharacter(char l) {
	hand.push_back(l);
	this->handLength += 1;
}

//This function adds points to the scoring chips of the player. If no points are added, if returns false, otherwise it returns true.
bool Player::addScoringChips(int& points) {
	this->scoringChips += points;
	if (points == 0)
		return false;
	return true;
}

//Returns the scoring chips of the player
int Player::getScoringChips() {
	return this->scoringChips;
}

//Shows the hand of the player
void Player::showHand() {

	for (int i = 0; i < hand.size(); i++) {
		if (i != 0)
			std::cout << ", ";
		std::cout << hand[i];
	}
}

//Returns the vector of the player's hand
vector<char> Player::getHand() {
	return this->hand;
}

//Returns the the length of the player's hand
int Player::getHandLength() {
	return this->handLength;
}

//Removes a letter from the player's hand in a certain index
void Player::removeCharacter(int& index) {
	this->hand.erase(hand.begin()+index);
	this->handLength -= 1;
}

//Checks if a character is in the player's hand, and if it isn't, it keep asking until it gets a valid answer. Then it returns the index of that letter in the player's hand
int Player::checkCharacterInHand(char& characterChosen) {
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int handIndex;
	while (true) {

		bool t = false;

		//Turning his chosen character to uppercase
		if (islower(characterChosen))
			characterChosen = toupper(characterChosen);

		//Checking if the character chosen is in the hand of the player
		for (handIndex = 0; handIndex < this->handLength; handIndex++) {
			if (this->hand[handIndex] == characterChosen) {
				t = true;
				break;
			}
		}

		//If he did a valid choice of the character, we break this loop and continue the play
		if (t)
			break;

		//If not, we'll repeat this loop
		SetConsoleTextAttribute(hConsole, RED);
		cout << "\nInvalid letter, try again (press ENTER):\n\n";
		SetConsoleTextAttribute(hConsole, BLACK);
		cin.clear();
		cin.ignore(10000, '\n');

		//Showing the player's hand
		cout << "\n\nThese are the letters you have : \n";
		this->showHand();

		cout << "\nWhich letter do you want to choose?\n";
		cin >> characterChosen;
	}

	return handIndex;

}