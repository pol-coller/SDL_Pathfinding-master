#include "Graph.h"

Graph::Graph(int V, Grid* _grid)
{
	numNodes = V;
	//adjLists = std::vector<Node>[numNodes];
	//adjLists=std::vector<Node>(numNodes);
	initGraph(_grid);
}



void Graph::initGraph(Grid* _grid)
{
	int idCnt = 0; 
	Vector2D coords;

	for (int j = 0; j < _grid->getNumCellY(); j++)
	{
		for (int i = 0; i < _grid->getNumCellX(); i++)
		{
			if (_grid->isValidCell(Vector2D((float)i, (float)j)))
			{	
				Node node;
				Node temp;
				node.coord2 = Vector2D((float)i, (float)j);
				node.weight = _grid->getCellWeight(Vector2D((float)i, (float)j)); 
				node.coord = _grid->cell2pix(Vector2D((float)i, (float)j));
				node.id = idCnt;

				if (_grid->isValidCell(Vector2D((float)i + 1, (float)j)))
				{
					temp.id = idCnt + 1;
					temp.coord = _grid->cell2pix(Vector2D((float)i + 1, (float)j));
					temp.weight = _grid->getCellWeight(Vector2D((float)i+1, (float)j));

					node.coord2 = Vector2D((float)i+1, (float)j);
					node.neighbours.push_back(temp);
				}

				if (_grid->isValidCell(Vector2D((float)i - 1, (float)j)))
				{
					temp.id = idCnt - 1;
					temp.coord = _grid->cell2pix(Vector2D((float)i - 1, (float)j)); 

					node.coord2 = Vector2D((float)i-1, (float)j);
					temp.weight = _grid->getCellWeight(Vector2D((float)i - 1, (float)j));
					node.neighbours.push_back(temp);
				}

				if (_grid->isValidCell(Vector2D((float)i, (float)j + 1)))
				{
					int counter = 0;
					for (int k = i; k < 40; k++)
					{
						if (_grid->isValidCell(Vector2D((float)k, (float)j)))
						{
							counter++;
						}
					}
					for (int k = 0; k < i; k++)
					{
						if (_grid->isValidCell(Vector2D((float)k, (float)j + 1)))
						{
							counter++;
						}
					}
					temp.id = idCnt + counter;

					node.coord2 = Vector2D((float)i, (float)j+1);
					temp.weight = _grid->getCellWeight(Vector2D((float)i, (float)j+1));
					temp.coord = _grid->cell2pix(Vector2D((float)i, (float)j + 1));
					node.neighbours.push_back(temp);
				}

				if (_grid->isValidCell(Vector2D((float)i, (float)j - 1)))
				{
					int counter = 0;
					for (int k = i; k > 0; k--)
					{
						if (_grid->isValidCell(Vector2D((float)k, (float)j)))
						{
							counter++;
						}
					}
					for (int k = 40; k > i; k--)
					{
						if (_grid->isValidCell(Vector2D((float)k, (float)j-1)))
						{
							counter++;
						}
					}
					temp.id = idCnt - counter;

					node.coord2 = Vector2D((float)i, (float)j-1);
					temp.weight = _grid->getCellWeight(Vector2D((float)i, (float)j-1));
					temp.coord = _grid->cell2pix(Vector2D((float)i, (float)j - 1));

					//temp.coord = _grid->cell2pix(Vector2D((float)i, (float)j - j));
					node.neighbours.push_back(temp);
				}
				adjLists.push_back(node);
				idCnt++;
			}
		}
	}
}
