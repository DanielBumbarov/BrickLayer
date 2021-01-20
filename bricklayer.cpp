#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class BrickLayer
{
private:
	int gridRows, gridCols;
	vector<vector<int>> brickGridData;

	//input space-separated brick IDs and convert to vector data
	vector<vector < int>> inputVectors() {
		string line;
		int number;
		vector<vector<int>> grid;
		grid.resize(gridRows);
		for (int i = 0; i < gridRows; i++)
		{
			getline(cin, line);
			istringstream stream(line);
			while (stream >> number) {
				grid[i].push_back(number);
			}
		}
		return grid;
	}
public:
	bool solved = false;
	BrickLayer(vector<int>dimensions) {
		gridRows = dimensions[0];
		gridCols = dimensions[1];
		brickGridData = inputVectors();

	}
	//print the brick grid
	void printGrid() {
		for (unsigned int i = 0; i < brickGridData.size(); i++)
		{
			for (unsigned int j = 0; j < brickGridData[i].size(); j++)
			{
				cout << brickGridData[i][j] << " ";
			}
			cout << endl;
		}
	}
	//check grid validity
	bool isvalid() {
		if (gridRows == brickGridData.size())
		{
			for (unsigned int i = 0; i < brickGridData.size(); i++)
			{
				if (brickGridData[i].size() != gridCols) return false;
			}
		}
		return true;
	}
	//construct next layer according to the user input
	//looks where to place a pair of brick IDs in every direction. If it does not overlap a brick, a brick will be placed
	void nextlayer() {
		vector<vector<int>> nextLayerGrid(gridRows, vector<int>(gridCols, 0));
		vector<int>modifiedBricks(gridRows * gridCols, 1);
		int brickID = 1;
		bool placedBrick = false;
		for (int i = 0; i < gridRows; i++)
		{
			for (int j = 0; j < gridCols; j++) {
				if(nextLayerGrid[i][j]==0)
				{
					placedBrick = false;
					if (j < gridCols - 1) {
						if (brickGridData[i][j] != brickGridData[i][j + 1] && placedBrick == false) {
							nextLayerGrid[i][j] = brickID; nextLayerGrid[i][j + 1] = brickID;
							modifiedBricks.push_back(brickID);
							brickID++; placedBrick = true;
						}
					}
					if (i < gridRows - 1) {
						if (brickGridData[i][j] != brickGridData[i + 1][j] && placedBrick == false)
						{
							nextLayerGrid[i][j] = brickID; nextLayerGrid[i + 1][j] = brickID;
							modifiedBricks.push_back(brickID);
							brickID++; placedBrick = true;
						}
					}
					if (i > 0) {
						if (brickGridData[i][j] != brickGridData[i - 1][j] && placedBrick == false)
						{
							nextLayerGrid[i][j] = brickID; nextLayerGrid[i - 1][j] = brickID;
							modifiedBricks.push_back(brickID);
							brickID++; placedBrick = true;
						}
					}
					if (j > 0) {
						if (brickGridData[i][j] != brickGridData[i][j - 1] && placedBrick == false)
						{
							nextLayerGrid[i][j] = brickID; nextLayerGrid[i][j - 1] = brickID;
							modifiedBricks.push_back(brickID);
							brickID++; placedBrick = true;
						}
					}
				}
			}
		}
			//if there is a zero inside the newly created layer of bricks, it means the algorithm failed somewhere and it isnt solved.
		for (int i = 0; i < nextLayerGrid.size(); i++) 
			if ((find(nextLayerGrid[i].begin(), nextLayerGrid[i].end(), 0) != nextLayerGrid[i].end()) == false) solved = true;
			
	
		if (solved) {
			brickGridData = nextLayerGrid;
			cout << "Grid Solved:" << endl;
			printGrid();
		}
		else cout << "Failed to solve grid!";
	}
};

//collects user input for grid dimensions. too generic for bricklayer class...
vector<int> getDimensions() {
	vector<int> xy;
	std::string input;
	getline(cin, input); // get input until newline
	istringstream sstr(input);
	int inputpair;

	while (sstr >> inputpair) {
		xy.push_back(inputpair);
	}
	return xy;
}


int main() {

	vector<int> dimensions = getDimensions();

	BrickLayer layer(dimensions);
	if (layer.isvalid()) {
		cout << "Starting Arrangement:"<<endl;
		layer.printGrid();
		layer.nextlayer();
	}
	else {
		cout << "Invalid Arrangement! Check your input!";
		getchar();
		return 0;
	}
}