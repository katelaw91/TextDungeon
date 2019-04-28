#include <iostream> //for cout, endl
#include <windows.h> //for sys clr
#include <vector> //for 2d vector
#include "read2DMaze.h" //load maze from file
#include "GameLevel.h" //generate/save maze to file
#include <time.h>
#include <chrono>

using namespace std;

bool gameOver = false;
int Gamespeed = 100;
double countDown = 30;
int Score = 0;
int level = 1;
int menu = 0;
int width = 22, height = 10;
int playerX = 1, playerY = 1;
int playerX_Move, playerY_Move;
enum direction { NONE, LEFT, RIGHT, UP, DOWN };
direction dir;
char input;


vector<int>::iterator it;
vec2d Map(SIZE + 1, vector<char>(0));
int columns = 0, rows = 0;



void Setup()
{
	cout << "\n\n\n\n\n\n\n\n\nWelcome to\n";
	Sleep(500);
	cout << "\n\nText Dungeon\n\n";
	Sleep(1500);
	cout << "\n\nN) New Game\n\n";
	cout << "\nS) View High Scores\n\n";

	while (menu != 1) {

		cin >> input;

		if ((input == 'n') || (input == 'N')) {
			readMaze(Map, rows, columns);
			cout << "\n\nloading maze...\n";
			Sleep(1500);
			menu = 1;
		}
		else {

			cout << "Highscores go here..." << endl;

		}
	}


}

void NewLevel()
{
	level++;
	Score+=100;
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\nLevel " << level << endl;
	cout << "\n\nScore: " << Score;
	cout << "\n +30 seconds\n";
	countDown += 3;
	Sleep(3000);
	GameLevel *oNewLevel = new GameLevel();
	oNewLevel->Update();
	vec2d NewMap(SIZE + 1, vector<char>(0));
	readMaze(NewMap, rows, columns);
	playerX = 1;
	playerY = 1;
	NewMap.swap(Map);
	countDown += 30;

	
}

void Draw(int &playerX, int &playerY)
{
	ofstream file;
	file.open("error.txt");
	file << "entering draw" << endl;
	//for (int i = 0; i < height; i++) { cout << Map[i] << endl; } //display map

	 //display map
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++)
		{
			cout << Map[i][j];
		}
		cout << endl;
	}
	file << "setting the char" << endl;
	Map[playerY][playerX] = '@'; //display character
	file << "set the char" << endl;
	file.close();



	//output GUI
	cout << "Use arrow keys to move." << endl;
	cout << "@: Player" << endl;
	cout << "=: Door" << endl;
	cout << "Press [esc] to quit." << endl;
	//search map grid for player, then move based on dir input
	//if there is an empty space, move character to the new position
	//and replace old character position with  blank space
	for(int y = 0; y < height; y++)
		for(int x = 0; x < height; x++)
			switch (Map[playerY][playerX])
			{
			case '@':
			{
				if (dir == UP) 
				{
					playerY_Move = playerY - 1;
					switch (Map[playerY_Move][playerX])
					{
						case ' ': 
						{
							Map[playerY][playerX] = ' ';
							playerY -= 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							break;
						}

						case '=': 
						{
							Map[playerY][playerX] = ' ';
							playerY -= 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							NewLevel();
							break;
						}
						case '+':
						{
							Map[playerY][playerX] = ' ';
							playerY -= 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							Score += 25;
							break;
						}
					}
				}

				if (dir == DOWN)
				{
					playerY_Move = playerY + 1;
					switch (Map[playerY_Move][playerX])
					{
						case ' ':
						{
							Map[playerY][playerX] = ' ';
							playerY += 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							break;
						}
						case '=':
						{
							Map[playerY][playerX] = ' ';
							playerY += 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							NewLevel();
							break;
						}
						case '+':
						{
							Map[playerY][playerX] = ' ';
							playerY += 1;
							Map[playerY_Move][playerX] = '@';
							dir = NONE;
							Score += 25;
							break;
						}
					}

				}

				if (dir == RIGHT)
				{
					playerX_Move = playerX + 1;
					switch (Map[playerY][playerX_Move])
					{
						case ' ':
						{
							Map[playerY][playerX] = ' ';
							playerX += 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							break;
						}
						case '=':
						{
							Map[playerY][playerX] = ' ';
							playerX += 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							NewLevel();
							break;
						}
						case '+':
						{
							Map[playerY][playerX] = ' ';
							playerX += 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							Score += 25;
							break;
						}
					}
				}

				if (dir == LEFT)
				{
					playerX_Move = playerX - 1;
					switch (Map[playerY][playerX_Move])
					{
						case ' ':
						{
							Map[playerY][playerX] = ' ';
							playerX -= 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							break;
						}
						case '=':
						{
							Map[playerY][playerX] = ' ';
							playerX -= 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							NewLevel();
							break;
						}
						case '+':
						{
							Map[playerY][playerX] = ' ';
							playerX -= 1;
							Map[playerY][playerX_Move] = '@';
							dir = NONE;
							Score += 25;
							break;
						}
					}
				}

				break;
			}

			}





}

void Input()
{
	if (GetAsyncKeyState(VK_UP) != 0)
		dir = UP;
	if (GetAsyncKeyState(VK_DOWN) != 0)
		dir = DOWN;
	if (GetAsyncKeyState(VK_RIGHT) != 0)
		dir = RIGHT;
	if (GetAsyncKeyState(VK_LEFT) != 0)
		dir = LEFT;
	if (GetAsyncKeyState(VK_ESCAPE) != 0)
	{ 
		system("cls");
		gameOver = true;
	}


}


int main()
{
	time_t start, end;
	double elapsedTime;

	GameLevel *oLevel = new GameLevel();
	oLevel->Update();
	//playerX = oLevel->getStartX();
	//playerY = oLevel->getStartY();

	Setup();
	time(&start); //start the timer

	while (!gameOver)
	{
		do {
			time(&end);
			elapsedTime = difftime(end, start);
			Draw(playerX, playerY);
			Input();
			printf("Score: [ %d ]   Timer: [  %4.2f  ]\n", Score, countDown - elapsedTime);
			Sleep(Gamespeed);
			system("cls");
		} while (elapsedTime != countDown); //run for countDown seconds
		gameOver = true;
		//system("cls");

	}

	cout << "Game Over\n";
	Sleep(4000);

	return 0;
}
