/*
	This is the CPPWidget.h header.
	//class to make and display levels, stored in 2D vector (vector of char vectors) grid


*/

#ifndef CPPWIDGET_H
#define CPPWIDGET_H

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

using namespace std;

class CPPWidget
{
public:
	CPPWidget()
	{
		cout << "Object of type CPPWidget is created." << endl;
	}

	virtual void draw() {
		cout << "This a virtual function." << endl;
	}
};

class Level:public CPPWidget
{
public:
	//data members
	int widthX = 0, heightY = 0;
	int playerX = 1, playerY = 1; // ori player XY
	int NPlayerX = 1, NPlayerY = 1; // new player XY
	vector<vector<char>> level;

	//constructor
	Level(vector<vector<char>> CLevelMAP)  //It can find player location when object is created
	{
		for (int i = 0; i < CLevelMAP.size(); i++)
		{
			heightY += 1;
			for (int j = 0; j < CLevelMAP[i].size(); j++)
			{
				widthX += 1;
				if (CLevelMAP[i][j] == '@')
				{
					playerX = i;
					playerY = j;
				}
			}
		}
		level = CLevelMAP;
		level[playerY][playerX] = '@';
	}

	//member functions()
	
	int getHeight() { return heightY; }
	int getWidth() { return widthX; }
	int getPlayerX() { return playerX; }
	int getPlayerY() { return playerY; }

	void draw()
	{
		// Displaying the 2D vector and the player at the same time
		for (int i = 0; i < level.size(); i++)
		{
			for (int j = 0; j < level[i].size(); j++)
				cout << level[i][j];
			cout << endl;
		}
	}

	template <class TPlayer>
	void changePlayerPos(TPlayer CPlayer)
	{
		NPlayerX = CPlayer.getPlayerX();
		NPlayerY = CPlayer.getPlayerY();
		if (level[playerY][playerX] != '#')
		{
			level[playerY][playerX] = ' '; //change the orginal position to be ' '
			level[NPlayerY][NPlayerX] = '@'; //after position chagned, update player position
			playerY = NPlayerY; // replace the new to ori
			playerX = NPlayerX; // replace the new to ori
		}	
	}

};

class Player :public Level
{
public:
	int x;
	int y;
	int lifes;
	char movingDirection;   /// As in 'w' = UP; 's' = DOWN; 'a' = LEFT; 'd' = RIGHT
	bool lostLife;
	int checkPoint;

	//constructor
	template <class TLevel>
	Player(TLevel CLevelObject)
	{
		x = CLevelObject.getPlayerX();
		y = CLevelObject.getPlayerY();
	}

	int getPlayerX() { return x; }
	int getPlayerY() { return y; }
};

#endif