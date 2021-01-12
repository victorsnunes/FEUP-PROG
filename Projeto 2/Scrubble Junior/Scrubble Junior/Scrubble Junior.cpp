#include <iostream>
#include <string>
#include <fstream>
#include "Board.h"
#include "Player.h"
#include "Pool.h"
#define YELLOW 6
#define BLUE 3
#define PURPLE 13
#define PINK 12
#define RED 4
#define GREEN 10
#define BLACK 7
using namespace std;

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "Welcome to the game Scrubble Junior!\n\n\n";

	//Storing the name of the file given by the user
	string filename;
	cout << "First, write the name of the file with the informations of the board (remember to write '.txt' at the end):\n";
	cin >> filename;

	//Inicializing the board by the constructor that receives an ifstream
	Board board(filename);

	cout << "\nGreat, here's your board\n";
	board.show();

	Pool pool;

	//This loop will pass to each letter of the board, and, if it's not an empty space, it'll be added to the pool
	for (int i = 0; i < board.getWidth(); i++) {
		for (int j = 0; j < board.getHeight(); j++) {
			if (board.getLetter(j, i).getCharacter() != ' ')
				pool.addNewCharacter(board.getLetter(j, i).getCharacter());
		}
	}

	//Suffle the words in the pool
	pool.sufflePool();

	//Asking how many players are going to play
	int numPlayers;
	while (1) {
		cout << "\nHow many players are going to play the game? (it should be from 2 to 4)\n";
		cin >> numPlayers;
		//Checking if the answer is valid
		if (numPlayers >= 2 && numPlayers <= 4)
			break;
		SetConsoleTextAttribute(hConsole, RED);
		cout << "\nInvalid answer, try again:\n";
		SetConsoleTextAttribute(hConsole, BLACK);
		cin.clear();
		cin.ignore(10000, '\n');
	}

	//Creating a vector with the players
	vector<Player> players;
	for (int i = 0; i < numPlayers; i++) {
		Player p;
		players.push_back(p);
	}

	int count = 0;
	int player = 0;
	//This loop will try to give each player a total of 7 characters, giving 1 at a time to each one. The objective is to try to distribute it as evenly as possible, if the pool doesn't have enough characters
	while (pool.getLenght() != 0 && count != numPlayers * 7) {
		players[player].addNewCharacter(pool.popOutWord());
		player = (player + 1) % numPlayers;
		count += 1;
	}

	//Showing the characters of each player
	cout << "\n\n\nHere are the letters of each player:\n\n";
	for (int i = 0; i < numPlayers; i++) {
		cout << "Player " << i + 1 << ": ";
		players[i].showHand();
		cout << endl;
	}

	player = 0;
	bool endGame = false;
	//This is the loop that will run until the game is over
	while (!endGame) {

		//This loop is for the 2 plays that the current player can make
		for (int o = 0; o < 2; o++) {

			//Checking if the player can make any valid move
			bool canPlay = false;

			endGame = true;

			//Passing through each letter in the board
			for (int i = 0; i < board.getWidth(); i++) {
				for (int j = 0; j < board.getHeight(); j++) {

					//At first, consider the actual board letter a non possible choice for the actual player. We want to erase any recommendations of the previous player
					board.recommendLetter(j, i, false);

					//If there is at least one letter that was not placed on the board, we won't end the game
					if (!board.getLetter(j, i).getPlaced())
						endGame = false;

					//Passing through each one of the player's characters
					for (int p = 0; p < players[player].getHandLength(); p++) {

						//If the player has an character that can be played in a certain position of the board and this position is valid, therefore the player can make a valid move
						if (board.getLetter(j, i).getCharacter() == players[player].getHand()[p] && board.getLetter(j, i).getIsValid()) {
							canPlay = true;
							board.recommendLetter(j, i, true);	//Now we can say that this actual board letter is a possible choice for this actual player
						}

					}
				}
			}

			//Ending the game, if all the letters are placed in the board
			if (endGame)
				break;

			//This is the case of the first letter to choose
			if (o == 0) {

				//Choosing diferent colors to the players
				if (player == 0)
					SetConsoleTextAttribute(hConsole, YELLOW);
				if (player == 1)
					SetConsoleTextAttribute(hConsole, BLUE);
				if (player == 2)
					SetConsoleTextAttribute(hConsole, PURPLE);
				if (player == 3)
					SetConsoleTextAttribute(hConsole, PINK);

				cout << "\n\nIt's the turn of the player " << player + 1 << endl << endl;
				SetConsoleTextAttribute(hConsole, BLACK);

			}
			//This is the case of the second letter to choose
			else 
				cout << "\n\nNow choose your second letter\n\n";

			board.show(); //Showin the board

			//Showing the player's hand
			cout << "\n\nThese are the letters you have : \n";
			players[player].showHand();

			//If the previous loop was completed without finding any valid plays to do, the player will have to exchange 2 letter  with the pool. But if the pool is empty, he'll have to pass
			if (!canPlay) {

				SetConsoleTextAttribute(hConsole, RED);
				cout << "\n\nYou can't make any valid moves.\n";
				//This is the case where the pool is empty and the player can't exchange
				if (pool.getLenght() == 0) {
					cout << "And unfortunately the pool is empty. Press ENTER to pass.\n";
					cin.get();
					cin.clear();
					cin.ignore(10000, '\n');
					break;
				}
				SetConsoleTextAttribute(hConsole, BLACK);


				int temp = 0;
				do {

					//This is the case where the pool has only 1 letter, and the player will only exchange 1 letter
					if (pool.getLenght() == 1)
						cout << "There's only 1 letter remaining in the pool.\nYou should exchange 1 letter with the pool\n\n";

					//This is the case where the pool has more than 2 letters, and the player will exchange 2 letter
					else {
						if (temp == 0) {
							cout << "You should exchange 2 letters with the pool\n\n";
							cout << "\nFirst letter:\n\n";
						}
						else
							cout << "\nSecond letter:\n\n";
					}

					//Showing the characters in the player's hand
					cout << "Here are the letters in your hand:\n";
					players[player].showHand();

					//Asking the user to choose the character
					char exchange;
					cout << "\n\nChoose the letter you want to exchange:\n";
					cin >> exchange;
					cin.clear();
					cin.ignore(10000, '\n');

					//Get the hand index of this character (or ask the user again if it isn't valid)
					int handIndex = players[player].checkCharacterInHand(exchange);
					
					pool.addNewCharacter(players[player].getHand()[handIndex]);		//Adds the chosen char to the pool
					players[player].removeCharacter(handIndex);						//Removes the char from the player's hand
					players[player].addNewCharacter(pool.popOutWord());				//Removes the char from the pool and adds it to the player's hand

					temp += 1;

				} while (pool.getLenght() >= 2 && temp != 2);

				//Showing one more time the letters in the player's hand
				cout << "Here are the letters in your hand:\n";
				players[player].showHand();

				break;
			}

			//This is the loop where the player is going to make his play. He's obliged to play, because we know he has possible plays to do
			while (true) {

				//Asking which letter the player will choose
				char characterChosen;
				cout << "\nWhich letter do you want to choose?\n";
				cin >> characterChosen;

				//Get the hand index of this character (or ask the user again if it isn't valid)
				int handIndex = players[player].checkCharacterInHand(characterChosen);

				characterChosen = players[player].getHand()[handIndex];
				
				char yposition;

				//This loop will ask the player for a Y coordiante, and will keep asking if the answer is valid
				while (true) {
					cout << "\nNow select the Y position:\n";
					cin >> yposition;
					//Turning the answer to uppercase
					if (islower(yposition))
						yposition = toupper(yposition);

					//The answer should be in the range of the board
					if (int(yposition) >= 65 && int(yposition) <= (board.getHeight() + 64))
						break;

					SetConsoleTextAttribute(hConsole, RED);
					cout << "\nInvalid position, try again:\n\n";
					SetConsoleTextAttribute(hConsole, BLACK);
				}

				char xposition;

				//This loop will ask the player for a Y coordiante, and will keep asking if the answer is valid
				while (true) {
					cout << "\nNow select the X position:\n";
					cin >> xposition;
					//Turning the answer to lowercase
					if (isupper(xposition))
						xposition = tolower(xposition);

					//The answer should be in the range of the board
					if (int(xposition) >= 97 && int(xposition) <= (board.getWidth() + 96))
						break;

					SetConsoleTextAttribute(hConsole, RED);
					cout << "\nInvalid position, try again:\n\n";
					SetConsoleTextAttribute(hConsole, BLACK);
				}

				//This if statement will run the function "board.play" which will try to make the play that the player has chosen. If the play isn't valid, the function will return false, and this if statement will be read, asking for the player to write a valid move
				if (!board.play(characterChosen, yposition, xposition)) {

					SetConsoleTextAttribute(hConsole, RED);
					cout << "\nInvalid move, try again!\n\n";
					SetConsoleTextAttribute(hConsole, BLACK);
					cin.clear();
					cin.ignore(10000, '\n');
					board.show();

					//Showing the player's hand
					cout << "\n\nThese are the letters you have : \n";
					players[player].showHand();
					continue;
				}
				//If the previous if statement was not read, that means that the play was valid and it was done.

				//Remove that character from the player's hand
				players[player].removeCharacter(handIndex);

				//Tries to pick up a new character from the pool
				if (pool.getLenght() != 0) {
					char l = pool.popOutWord();
					players[player].addNewCharacter(l);
				}

				//Checks if this letter chosen has completed a word (or words), and stores the points in the variable "points" (it can be 0)
				int points = board.checkCompletedWord(yposition, xposition);
				
				//Adds that quantity of points to the score of the player. And if the points != 0, it will run this if statement with a message show how many points he won and his score
				if (players[player].addScoringChips(points)) {

					SetConsoleTextAttribute(hConsole, GREEN);
					cout << "\n\nFantastic, looks like player " << player + 1 << " got " << points << " scoringChip";
					if (points == 2)
						cout << "s";
					cout << "!\n\n";
					SetConsoleTextAttribute(hConsole, BLACK);
					cout << "Player " << player + 1 << ", now your score is: " << players[player].getScoringChips() << endl;
				}

				break;
			}
		}

		//Go to the next player
		player = (player + 1) % numPlayers;
	}

	cout << "\n\n";
	board.show();

	SetConsoleTextAttribute(hConsole, GREEN);
	cout << "\n\n\n\nThe game is over!\n\n";
	SetConsoleTextAttribute(hConsole, BLACK);


	//This loop is to determine the maximum score
	int maxScore = 0;
	for (int p = 0; p < numPlayers; p++)
		if (players[p].getScoringChips() > maxScore)
			maxScore = players[p].getScoringChips();

	//And this loop is to determine how many players got the maximum score
	vector<int> winners;
	for (int p = 0; p < numPlayers; p++)
		if (players[p].getScoringChips() == maxScore)
			winners.push_back(p+1);

	//Final message to announce the winner
	//If there's only 1 winner
	if (winners.size() == 1)
		cout << "\n\nThe winner is player " << winners[0] << "!";
	//If there's more than 1 winner
	else {

		cout << "\n\nIt's a draw between the players ";
		for (int i = 0; i < winners.size(); i++) {
			if (i == winners.size() - 1)
				cout << " and ";
			else if (i != 0)
				cout << ", ";

			cout << winners[i];
		}
	}

	cout << "\n\nThanks for playing :)\n\n\n";

	return 0;
}