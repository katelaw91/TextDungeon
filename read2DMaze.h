#include <iostream> // for cout
#include <fstream> // for file io
#include <vector> // for vectors
#include <string> // for getline
using namespace std;
using vec2d = vector<vector<char> >;

void readMaze(vec2d &Map, int &rows, int &cols)
{
	ifstream file("currentMaze.txt");
	string row;
	char c;
		
		for(int j = 0; getline(file,row); j++)
		{	
			for(int i = 0; i < row.length(); i++)
			{
				Map[j].push_back(row[i]);
				//cout << Map[j][i];
				cols = row.length();
			}
		//cout << endl;
		rows++;
		}

}


/*int main()
{
	int columns =0, rows = 0;
	vector<vector<char> > Map(SIZE, vector<char>(0));
	readMaze(Map, rows, columns);
	//cout << "columns: " << columns << endl;
	//cout << "rows: " << rows << endl;

	for(int i = 1; i < rows; i++)
		{
			for(int j=0; j < columns; j++)
			{
				cout << Map[i][j];
			}
			cout << endl;
		}

	return 0;
}
*/
