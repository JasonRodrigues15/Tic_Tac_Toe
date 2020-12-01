// a4_q1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Student Name : Jason Rodrigues, Brian Widjaja
// Syde 121 Assignment 4 question 1
// Filename: a4_q1 
//
// I hereby declare that this code, submitted for credit for the course SYDE121, is a product of my own efforts. This coded solution has not been plagiarized from other sources and has not been knowingly plagiarized by others.
//
//Project: Is a 4x4 tic-tac-toe game that allows two players to compete
//Due : 2020-11-06


#include <iostream>				//enables useful commands
#include <sstream>				//allows the conversion of integers into strings


using namespace std;			//allows us to not have to use std:: for every command

/*TEST CASES FOR WINNING:
Diagonal win:
X       O       O       X
5       X       O       8
9       10      X       12
13      O       15      X

>Outputs that Player X has won

Vertical win:
1       2       X       O
5       6       O       O
X       X       11      O
13      X       15      O

>Outputs that Player O has won

Horizontal win:
X       X       X       X
O       6       7       8
9       O       X       12
13      O       O       16

>Outputs that Player X has won

Tie game:
X       O       X       O
X       O       X       O
X       O       X       O
O       X       O       X

>Outputs that there is a tie

TEST CASES FOR MULTIPLE GAMES:
Game 1: if player X wins
player_X_score = 1, player_O_score = 0, total_ties = 0
player O starts game 2

Game 2: if player X wins
player_X_score = 2, player_O_score = 0, total_ties = 0
player X starts game 3

Game 3: if player O wins
player_X_score = 2, player_O_score = 1, total_ties = 0
player O starts game 4

Game 4: if player X wins
player_X_score = 3, player_O_score = 1, total_ties = 0
player X starts game 5

Game 5: if tie
player_X_score = 3, player_O_score = 1, total_ties = 1
player O starts game 6

Game 6: if tie
player_X_score = 3, player_O_score = 1, total_ties = 2
player X starts game 7

Game 7: if player X wins
player_X_score = 4, player_O_score = 1, total_ties = 2
player O starts game 8

Game 8: if player O wins
player_X_score = 4, player_O_score = 2, total_ties = 2
player X starts game 9

Game 9: if player O wins
player_X_score = 4, player_O_score = 3, total_ties = 2
player O starts game 10

Game 10: if player X wins
player_X_score = 5, player_O_score = 3, total_ties = 2

TEST CASES FOR USER INPUT:
1       2       3       X
5       6       7       8
9       10      11      12
13      14      15      16

If player O tries to place an O on 4
cout = Slot 4 is already filled.

If player O tries to place an O on 6:
1       2       3       X
5       O       7       8
9       10      11      12
13      14      15      16

If player X tries to place an X on 18
cout = That was an invalid input. Please input a value between 1 and 16

If player X tries to place an X on -245
cout = That was an invalid input. Please input a value between 1 and 16

AT END OF GAME:
if user types play, board will restart and game will start again
if user types exit, results appear
if user types something else, it will ask user to reinput
*/

//Input: takes in an integer num
//Processing: uses the sstream library to convert the integer num into a string
//Output: ouputs num_as_string which is a string conversion of the inputted num
string convert_to_string(int num) {
	stringstream ss;
	ss << num;
	string num_as_string;
	ss >> num_as_string;
	return num_as_string;
}


//Input: takes in my_array which is a string array that has a size of 4x4
//Processing: uses for loops to fill my_array with numbers from 1-16
//Output: no specific output although my_array will now be initialized
void create_board(string my_array[4][4]) {
	int counter = 0;
	string num_as_string;

	//a double for loop that iterates through the values of the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			counter += 1;
			num_as_string = convert_to_string(counter); //converts numbers from counter 1-16, into strings by calling the convert_to_string function

			my_array[i][j] = num_as_string; //assigns each string number from 1-16 an index in the array
			
		}
	}
}

//Input: takes in my_array which is a string array that has a size of 4x4
//Processing: prints the rows and columns of the 4x4 array as the game board
//Output: no specific output 
void print_board(string my_array[4][4]) {

	//a double for loop that iterates through the values of the array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << my_array[i][j] << "\t"; //Prints the board at this specific index with adequate spacing
		}
		cout << endl;
	}
	cout << endl;
}

//Input: takes in my_array which is a string array that has a size of 4x4
//Processing: uses for loops to iterate through my_array to check if the entire board is filled(which subsequently leads to a tie)
//Output: returns true if the board is  filled and returns false if the board is not filled
bool check_board_filled(string my_array[4][4]) {

	//a double for loop that iterates through the values of the array
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (my_array[i][j] != "X" && my_array[i][j] != "O") { //checks if there are any values on the board that are not filled
				return false; //will return false if all values of the board are not filled
			}
		}
	}
	return true;
}

