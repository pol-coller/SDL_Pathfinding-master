#pragma once
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <time.h>
////#include "Agent.h" //
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "SDL_SimpleApp.h"
#include <time.h>

class Grid
{
public:
	Grid(char* filename);
	~Grid();

	struct pointsLine	//NEW
	{
		Vector2D initPoint, endPoint;

		pointsLine() { initPoint = endPoint = Vector2D(0, 0); }
	};

private:
	int num_cell_x;
	int num_cell_y;

	std::vector< std::vector<int> > terrain;
	std::vector<pointsLine> walls;	//NEW

	void initWalls();	//NEW

public:

	//GETTERS//
	inline std::vector<pointsLine> getWalls() { return walls; }	//NEW
	bool isValidCell(Vector2D cell);
	int getNumCellX();
	int getNumCellY();
	int getCellWeight(Vector2D cell);
	//UTILS//
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
};
