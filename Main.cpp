#include <iostream> //for cout, endl
#include <windows.h> //for sys clr
#include <vector> //for 2d vector
#include "read2DMaze.h" //load maze from file
#include "GameLevel.h" //generate/save maze to file
#include <time.h> // for timer
#include <chrono> // for timer
#include <string.h> //for player name entry
#include <sstream> //for string parsing
#include <iomanip> //for output formatting
#include <string> //for to_string

using namespace std;

bool gameOver = false;
int Gamespeed = 100;
double countDown = 30;
int Score = 0;
int highestScore = 0;
int level = 1;
int menu = 0;
int width = 22, height = 10;
int playerX = 1, playerY = 1;
int playerX_Move, playerY_Move;
enum direction { NONE, LEFT, RIGHT, UP, DOWN };
direction dir;
char input;

char block = 219;
char box = '+';
char enemy = 248;
char door = 240;
char player = '@';

vector<int>::iterator it;
vec2d Map(SIZE + 1, vector<char>(0));
int columns = 0, rows = 0;

int ex1, ex2, ey1, ey2;

struct highscore {
	int score;
	string name;
};

vector<highscore> highscoreList;

void LoadScores(vector<highscore> &highscoreList) {
	ifstream file;
	int i = 0;
	string name, line, delim, tempName;
	int score;
	highscore loadScore;
	int tempScore;
	file.open("highscores.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			stringstream ss(line);
			ss >> score >> name;
			//cout << "score: " << score << "name: " << name;
			loadScore.score = score;
			loadScore.name = name;
			highscoreList.push_back(loadScore);
		}
		file.close();
		
	}

	//sort highscores
	for (int i = highscoreList.size() - 1; i > 0; i--) {
		int first = 0;
		for (int j = 1; j <= i; j++) {

			if (highscoreList[j].score > highscoreList[first].score) {
				first = j;
			}
				tempScore = highscoreList[first].score;
				tempName = highscoreList[first].name;
				highscoreList[first].score = highscoreList[i].score;
				highscoreList[first].name = highscoreList[i].name;
				highscoreList[i].score = tempScore;
				highscoreList[i].name = tempName;

			}

	}
	highestScore = highscoreList[0].score;
	//output highscores

	for (int i = highscoreList.size() -1; i > 0; i--) {
		cout << "\t\t\t[" << left << setw(30) << highscoreList[i].name << right << setw(10) << highscoreList[i].score << " ]" << endl;

	}

}