//Input: takes in my_array which is a string array that has a size of 4x4, as well as the symbol of the current player(X or O), also a pass by reference integer for the rows and columns of the array
//Processing: asks the user to input a value for where they would like to mark, then has an error check to guarantee that the user inputs a value between 1-16 and then iterates to the array to find the value then make the index equal to that value of the user output and changes a boolean to check if the value has a symbol yet or not
//Output: returns a boolean that stores true if a slot is not filled and false if a slot is filled
bool player_turn(string my_array[4][4], string symbol, int& row, int& column)
{
	int choice;
	string s_choice;
	bool slot_filled = true;

	cout << "Where would you like to mark? ( Player " << symbol << " )"<< endl; 
	cin >> choice; //Gets the choice of where the user is putting their symbol

	while (choice > 16 || choice < 1) //Continuously asks the user to input a value if they have no inputted a valiid value between 1-16
	{
		cout << "That was an invalid input. Please input a value between 1 and 16\nWhere would you like to mark?" << endl;
		cin >> choice;
	}

	s_choice = convert_to_string(choice); //Converts the users choice to a string so that we are able to put it into the string array
	
	//a double for loop that iterates through the values of the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (s_choice == my_array[i][j]) //Iterates through until the value of the array is equal to the users choice
			{
				row = i;
				column = j;
				my_array[i][j] = symbol; //Makes the array at this index equal to the users symbol 
				slot_filled = false; // Makes slot_filled false so that the program knows that the slot is not filled already

			}
		}
	}
	if (slot_filled) // Checks slotfilled and if the value the user inputted was already used, then it will tell the user their choice is already filled
	{
		cout << "Slot " << choice << " is already filled." << endl;
	}

	return slot_filled;
}

//Input: takes in my_array which is a string array that has a size of 4x4, as well as the symbol of the current player(X or O), as well as an integer for the column value
//Processing: goes through the loop to check if the column that the user inputted is filled with the users symbol
//Output: returns a boolean that checks if one of the users has gotten a full column which will evaluate to true if the column is filled
bool check_vertical(string my_array[4][4], string symbol, int column) {
	bool c_vert = true;

	for (int i = 0; i < 4; i++) //Iterates through all the elements of the column of the array
	{
		if (my_array[i][column] != symbol) //Checks if the current index of the array is equal to the users value, it evaluate to false and the function outputs false if any of the values of the column are not equal to the users symbol
		{
			c_vert = false;
		}
	}

	return c_vert;
}

//Input: takes in my_array which is a string array that has a size of 4x4, as well as the symbol of the current player(X or O), as well as an integer for the row value
//Processing: goes through the loop to check if the row that the user inputted is filled with the users symbol
//Output: returns a boolean that checks if one of the users has gotten a full row which will evaluate to true if the row is filled
bool check_horizontal(string my_array[4][4], string symbol, int row) {
	bool c_hori = true;

	for (int i = 0; i < 4; i++) //Iterates through all the elements of the row of the array
	{
		if (my_array[row][i] != symbol)//Checks if the current index of the array is equal to the users value, it evaluate to false and the function outputs false if any of the values of the row are not equal to the users symbol
		{
			c_hori = false;
		}
	}

	return c_hori;

}

//Input: takes in my_array which is a string array that has a size of 4x4, as well as the symbol of the current player(X or O), as well as an integer for the row value and column
//Processing: goes through the loop to check if the diagonal that the user inputted is filled with the users symbol from top left to bottom right and from top right to bottom left
//Output: returns a boolean which checks OR for the booleans of whether from top left to bottom right is filled or if from top right to bottom left is filled
bool check_diagonal(string my_array[4][4], string symbol) {

	int row = 0, column = 3;
	bool tl_check = true, tr_check = true;

	for (int i = 0; i < 4; i++) 
	{
		if (my_array[row][row] != symbol) { //Will iterate through the loop of the array and check if the values from the top left to the bottom right are filled with the users symbol

			tl_check = false;
		}
		if (my_array[row][column] != symbol) //Will iterate through the loop of the array and check if the values from the top right to the bottom left are filled with the users symbol
		{
			tr_check = false;
		}
		//Changes the values of the rows and columns so that it iterates through all the values from top left to bottom right and from top right to bottom left
		row += 1; 
		column -= 1;
	}
	return tl_check || tr_check;
}

//Input: takes in my_array which is a string array that has a size of 4x4, as well as the symbol of the current player(X or O), as well as an integer for the row value and column
//Processing: creates a boolean that compares the value of the functions check_diagonal, check_horizontal, and check_vertical then it checks which of them are true to know whether the game is won or not
//Output: returns a boolean of game_is_won which gives true or false on whether the game has been won by either player
bool check_win(string my_array[4][4], string symbol, int row, int column) {

	bool game_is_won = check_diagonal(my_array, symbol) || check_horizontal(my_array, symbol, row) || check_vertical(my_array, symbol, column); //a bool to store the value of whether a player has gotten a line to win

	return game_is_won;
}

