/*
	This is the main.cpp game.



*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "CPPWidget.h";

using vec = vector<vector<char> >; //alias for 2D vector for easier re-typing

vector<vector<char>> level1Map = {	"##########=#########",
									"#                  #",
									"#                  #",
									"#                  #",
									"#                  #",
									"#                  #",
									"#                  #",
									"#                  #",
									"#@                 #",
									"####################" };

bool gameOver = false;
int Gamespeed = 100;
int level = 1;
enum direction { NONE, LEFT, RIGHT, UP, DOWN };
direction dir;
Level level1(level1Map);
Player player(level1);


void Setup()
{
	cout << "\n\n\n\n\n\n\n\n\nWelcome to\n";
	Sleep(500);
	cout << "\n\nText Dungeon\n\n";
	Sleep(1500);
	cout << "\n\n<insert menu/instructions here or something>...\n\n";
	Sleep(2000);

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

void ChangePlayerPosition()  //Here we get the input and change player position
{
	if (dir == UP)
	{
		player.y -= 1;
		level1.changePlayerPos(player);
	}
	if (dir == DOWN)
	{
		player.y += 1;
		level1.changePlayerPos(player);
	}
	if (dir == LEFT)
	{
		player.x -= 1;
		level1.changePlayerPos(player);
	}
	if (dir == RIGHT)
	{
		player.x += 1;
		level1.changePlayerPos(player);
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		system("cls"); //clear the screen

		Input();

		ChangePlayerPosition();
		
		level1.draw();

		cout << "\n\nUse arrow keys to move.\n" << endl;
		cout << "@: Player" << endl;
		cout << "=: Door" << endl;

		Sleep(Gamespeed);
	}
	return 0;
}