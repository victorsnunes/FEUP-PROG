#include <iostream>
#include "Board.h"
#include <fstream>
using namespace std;

int main()
{
	cout << "Welcome to the Board Builder for the game Scrabble Junior\n\n";

	//Asks the user to give a name for the file name
	string filename;
	cout << "Let's begin by writing the name of the text file that we're going to create (remember to write .txt at the end):\n";
	cin >> filename;
	cin.clear();
	cin.ignore(10000, '\n');

	//This loop is to check if the chosen file name is valid
	while (true) {
		
		//Checking if the file name has at least 5 characters ()
		if (filename.length() < 5) {
			cout << "\nInvalid name, remember to write .txt at the end, try again:\n";
			cin >> filename;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		//This string is going to store the last 4 characters of the file name"
		string final = filename.substr(filename.length() - 4, 4);
		
		//Checking if these last characteres are ".txt"
		if (final == ".txt")
			break;

		cout << "\nInvalid name, remember to write .txt at the end, try again:\n";
		cin >> filename;
		cin.clear();
		cin.ignore(10000, '\n');
	}

	//Creating the file
	ofstream boardFile(filename);

	cout << "\nNow let's define the board's size\n";
	int width, height;

	//Letting the user choose the height of the board and checking if it is valid
	while (true) {
		cout << "Please, write the height (y axis) of the board: (It should be a number from 1 to 20)\n";
		cin >> height;
		if (height >= 1 && height <= 20)	//If the answer is valid, we break the loop and continue, otherwise we'll still be in the loop
			break;
		cout << "\nInvalid answer!\n\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	cout << endl;

	//Letting the user choose the width of the board and checking if it is valid
	while (true) {
		cout << "Please, write the width (x axis) of the board: (It should be a number from 1 to 20)\n";
		cin >> width;
		if (width >= 1 && width <= 20)		//If the answer is valid, we break the loop and continue, otherwise we'll still be in the loop
			break;
		cout << "\nInvalid answer!\n\n";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	//Writing the board's dimensions on the file
	boardFile << width << " x " << height;

	//Creating the board
	Board board(width, height);

	//Now, this is the loop to keep adding new words to the board
	while (true) {

		cout << "\nHere's your board right now:\n";
		board.show();

		//This loop is to ask the user if he still wants to add new words to the board
		char answer;
		while (true) {
			cout << "\nWould you like to add a new word? (Y or N)\n";
			cin >> answer;
			if (islower(answer))
				answer = toupper(answer);		//Turning the answer into uppercase
			if (answer == 'Y'|| answer == 'N')
				break;							//If the answer is valid, we break the loop and continue
			cout << "\nInvalid answer\n\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		//End the loop and prepare to save the file
		if (answer == 'N')
			break;

		//Continue to add a new word
		cout << "\nWrite the word you want to add:\n";
		string newWord;
		cin >> newWord;
		cout << endl;

		//Putting the word in lowercase 
		for (int i = 0; i < newWord.length(); i++)
			newWord[i] = tolower(newWord[i]);

		//Checking if the word is in the dictionary
		if (!board.checkValidNewWord(newWord)) {
			cout << "\n\nInvalid word!\n\n";
			continue;
		}

		//Putting the word in uppercase 
		for (int i = 0; i < newWord.length(); i++)
			newWord[i] = toupper(newWord[i]);

		//Letting the user write the orientation of the word and checking if it's valid
		char orientation;
		while (true) {
			cout << "Now, write the orientation (V for vertical or H for horizontal):\n";
			cin >> orientation;
			if (islower(orientation))
				orientation = toupper(orientation);			//Turning the orientation into uppercase
			if (orientation == 'V' || orientation == 'H')
				break;										//If the orientation is valid, we break the loop and continue
			cout << "\nInvalid orientation!\n\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		//Letting the user write the Y position of the word and checking if it's valid
		char yposition;
		while (true) {
			cout << "\nWrite the letter corresponding to the y axis of the first letter of the word:\n";
			cin >> yposition;
			if (islower(yposition))
				yposition = toupper(yposition);		//Turning the Yposition into uppercase
			if (int(yposition) >= 65 && int(yposition) <= (board.getHeight() + 64))		//Checking if the Yposition chosen is in the range of the board's height (in other words, checking if it is in the range from 'A' (ASCII code = 65) to the last letter of the y axis (ASCII code = board.getHeight() + 64)
				break;
			cout << "\nInvalid position!\n\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		//Letting the user write the X position of the word and checking if it's valid
		char xposition;
		while (true) {
			cout << "\nWrite the letter corresponding to the x axis of the first letter of the word:\n";
			cin >> xposition;
			if (isupper(xposition))
				xposition = tolower(xposition);		//Turning the Xposition into lowercase
			if (int(xposition) >= 97 && int(xposition) <= (board.getWidth() + 96))		//Checking if the Xposition chosen is in the range of the board's width (in other words, checking if it is in the range from 'a' (ASCII code = 97) to the last letter of the x axis (ASCII code = board.getWidth() + 96)
				break;
			cout << "\nInvalid position!\n\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		//Check if the can be added, and do it if it can
		if (!board.addNewWord(newWord, orientation, xposition, yposition)) {
			cout << "\n\nInvalid operation, you can't add this word in this place\n\n";
			continue;	//This will repeat the loop to ask if you want to add a new letter
		}

		cout << "\nThe word was added successfully\n\n";

		//Writing this new word on the file
		boardFile << "\n" << yposition << xposition << " " << orientation << " " << newWord;

	}

	cout << "\n\nSaving your board into an text file...\n\n";

	//Closing the file
	boardFile.close();

	cout << "\nOperation succeeded, text file created. Now you can play Scrubble Junior by using that file. Enjoy! :)\n\n";
	return 0;
}