#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include "Level.h"

using namespace std;
using vec = vector<vector<char> >; //alias for 2D vector for easier re-typing

bool gameOver = false;
int Gamespeed = 100;
int level = 1;
Level olvl1(5, 5);
enum direction { NONE, LEFT, RIGHT, UP, DOWN };
direction dir;

void Setup()
{
	cout << "\n\n\n\n\n\n\n\n\nWelcome to\n";
	Sleep(500);
	cout << "\n\nText Dungeon\n\n";
	Sleep(1500);
	cout << "\n\n<insert menu/instructions here or something>...\n\n";
	Sleep(2000);

}

void Draw()
{
	int height = olvl1.getHeight();
	int width = olvl1.getWidth();
	int playerX = 1, playerY = height - 2;
	int playerX_Move, playerY_Move;
	vec Map;

	system("cls"); //clear the screen
	Map = olvl1.getLevel(); //fill map grid
	olvl1.displayRoom(); //display map
	Map[playerY][playerX] = '@'; //display character



	//search map grid for player, then move based on dir input
	//if there is an empty space, swap with player char
	for (int y = 0; y < height; y++)
		for (int x = 0; x < height; x++)
			switch (Map[y][x])
			{
			case '@': //search for char
			{
				if (dir == UP)
				{
					playerY_Move = playerY - 1;
					switch (Map[playerY_Move][playerX])
					{
					case ' ': //blank space
					{
						Map[playerY][playerX] = ' ';
						playerY -= 1;
						Map[playerY_Move][playerX] = '@';
						dir = NONE;
						break;
					}

					case '=': {level = 2; break; } //door
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
					case '=': {level = 2; break; }
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
					case '=': {level = 2; break; }
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
					case '=': {level = 2; break; }
					}
				}

				break;
			}
			}

	//output GUI
	cout << "\n\nUse arrow keys to move.\n" << endl;
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


int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Sleep(Gamespeed);
	}
	return 0;
}