void Setup()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 800, 800, TRUE); // 800 width, 100 height

	system("color 1C");
	cout << "\n\n\n\n\n\n\n\n\nWelcome to\n";
	Sleep(500);
	cout << "\n\nText Dungeon\n\n";
	Sleep(1500);
	cout << "\n\n\t\tN) New Game\n\n";
	cout << "\n\t\tS) View High Scores\n\n\n\n\n\n";

	while (menu != 1) {

		cin >> input;

		if ((input == 'n') || (input == 'N')) {
			readMaze(Map, rows, columns);
			cout << "\n\nloading maze...\n";
			Sleep(1500);
			menu = 1;
		}
		else {
			cout << "\t\t\t\t   Highscores" << endl;
			LoadScores(highscoreList);

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
	cout << "\n +10 seconds\n";
	countDown += 3;
	Sleep(3000);
	GameLevel *oNewLevel = new GameLevel();
	oNewLevel->Update();
	vec2d NewMap(SIZE + 1, vector<char>(0));
	readMaze(NewMap, rows, columns);
	playerX = 1;
	playerY = 1;
	NewMap.swap(Map);
	countDown += 10;

	
}

int Draw(int &playerX, int &playerY)
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
			if (Map[i][j] == '|') {
				cout << block;
			}
			if (Map[i][j] == ' ') {
				cout << ' ';
			}
			if (Map[i][j] == '+') {
				cout << box;
			}
			if (Map[i][j] == '=') {
				cout << door;
			}
			if(Map[i][j] == '@'){
				cout << player;
			}
			if (Map[i][j] == '*') {
				cout << enemy;
			}
		}
		cout << endl;
	}
	file << "setting the char" << endl;
	Map[playerY][playerX] = '@'; //display character
	file << "set the char" << endl;
	file.close();

	//output GUI
	cout << "Use arrow keys to move." << endl;
	cout << player <<": Player" << endl;
	cout << door <<": Door" << endl;
	cout << enemy << ": Enemy" << endl;
	cout << box << ": Treasure" << endl;
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
						case '*':
						{
							Map[playerY][playerX] = ' ';
							playerY -= 1;
							Map[playerY_Move][playerX] = '*';
							dir = NONE;
							system("cls");
							Score -= 100;
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
						case '*':
						{
							Map[playerY][playerX] = ' ';
							playerY += 1;
							Map[playerY_Move][playerX] = '*';
							dir = NONE;
							system("cls");
							Score -= 100;
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
						case '*':
						{
							Map[playerY][playerX] = ' ';
							playerX += 1;
							Map[playerY][playerX_Move] = '*';
							dir = NONE;
							system("cls");
							Score -= 100;
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
						case '*':
						{
							Map[playerY][playerX] = ' ';
							playerX -= 1;
							Map[playerY][playerX_Move] = '*';
							dir = NONE;
							system("cls");
							Score -= 100;
							break;
						}
					}
				}

				break;
			}

			}

			//Move enemies
			Map[ey1][ex1] = '*'; //display character
			if ((ey1 == playerY) && (ex1 == playerX)) {
				Map[playerY][playerX] = ' ';
				return 1;
			}
			int enemyDirection1;
			int enemyDirection2;

			srand((unsigned)time(NULL));                    // Pick random seed


			enemyDirection1 = rand() % 4;
			enemyDirection2 = rand() % 4;
			if ((GetAsyncKeyState(VK_UP) != 0) || (GetAsyncKeyState(VK_DOWN) != 0) || (GetAsyncKeyState(VK_RIGHT) != 0) || (GetAsyncKeyState(VK_LEFT) != 0)) {
				if (enemyDirection1 == 0) {
					if (ey1 > 2) {
						if (Map[ey1][ey2] != '=') {
							Map[ey1][ex1] = ' ';
							Map[ey1 - 1][ex1] = '*';
							ey1 -= 1;
							srand((unsigned)time(NULL));
							enemyDirection1 = rand() % 4;
						}
						else {
							enemyDirection1 = rand() % 4;
						}

					}
				}
				if (enemyDirection1 == 1) {
					if (ey1 < rows - 2) {
						if (Map[ey1][ey2] != '=') {
							Map[ey1][ex1] = ' ';
							Map[ey1 + 1][ex1] = '*';
							ey1 += 1;
							srand((unsigned)time(NULL));                    // Pick random seed
							enemyDirection1 = rand() % 4;
						}
					}
					else {
						enemyDirection1 = rand() % 4;
					}

				}
				if (enemyDirection1 == 2) {
					if (ex1 < columns - 2) {
						if (Map[ey1][ey2] != '=') {
							Map[ey1][ex1] = ' ';
							Map[ey1][ex1 + 1] = '*';
							srand((unsigned)time(NULL));                    // Pick random seed
							enemyDirection1 = rand() % 4;
							ex1 += 1;
						}
					}
					else {
						enemyDirection1 = rand() % 4;
					}
				}
				if (enemyDirection1 == 3) {
					if (ex1 > 2) {
						if (Map[ey1][ey2] != '=') {
							Map[ey1][ex1] = ' ';
							Map[ey1][ex1 - 1] = '*';
							ex1 -= 1;
							srand((unsigned)time(NULL));                    // Pick random seed
							enemyDirection1 = rand() % 4;
						}
					}
					else {
						enemyDirection1 = rand() % 4;
					}

				}

				if (enemyDirection2 == 0) {
					if (ey2 > 2) {
						if (Map[ey2 - 1][ex2] == ' ') {
							Map[ey2][ex2] = ' ';
							Map[ey2 - 1][ex2] = '*';
							ey2 -= 1;
							srand((unsigned)time(NULL));
							enemyDirection2 = rand() % 4;
						}

					}
					else {
						enemyDirection2 = rand() % 4;

					}
				}
				if (enemyDirection2 == 1) {
					if (ey2 < rows - 2) {
						if (Map[ey2 + 1][ex2] == ' ') {
							Map[ey2][ex2] = ' ';
							Map[ey2 + 1][ex2] = '*';
							ey2 += 1;
							srand((unsigned)time(NULL));                    // Pick random seed
							enemyDirection2 = rand() % 4;
						}
					}
					else {
						enemyDirection2 = rand() % 4;
					}

				}
				if (enemyDirection2 == 2) {
					if (ex2 < columns - 2) {
						if (Map[ey2][ex2 + 1] == ' ') {
							Map[ey2][ex2] = ' ';
							Map[ey2][ex2 + 1] = '*';
							srand((unsigned)time(NULL));                    // Pick random seed
							enemyDirection2 = rand() % 4;
							ex2 += 1;
						}
					}
					else {
						enemyDirection2 = rand() % 4;
					}
				}
				if (enemyDirection2 == 3) {
					if (ex2 > 2) {
						if (Map[ey2][ex2 - 1] == ' ') {
							Map[ey2][ex2] = ' ';
							Map[ey2][ex2 - 1] = '*';
							ex2 -= 1;
							srand((unsigned)time(NULL));                    // Pick random seed

							enemyDirection2 = rand() % 4;
						}
					}
					else {
						enemyDirection2 = rand() % 4;
					}

				}

			}


			return 0;
}

int Input()
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
		return 1;
	}


	return 0;
}



void Save(vector<highscore> &highscoreList) {
	string name;
	cout << "Score: " << Score << endl;

	if (Score >= highestScore)
		cout << "\nHighscore!!!\n";
	cout << "\n\nEnter name: " << endl;
	cin >> name;

	ofstream file;
	file.open("highscores.txt", ios::app);
	if (file.is_open())
	{
		file << Score << " " << name << endl;
	}
	file.close();
}

int main()
{
	time_t start, end;
	double elapsedTime;
	int g, i;

	GameLevel *oLevel = new GameLevel();
	oLevel->Update();
	oLevel->getEnemyCoord(ex1, ex2, ey1, ey2);

	Setup();
	time(&start); //start the timer

	while (!gameOver)
	{
		do {
			time(&end);
			elapsedTime = difftime(end, start);
			g = Draw(playerX, playerY);
			i = Input();
			printf("Score: [ %d ]   Timer: [  %4.2f  ]\n", Score, countDown - elapsedTime);
			Sleep(Gamespeed);
			system("cls");
			if ((Score < 0) || (g > 0) || (i > 0)) {
				break;
			}
		} while (elapsedTime != countDown); //run for countDown seconds
		gameOver = true;
		Save(highscoreList);
		//system("cls");

	}

	cout << "Game Over\n";
	Sleep(4000);

	return 0;
}
