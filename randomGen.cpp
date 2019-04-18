#ifndef RANDOMGEN_CPP
#define RANDOMGEN_CPP
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
vector<int> randomCoord(int height, int width)
{
	vector <int> coord;
	int x, y;
	//initialize random seed from clock:
	srand (time(NULL));

	//generate random numbers
	x = rand() % width + 1;
	y = rand() % height + 1;

	coord.push_back(x);
	coord.push_back(y);

	return coord;
}

int randomNum(int min, int max)
{
	int x;
	x= rand() % max + min;
	return x;
}

#endif