//Input: takes in player_X_score and player_O_score which stores the amount of wins each player has as well as total_ties to store the amount of ties, the function also inputs the symbol of the first player and the second player to account for who starts first
//Processing: has a while loop that checks if the game was won or tied to add a point to player X win player O win or ties and outputs depending on that statement, one of the statements runs player_turn for symbol_1 and the other runs its for symbol_2, refering to either X or O
//Output: returns a boolean of game_is_won which gives true or false on whether the game has been won by either player
void initialize_game(int& player_X_score, int& player_O_score, int& total_ties, string symbol_1, string symbol_2) {
	string my_array[4][4];
	bool game_won = false, player_invalid = false, game_tied = false;
	int row, column;

	create_board(my_array); //Calls create board and initializes the array

	print_board(my_array); //Prints the array that was just created using create_board

	while (!game_won && !game_tied) //Check if the game has not ended yet
	{
		do //calls player_turn so that the player completes a turn although does so using symbol_1 which is either X or O depending on how many games there is and loops until the players turn is not invalid
		{
			player_invalid = player_turn(my_array, symbol_1, row, column);

		} while (player_invalid);

		game_won = check_win(my_array, symbol_1, row, column); //Checks if the game is over

		if (game_won && symbol_1 == "X") //An output statement and counter for if player X has won
		{
			player_X_score += 1;
			cout << "Player X has won the game! They have " << player_X_score << " total wins!" << endl;
		}
		else if (game_won && symbol_1 == "O") //An output statement and counter for if player O has won
		{
			player_O_score += 1;
			cout << "Player O has won the game! They have " << player_O_score << " total wins!" << endl;
		}

		game_tied = check_board_filled(my_array); //Checks if the game has tied by checking if the board is full using check_board_filled

		cout << endl;
		print_board(my_array);

		if (!game_won && !game_tied) //Check if the game has not ended yet
		{
			do //calls player_turn so that the player completes a turn although does so using symbol_1 which is either X or O depending on how many games there is and loops until the players turn is not invalid
			{
				player_invalid = player_turn(my_array, symbol_2, row, column);

			} while (player_invalid);

			game_won = check_win(my_array, symbol_2, row, column); //Checks if the game is over

			if (game_won && symbol_2 == "X") //An output statement and counter for if player X has won
			{
				player_X_score += 1;
				cout << "Player X has won the game! They have " << player_X_score << " total wins!" << endl;
			}
			else if (game_won && symbol_2 == "O") //An output statement and counter for if player O has won
			{
				player_O_score += 1;
				cout << "Player O has won the game! They have " << player_O_score << " total wins!" << endl;
			}

			game_tied = check_board_filled(my_array); //Checks if the game has tied by checking if the board is full using check_board_filled

			cout << endl;
			print_board(my_array);
		}
		if (game_tied) //An output statement and counter for if the game has tied
		{
			total_ties += 1;
			cout << "The game results in a TIE!" << endl;
		}
	}
}
//Input: none
//Processing: Prompt the user to play the game or exit the game and will initialize the game if the user inputs play and if the user inputs exit then it will display the final scores and complete the code
//Output: none
void load_game() {

	bool continue_game = true;
	bool player_X_first = true;
	int player_X_score = 0, player_O_score = 0, total_ties = 0;
	string user_input;

	cout << "Welcome to 4x4 Tic-Tac-Toe!" << endl;

	while (continue_game) { // Will prompt the user to play or exit the game and will run the game if the user types play although will exit exit the game if the user input the exit
		cout << "Type 'play' to play, 'exit' to exit the game" << endl;
		cin >> user_input;

		if (user_input == "play" && player_X_first) { // will run if the user types play and runs the game in which X will go first
			initialize_game(player_X_score, player_O_score, total_ties, "X", "O");
			player_X_first = false;
		}
		else if (user_input == "play" && !player_X_first){ // will run if the user types play and runs the game in which O will go first
			initialize_game(player_X_score, player_O_score, total_ties, "O", "X");
			player_X_first = true;
		}
		else if (user_input == "exit") { // will exit the game if the user types exit and will ouput the score of number of player X wins, player O wins, and ties
			cout << "\nPlayer X has a total of " << player_X_score << " win(s)" << endl;
			cout << "Player O has a total of " << player_O_score << " win(s)" << endl;
			cout <<  total_ties << " game(s) resulted in a tie\n" << endl;
			cout << "Have a nice day! :D" << endl;
			continue_game = false;
		}
		else { //will ask the user to input a different value if they didn't enter play or exit
			cout << "Please input a valid answer!" << endl;
		}
	}
}

//Input: none
//Processing: will call load_game which runs the game
//Output: none
int main()
{
	load_game(); //runs the game
}
