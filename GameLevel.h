#include <iostream>
#include <ctime> //for random num gen
#include <windows.h> // for clearing screen
#include <conio.h> // for getch()
#include <stack> //for backtracking path
#include <fstream> // for file io
#include <iomanip>
#include <vector>

#ifndef SIZE
#define SIZE 25
#endif
using namespace std;


class GameLevel
{
public:


	//PUBLIC DATA MEMBERS

	//CELL STRUCTURE
	struct Cell
	{
		bool visited;
		bool top_wall;
		bool bot_wall;
		bool left_wall;
		bool right_wall;
		char display;
	};

	Cell Level[SIZE][SIZE];
	int posX, posY;
	int playerX_Move, playerY_Move;
	int goalX, goalY;
	int startX = 2, startY = 2;
	int level = 1;


	//PUBLIC FUNCTIONS

	//INITIALIZE MAZE
	void Init()
	{
		for(int i = 0; i < SIZE; i++)
		{
			for(int j=0; j < SIZE; j++)
			{
				Level[i][j].display = '|';
				Level[i][j].visited = false;
				Level[i][j].top_wall= true;
				Level[i][j].bot_wall= true;
				Level[i][j].left_wall= true;
				Level[i][j].right_wall= true;
			}
		}

		for(int i = 1; i <SIZE-1; i++)
		{
			for(int j = 1; j<SIZE-1; j++)
			{
				Level[1][j].top_wall = false;
				Level[SIZE-2][j].bot_wall = false;
				Level[i][1].left_wall = false;
				Level[i][SIZE-2].right_wall = false;
			}
		}

		GenMaze(Level, posX, posY, goalX, goalY, startX, startY);				// Generate Maze
	}//end initialize definition

	//Draw MAZE
	void Draw(vector<vector<char> > &Map, int rows, int columns)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				cout << Map[i][j];
			}
			cout << endl;
		}

	}//end Draw() function

	void Draw()
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j<SIZE; j++)
				cout << Level[i][j].display;
		}
		cout << endl;


	}

	//SAVE MAZE
	void Save()
	{
		ofstream file;
		if (remove("currentMaze.txt") != 0)
			perror("Error deleting file");

		file.open("currentMaze.txt");
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				file << Level[i][j].display;             //save maze to file
			} 
			file << endl;

		}
		file.close();
	}

	void Update()
	{
		Init();
		Save();
	}

	int getStartX() { return startX; }
	int getStartY() { return startY; }


