//class to make and display levels, stored in 2D vector (vector of char vectors) grid
#include <iostream>
#include <vector>
using namespace std;


class Level
{
public:

	//data members
	int width = 20, height = 10;
	vector<vector<char> > lvl;

	//constructor
	Level(int w, int h)
	{
		width = w;
		height = h;
		lvl = makeRoom(w, h);
	}

	//member functions()
	vector<vector<char> > getLevel() { return lvl; }
	int getHeight() { return height; }
	int getWidth() { return width; }

	void displayRoom()
	{
		// Displaying the 2D vector
		for (int i = 0; i < lvl.size(); i++)
		{
			for (int j = 0; j < lvl[i].size(); j++)
				cout << lvl[i][j];
			cout << endl;
		}
	}


	//setLevel()

private:

	//data members

	//member functions()
	vector<vector<char> > makeRoom(int columns, int rows)
	{
		int i, j;
		// Initializing 2D vector
		vector<vector<char> > MapV;

		//store map in vect
		for (i = 1; i <= columns; i++)
		{
			vector<char> RowsV; //initialize inner vect (each row)
			for (j = 1; j <= rows; j++)
			{
				if (i == 1 || i == columns || j == 1 || j == rows)
					RowsV.push_back('#');

				else
					RowsV.push_back(' ');
			}

			MapV.push_back(RowsV); //store row to outer vect
		}
		return MapV;
	}
	
};

