/*
 * Mining.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: Green
 */

#include <iostream>

#define MAX_X 32
#define MAX_Y 12
#define MAX_Z 32
const int TOTAL_BLOCKS = MAX_X * MAX_Y * MAX_Z;

using namespace std;

//void generateOres(int mine[MAX_X][MAX_Y][MAX_Z], int seed); // 0 is always stone.
															// 1 is always air.
void createBranchMine(int mine[MAX_X][MAX_Y][MAX_Z], int spacing, int height, int width, int & blocksMined);
void calculateEfficiency(int mine[MAX_X][MAX_Y][MAX_Z], bool uncovered[MAX_X][MAX_Y][MAX_Z], double & efficiency, int spacing, int height, int width, int blocksMined, int & blocksUncovered);
void displayMine(int mine[MAX_X][MAX_Y][MAX_Z], double & efficiency, int spacing, int height, int width, int blocksMined, int blocksUncovered);

int main()
{
	int mine[MAX_X][MAX_Y][MAX_Z] = {0};
	bool uncovered[MAX_X][MAX_Y][MAX_Z] = {false};
	int spacing = 3;
	int height = 1;
	int width = 1;
	int blocksMined = 0;
	int blocksUncovered = 0;
	double efficiency = 0.0F;

	createBranchMine(mine, spacing, height, width, blocksMined);
	calculateEfficiency(mine, uncovered, efficiency, spacing, height, width, blocksMined, blocksUncovered);
	displayMine(mine, efficiency, spacing, height, width, blocksMined, blocksUncovered);

	return 0;
}

/**
 * Name: createBranchMine();
 * 	Description: Creates a branch mine from the 2 dimensional array mine[][][].
 * 				The branch mine uses 1 to signifying air blocks that have been mined.
 * 				This function also keeps track of the number of blocks mined.
 * 	Parameters: int[][][] mine, int spacing, int height, int & blocksMined
 * 				mine[][][]
 * 					>> The 3D array of the mine.
 * 				spacing
 * 					>> Used to determine the spaces for each branch.
 * 				height
 * 					>> Height of each branch.
 * 				& blocksMined
 * 					>> Call by reference value that is the number of blocks mined.
 * 	Returns: void.
 *
 */
void createBranchMine(int mine[MAX_X][MAX_Y][MAX_Z], int spacing, int height, int width, int & blocksMined)
{
	int yLayer = 1;
	for (int x = 0; x < MAX_X;)
	{
		for (int j = 0; j < width; j++)
		{
			for (int z = 0; z < MAX_Z; z++)
			{
				for (int y = yLayer; y < height + yLayer; y++)
				{
					mine[x+j][y][z] = 1;
					blocksMined++;
				}
			}
		}
		x+=spacing;
	}
}

void displayMine(int mine[MAX_X][MAX_Y][MAX_Z], double & efficiency, int spacing, int height, int width, int blocksMined, int blocksUncovered)
{
	cout << "+";
	for (int x = 0; x < MAX_X; x++)
	{
		cout << "-";
	}
	cout << "+" << endl;
	for (int x = 0; x < MAX_X; x++)
	{
		cout << "|";
		for (int z = 0; z < MAX_Z; z++)
		{
			cout << mine[x][1][z];
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int x = 0; x < MAX_X; x++)
	{
		cout << "-";
	}
	cout << "+" << endl;
	cout << "=> Statistics <=" << endl;
	cout << "Efficiency: " << efficiency << endl;
	cout << "Spacing: " << spacing << endl;
	cout << "Height: " << height << endl;
	cout << "Width: " << width << endl;
	cout << "Blocks mined: " << blocksMined << endl;
	cout << "Blocks uncovered: " << blocksUncovered << endl;
}

void calculateEfficiency(int mine[MAX_X][MAX_Y][MAX_Z], bool uncovered[MAX_X][MAX_Y][MAX_Z], double & efficiency, int spacing, int height, int width, int blocksMined, int & blocksUncovered)
{
	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			for (int z = 0; z < MAX_Z; z++)
			{
				// X#X
				// # #
				// # #
				// X#X
				// Do not parse corners!!
				if (mine[x][y][z] == 1)
				{
					if (mine[x+1][y][z] == 0 && uncovered[x+1][y][z] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
					if (mine[x-1][y][z] == 0 && uncovered[x-1][y][z] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
					if (mine[x][y+1][z] == 0 && uncovered[x][y+1][z] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
					if (mine[x][y-1][z] == 0 && uncovered[x][y-1][z] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
					if (mine[x][y][z+1] == 0 && uncovered[x][y][z+1] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
					if (mine[x][y][z-1] == 0 && uncovered[x][y][z-1] == false)
					{
						blocksUncovered++;
						uncovered[x+1][y][z] = true;
					}
				}
			}
		}
	}

	efficiency = (double) blocksMined / (double) blocksUncovered;
}


