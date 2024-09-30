#include <list>
#include "Grid.h"
//struct Coord
//{
//	int x;
//	int y;
//};

	struct Node
	{
		std::vector<Node> neighbours;
		int id;
		Vector2D coord;
		Vector2D coord2;
		int weight;
		float costSoFar = 0;
	};
	class Graph {


		int numNodes;
		//std::list<Node>* adjLists;
		//std::list<Node> _adjLists;
		std::vector<Node> adjLists;
	public:
		Graph(int V, Grid* _grid);

		void initGraph(Grid* _grid);
		inline int getnumNodes() const & { return numNodes; };
		inline std::vector<Node> getAdjList() const& { return adjLists; };
	};

