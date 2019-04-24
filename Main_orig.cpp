#include <iostream> //for cout, endl
#include <windows.h> //for sys clr
#include <vector> //for 2d vector
#include "read2DMaze.h" //load maze from file
#include "GameLevel.h" //generate/save maze to file

using namespace std;

bool gameOver = false;
int Gamespeed = 24;
int level = 1;
int width = 22, height = 10;
int playerX = 1, playerY = height - 2;
int playerX_Move, playerY_Move;
enum direction { NONE, LEFT, RIGHT, UP, DOWN };
direction dir;

vec2d Map(SIZE +1, vector<char>(0));
int columns = 0, rows = 0;

void Setup()
{
	cout << "\n\n\n\n\n\n\n\n\nWelcome to\n";
	Sleep(500);
	cout << "\n\nText Dungeon\n\n";
	Sleep(1500);
	cout << "\n\n<insert menu/instructions here or something>...\n\n";
	Sleep(1500);

	readMaze(Map, rows, columns);
	cout << "\n\nloaded maze successfully\n";
	Sleep(1500);



}

void Draw()
{
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

	Map[playerY][playerX] = '@'; //display character


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
							level = 2;
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
							level = 2;
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
							level = 2;
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
							level = 2;
							break;
						}
					}
				}

				break;
			}

			}

	//output GUI
	cout << "\nUse arrow keys to move." << endl;
	cout << "@: Player" << endl;
	cout << "=: Door" << endl;



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


}

void CheckLevel()
{
	if (level == 1)
	{
		GameLevel *oLevel1 = new GameLevel();
		oLevel1->Update();
		playerX = oLevel1->getStartX();
		playerY = oLevel1->getStartY();
	}

	if (level == 2)
	{
		cout << "new level" << endl;
		Sleep(1500);
		GameLevel *oLevel2 = new GameLevel();
		oLevel2->Update();
		readMaze(Map, rows, columns);
		playerX = oLevel2->getStartX();
		playerY = oLevel2->getStartY();
	}
}

int main()
{
	Setup();

	GameLevel *oLevel1 = new GameLevel();
	oLevel1->Update();
	playerX = oLevel1->getStartX();
	playerY = oLevel1->getStartY();

	while (level == 1)
	{
		system("cls");
		Draw();
		Input();
		Sleep(Gamespeed);
	}


	cout << "new level" << endl;

	Sleep(1500);
	GameLevel *oLevel2 = new GameLevel();
	oLevel2->Update();
	readMaze(Map, rows, columns);
	playerX = oLevel2->getStartX();
	playerY = oLevel2->getStartY();

	while (level == 2)
	{
		system("cls");
		Draw();
		Input();
		Sleep(Gamespeed);
	}

	return 0;
}
