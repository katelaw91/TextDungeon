#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "randomGen.cpp"
using namespace std;
using vec = vector<vector<char> >; //alias for 2D vector

class Level
{
	public:

		//data members
		int width = 20, height = 10;
		vec lvl;

		int r = width/2, c = height;
		//constructor
		Level(int w, int h)
		{
			width = w;
			height = h;
			lvl = makeRoom(w, h);
		}

		//member functions()
		vec getLevel(){return lvl;}
		void displayRoom()
		{
    	// Displaying the 2D vector
			for (int i = 0; i < lvl.size(); i++ )
			{
   			for (int j = 0; j < lvl[i].size(); j++ )
      		cout << lvl[i][j];
   			cout << endl;
			}
		}	

	
		//setLevel()

	private:

		//data members

		//member functions()
		vec makeRoom(int columns, int rows) 
		{ 
    		int i, j; 
				// Initializing 2D vector
				vec MapV;

				//store map in vect
				for (i = 1; i <= columns; i++) 
    		{ 
					vector<char> RowsV; //initialize inner vect (each row)
        		for (j = 1; j <= rows; j++) 
        		{ 
            		if (i==1 || i==columns || j==1 || j==rows)             
										RowsV.push_back('#');
								
            		else
										RowsV.push_back('*');
        		}	

        		MapV.push_back(RowsV); //store row to outer vect
   		 } 
				int x = randomNum(1, height);
				int y = width -2;
				//display random point with 0
				MapV[y+1][x] = '_'; //char representing entrance
				MapV[y][x] = ' ';
			 	recursivePath(MapV, x, y);
	
				return MapV;
		}

		void recursivePath(vec &MapV,int x, int y) //carves maze into vec by reference
		{
				//make array of random directions
				int directionArray[15] = {2,0,2,3,1,3,0,2,2,0,1,2,3,0,1};
				
				//switch on array of random directions
				//check 2 spaces in a random direction, if not path or wall, fill chars
				for(int i = 0; i < 14; i++)
				{
					switch(directionArray[i]){
						case 0: //UP
							if((y-2 > 0) && (MapV[y-2][x] == '*')){
									MapV[y-2][x] = ' ';
									MapV[y-1][x] = ' ';
									y-=2;}
									//recursivePath(MapV, x, y);}
							break;
						case 1: //DOWN
							if(y+2 >= height-1) //if y coord is outside bottom of map
								continue;
							if(MapV[y+2][x] == '*'){
									MapV[y+2][x] = ' ';
									MapV[y+1][x] = ' ';
									y+=2;}
									//recursivePath(MapV, x, y+2);}
							break;
						case 2: //LEFT
							if(x-2 <= 0) //if x coord is outside map
								continue;
							if(MapV[y][x-2] == '*'){
									MapV[y][x-2] = ' ';
									MapV[y][x-1] = ' ';
									x-=2;}
									//recursivePath(MapV, x, y);}
							break;
						case 3: //RIGHT
							if(x+2 >= width-1) //if x coord is outside map
								continue;
							if(MapV[y][x+2] == '*') {
									MapV[y][x+2] = ' ';
									MapV[y][x+1] = ' ';
									x+=2;}
									//recursivePath(MapV, x, y);}
							break;
						default: 
							cout << "direction value out of range" << endl;
				}	
			}
		} //end recursivePath

}; //end class

int main()
{
	int h, w;
	//vec r;
	cout << "Enter height, width" << endl;
	cin >> h >> w;

	Level olvl1(w,h);
	olvl1.displayRoom();

	//r= makeRoom(h, w);
		return 0;
}
