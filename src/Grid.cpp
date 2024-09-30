#include "Grid.h"

using namespace std;

Grid::Grid(char* filename)
{
	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;

	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	//llegueix lineas fins que no hi ha mes
	while (std::getline(infile, line))
	{
		vector<int> terrain_row;
		std::stringstream lineStream(line);
		std::string cell;
		while (std::getline(lineStream, cell, ','))
			terrain_row.push_back(atoi(cell.c_str()));
		SDL_assert(terrain_row.size() == num_cell_x);
		terrain.push_back(terrain_row);
	}
	SDL_assert(terrain.size() == num_cell_y);
	infile.close();

	initWalls();
}

Grid::~Grid()
{
}

int Grid::getNumCellX()
{
	return num_cell_x;
}

int Grid::getNumCellY()
{
	return num_cell_y;
}


Vector2D Grid::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Grid::pix2cell(Vector2D pix)
{
	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

void Grid::initWalls()
{

	Vector2D _initPos(0, 0), endPos(0, 0);
	int count = 0;

	for (int j = 0; j < num_cell_y; j++)
	{
		//count = 0;
		for (int i = 0; i < num_cell_x - 1; i++)
		{
			if (!isValidCell(Vector2D((float)i, (float)j)))
			{
				count = 1;
				_initPos = Vector2D((float)i, (float)j);	//Pos primera
				i++;

				for (i; i < num_cell_x - 1; i++)
				{
					if (!isValidCell(Vector2D((float)i, (float)j)) && i < num_cell_x - 2) { count++; endPos = Vector2D((float)i, (float)j); }

					else if (!isValidCell(Vector2D((float)i, (float)j)) && i == num_cell_x - 2) {
						count++;	endPos = Vector2D((float)i, (float)j);
						pointsLine pl;	pl.initPoint = _initPos;	pl.endPoint = endPos;	walls.push_back(pl); break;
					}

					else if (isValidCell(Vector2D((float)i, (float)j)) && count >= 2) {
						pointsLine pl; pl.initPoint = _initPos; pl.endPoint = endPos;
						walls.push_back(pl); break;
					}



					else  break;
				}

			}

		}
	}
	for (int i = 0; i < num_cell_x; i++)
	{
		//count = 0;
		for (int j = 0; j < num_cell_y - 1; j++)
		{
			if (!isValidCell(Vector2D((float)i, (float)j)))
			{
				count = 1;
				_initPos = Vector2D((float)i, (float)j);	//Pos primera
				j++;

				for (j; j < num_cell_y - 1; j++)
				{
					if (!isValidCell(Vector2D((float)i, (float)j)) && j < num_cell_y - 2) { count++; endPos = Vector2D((float)i, (float)j); }

					else if (!isValidCell(Vector2D((float)i, (float)j)) && j == num_cell_y - 2) {
						count++;	endPos = Vector2D((float)i, (float)j);
						pointsLine pl;	pl.initPoint = _initPos;	pl.endPoint = endPos;	walls.push_back(pl); break;
					}

					else if (isValidCell(Vector2D((float)i, (float)j)) && count >= 2) {
						pointsLine pl; pl.initPoint = _initPos; pl.endPoint = endPos;
						walls.push_back(pl); break;
					}



					else  break;
				}

			}

		}
	}

}

//void Grid::initWalls()
//{
//
//	Vector2D _initPos(0, 0), endPos(0, 0);
//	int count = 0;
//
//	for (int j = 0; j < num_cell_y; j++)
//	{
//		//count = 0;
//		for (int i = 0; i < num_cell_x; i++)
//		{
//
//			if (!isValidCell(Vector2D((float)i, (float)j)))
//			{
//				count = 1;
//				_initPos = Vector2D((float)i, (float)j);	//Pos primera
//				i++;
//
//				for (i; i < num_cell_x - 1; i++)
//				{
//					if (!isValidCell(Vector2D((float)i, (float)j)) && i < num_cell_x - 1) { count++; endPos = Vector2D((float)i, (float)j); }
//
//					else if (!isValidCell(Vector2D((float)i, (float)j)) && i == num_cell_x - 1) {
//						count++;	endPos = Vector2D((float)i, (float)j);
//						pointsLine pl;	pl.initPoint = _initPos;	pl.endPoint = endPos;	walls.push_back(pl); break;
//					}
//
//					else if (isValidCell(Vector2D((float)i, (float)j)) && count >= 2) {
//						pointsLine pl; pl.initPoint = _initPos; pl.endPoint = endPos;
//						walls.push_back(pl); break;
//					}
//					else  break;
//				}
//			}
//		}
//	}
//}

bool Grid::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x] == 0);
}

int Grid::getCellWeight(Vector2D cell)
{
	if (isValidCell(cell))
	{
		return terrain[(unsigned int)cell.y][(unsigned int)cell.x]; //retornem el numero de la cell asignat al maze
	}
}