private:

	//PRIVATE DATA MEMBERS

	//PRIVATE FUNCTION DECLARATIONS

	//GENERATE MAZE
	void GenMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY, int &startX, int &startY)
	{
		srand((unsigned)time(NULL));                    // Pick random seed

		int random;
		//int randomX = ((2 * rand()) + 1) % (SIZE - 1);          // Generate random odd num between 1 and SIZE for starting place
		//int randomY = ((2 * rand()) + 1) % (SIZE - 1);
		int randomX = 1;
		int randomY = 1;
		posX = randomX;																	// Save player's initial x,y positions				
		posY = randomY;
		int visitedCells = 1;
		int totalCells = ((SIZE - 1) / 2)*((SIZE - 1) / 2);     // Total maze cells excluding display and border cells
		int percent;
		stack<int> back_trackX, back_trackY;            // Stack used to trace the reverse path

		Level[randomY][randomX].display = '_';			//Set _ as entrance ( start cell )
		startX = randomX;
		startY = randomY-1;
		Level[randomY][randomX].visited = true;

		while (visitedCells < totalCells)
		{
			if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true) && (Level[randomY - 2][randomX].bot_wall == true)) ||
				((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true) && (Level[randomY + 2][randomX].top_wall == true)) ||
				((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true) && (Level[randomY][randomX - 2].right_wall == true)) ||
				((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true) && (Level[randomY][randomX + 2].left_wall == true))) {

				random = (rand() % 4 + 1);                    // Pick a random wall 1-4 to knock down
				//GO UP
				if ((random == 1) && (randomY > 1))
				{
					if (Level[randomY - 2][randomX].visited == false)  //if not visited
					{
						Level[randomY - 1][randomX].display = ' ';      //carve path
						Level[randomY - 1][randomX].visited = true;     //mark visited
						Level[randomY][randomX].top_wall = false;     //knock down wall

						back_trackX.push(randomX);                    //save X for backtrack
						back_trackY.push(randomY);                    //save Y for backtrack

						randomY -= 2;                                 //move to next cell
						Level[randomY][randomX].visited = true;       //mark visited
						Level[randomY][randomX].display = ' ';        //carve path
						Level[randomY][randomX].bot_wall = false;     //knock down wall
						visitedCells++;                               //increment visited cells
					}
					else
						continue;
				}
				//GO DOWN 
				else if ((random == 2) && (randomY < SIZE - 2))
				{
					if (Level[randomY + 2][randomX].visited == false)  //if not visited
					{
						Level[randomY + 1][randomX].display = ' ';      //carve path
						Level[randomY + 1][randomX].visited = true;     //mark visited
						Level[randomY][randomX].bot_wall = false;     //knock down wall

						back_trackX.push(randomX);                    //save X for backtrack
						back_trackY.push(randomY);                    //save Y for backtrack

						randomY += 2;                                 //move to next cell
						Level[randomY][randomX].visited = true;       //mark visited
						Level[randomY][randomX].display = ' ';        //carve path
						Level[randomY][randomX].top_wall = false;     //knock down wall
						visitedCells++;                               //increment visited cells
					}
					else
						continue;
				}
				//GO LEFT 
				else if ((random == 3) && (randomX > 1))
				{
					if (Level[randomY][randomX - 2].visited == false)  //if not visited
					{
						Level[randomY][randomX - 1].display = ' ';      //carve path
						Level[randomY][randomX - 1].visited = true;     //mark visited
						Level[randomY][randomX].left_wall = false;     //knock down wall

						back_trackX.push(randomX);                    //save X for backtrack
						back_trackY.push(randomY);                    //save Y for backtrack

						randomX -= 2;                                 //move to next cell
						Level[randomY][randomX].visited = true;       //mark visited
						Level[randomY][randomX].display = ' ';        //carve path
						Level[randomY][randomX].right_wall = false;     //knock down wall
						visitedCells++;                               //increment visited cells
					}
					else
						continue;
				}
				//GO RIGHT 
				else if ((random == 4) && (randomX < SIZE - 2))
				{
					if (Level[randomY][randomX + 2].visited == false)  //if not visited
					{
						Level[randomY][randomX + 1].display = ' ';      //carve path
						Level[randomY][randomX + 1].visited = true;     //mark visited
						Level[randomY][randomX].right_wall = false;     //knock down wall

						back_trackX.push(randomX);                    //save X for backtrack
						back_trackY.push(randomY);                    //save Y for backtrack

						randomX += 2;                                 //move to next cell
						Level[randomY][randomX].visited = true;       //mark visited
						Level[randomY][randomX].display = ' ';        //carve path
						Level[randomY][randomX].left_wall = false;     //knock down wall
						visitedCells++;                               //increment visited cells
					}
					else
						continue;
				}
			}
			else                                                        //backtrack using stack
			{
				randomX = back_trackX.top();                           //save the top of stack so we can backtrack
				back_trackX.pop();                                    //pop top of the stack

				randomY = back_trackY.top();
				back_trackY.pop();
			}
		}
		goalX = randomX;
		goalY = randomY;
		Level[goalY][goalX].display = '=';                    //display exit door
		system("cls");
		//Draw();
	}//end Update() function

}; //end GameLevel class

/*class Player: public GameLevel
{
public:
	//PUBLIC DATA MEMBERS
	int width = SIZE, height = SIZE;
	int playerX, playerY;
	int playerX_Move, playerY_Move;

	//PUBLIC FUNCTIONS
	Player(int x, int y)
	{
		playerX = x;
		playerY = y;
		

	}

	//INITIALIZE PLAYER
	void Init()
	{

	}

	//Draw PLAYER
	void Draw(vec &Map)
	{
		//Map[0][0] = '@'; //display character
	}

	//SAVE PLAYER
	void Save()
	{

	}
private:

	//PRIVATE DATA MEMBERS

	//PRIVATE FUNCTION DECLARATIONS
};*/


/*//MAIN
int main()
{
	GameLevel oLevel1;
	oLevel1.Init();											// Initialize
	oLevel1.Save();											// Save to txt file

	bool game_over = false;

	while (!game_over)
	{
		system("cls");
		oLevel1.Draw();										// Draw
		Sleep(200);
	}
	return 0;
}
*/
