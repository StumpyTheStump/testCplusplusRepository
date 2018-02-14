#include <iostream>
#include <random>
#include <time.h>
using namespace std;

const char* INDENT = "\t";
const char* EMPTY_TILE = "[ \xb0 ]";
const char* ENEMY_TILE = "[ \x94 ]";
const char* TREASURE_TILE = "[ $ ]";
const char* FOOD_TILE = "[ \xcf ]";
const char* ENTRANCE_TILE = "[ \x9d ]";
const char* EXIT_TILE = "[ \xFE ]";
const char* PLAYER_TILE = "[ X ]";

// Variables
const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;

// Maze Dimentions
const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

void main()
{
	// Set cmd Text and Background Colour
	system("Color 0a");



	// Create a 2D Array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	srand(time(nullptr));

	// Fill the Arrays With Random Room Types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
			{
				rooms[y][x] = type;
			}
			else
			{
				rooms[y][x] = EMPTY;
			}
		}
	}
	// Set the Entrance and Exit the Maze
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;

	// Game Loop
	while (!gameOver)
	{
		system("cls");
		// Introduction
		cout << INDENT << INDENT << "Welcome to ZORP!" << endl;
		cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << endl;
		cout << INDENT << "It is definitely not related to any other text-based adventure game." << endl << endl;

		// Output the Map
		cout << endl;
		cout << endl;
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			cout << INDENT;
			for (int x = 0; x < MAZE_WIDTH; x++)
			{
				if (playerX == x && playerY == y)
				{
					// Draw player's position on the map
					cout << PLAYER_TILE;
					continue;
				}

				// Draw room positions
				switch (rooms[y][x])
				{
				case EMPTY:
					cout << EMPTY_TILE;
					break;
				case ENEMY:
					cout << ENEMY_TILE;
					break;
				case TREASURE:
					cout << TREASURE_TILE;
					break;
				case FOOD:
					cout << FOOD_TILE;
					break;
				case ENTRANCE:
					cout << ENTRANCE_TILE;
					break;
				case EXIT:
					cout << EXIT_TILE;
					break;
				}
			}
			cout << endl;
		}
		cout << endl;

		// Descriptions of Rooms
		switch (rooms[playerY][playerX])
		{
		case EMPTY:
			cout << INDENT << "You are in an empty meadow. There is nothing of note here." << endl;
			break;
		case ENEMY:
			cout << INDENT << "BEWARE. An enemy is approaching." << endl;
			break;
		case TREASURE:
			cout << INDENT << "Your journey has been rewarded. You have found some treasure." << endl;
			break;
		case FOOD:
			cout << INDENT << "At last! You collect some food to sustain you on your journey." << endl;
			break;
		case ENTRANCE:
			cout << INDENT << "The entrance you used to enter this maze is blocked." << endl << INDENT << "There is no going back." << endl;
			break;
		case EXIT:
			cout << INDENT << "Despite all the odds, you made it to the exit. Congratulations." << endl;
			gameOver = true;
			continue;
		}


		// Directions the Player Can Take
		cout << INDENT << "You can see paths leading to the " <<
			((playerX > 0) ? "west, " : "") <<
			((playerX < MAZE_WIDTH - 1) ? "east, " : "") <<
			((playerY > 0) ? "north, " : "") <<
			((playerY < MAZE_HEIGHT - 1) ? "south, " : "") << endl;

		cout << INDENT << "Where to now?" << INDENT;

		// Clear the Input Buffer, Ready for Player Input
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		int direction = 0;
		cin >> direction;

		// If Any Error Occured While Reading the Input, Go Back to the Top of the Game Loop and Ask Again
		if (cin.fail())
		{
			continue;
		}

		switch (direction)
		{
		case EAST:
			if (playerX < MAZE_WIDTH - 1)
				playerX++;
			break;
		case WEST:
			if (playerX > 0)
				playerX--;
			break;
		case NORTH:
			if (playerY > 0)
				playerY--;
			break;
		case SOUTH:
			if (playerY < MAZE_HEIGHT - 1)
				playerY++;
		default:
			// Do Nothing, Go Back to the Top of the Loop and Ask Again
			break;
		}
	}

	cout << endl << INDENT << "Press 'Enter' to exit the program." << endl;
	cin.get();
	return;
}


