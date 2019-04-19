#include <iostream>
#include <ctime> //for random num gen
#include <windows.h> // for clearing screen
#include <conio.h> // for getch()
#include <stack> //for backtracking path
#include <fstream> // for file io

using namespace std;
#define SIZE 31 //size of maze has to be odd for traversing reasons

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

//FUNCTION DECLARATIONS
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]);
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY);
//void Save(Cell Level[][SIZE]);

//MAIN
int main()
{
	Cell Level[SIZE][SIZE];
	int posX, posY;
	int goalX, goalY;
	bool game_over = false;

	while(!game_over)
	{
		system("cls");
		Initialize(Level);                             // Initialize
		Redraw(Level);                                 // Draw
		GenerateMaze(Level, posX, posY, goalX, goalY); // Generate Maze
		//Save(Level);                                   // Save to txt file

		char input;																		 // Key input
		cout << "Create a new Maze? (Y)/(N): ";
		cin >> input;

		if((input != 'n') && (input != 'N') && (input != 'y') && (input != 'Y'))
			cout << "Invalid command, please try again." << endl;
		else if((input == 'n') || (input == 'N'))      // Exit Game
		{
			game_over = true;
			cout << "Good bye!" << endl;
		}
	} //end main while loop

	_getch();
	return 0;
}

//INITIALIZE MAZE
void Initialize(Cell Level[][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			Level[i][j].display = '*';
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
}//end initialize definition

//CLEAR SCREEN
void ClearScreen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);

}//end clearscreen() function

//REDRAW MAZE
void Redraw(Cell Level[][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		cout << endl;
		for(int j=0; j<SIZE; j++)
			cout << " " << Level[i][j].display;
	}
}//end redraw() function

//GENERATE MAZE
void GenerateMaze(Cell Level[][SIZE], int &posX, int &posY, int &goalX, int &goalY)
{
	srand((unsigned)time(NULL));                    // Pick random seed

	int random;
	int randomX = ((2*rand())+1)%(SIZE-1);          // Generate random odd num between 1 and SIZE
	int randomY = ((2*rand())+1)%(SIZE-1);          
	posX = randomX;																	// Save player's initial x,y positions				
	posY = randomY;
	int visitedCells = 1;
	int totalCells = ((SIZE-1)/2)*((SIZE-1)/2);     // Total maze cells excluding display and border cells
	int percent;
	stack<int> back_trackX, back_trackY;            // Stack used to trace the reverse path

	Level[randomY][randomX].display = '_';          //Set _ as entrance ( start cell )
	Level[randomY][randomX].visited = true;

	while(visitedCells < totalCells)
	{
		if(((Level[randomY-2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true) && (Level[randomY-2][randomX].bot_wall == true)) ||
		  ((Level[randomY+2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true) && (Level[randomY+2][randomX].top_wall == true)) ||
		  ((Level[randomY][randomX-2].visited == false) && (Level[randomY][randomX].left_wall == true) && (Level[randomY][randomX-2].right_wall == true)) ||
		  ((Level[randomY][randomX+2].visited == false) && (Level[randomY][randomX].right_wall == true) && (Level[randomY][randomX+2].left_wall == true))){
			
				random = (rand()%4+1);                    // Pick a random wall 1-4 to knock down
				//GO UP
				if((random == 1) && (randomY > 1))
				{
					if(Level[randomY-2][randomX].visited == false)  //if not visited
					{
						Level[randomY-1][randomX].display = ' ';      //carve path
						Level[randomY-1][randomX].visited = true;     //mark visited
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
			percent = (visitedCells*100/totalCells*100)/100;   //progress in percentage
			cout << endl << "         Generating a Random Maze..." << percent << "%" << endl;
		}
		else                                                 //backtrack using stack
		{
			randomX = back_trackX.top();                       //save the top of stack so we can backtrack
			back_trackX.pop();                                 //pop top of the stack

			randomY = back_trackY.top();
			back_trackY.pop();
		}
		ClearScreen();
		Redraw(Level);
	}
	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = '=';                    //display exit door
	system("cls");
	ClearScreen();
	Redraw(Level);
	cout << endl << "\a\t       Complete!" << endl;       //display alert
}//end generatemaze() function
