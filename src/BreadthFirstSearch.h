#pragma once
//#include "Path"
#include "Agent.h"
#include "Vector2D.h"
#include <map>
class BreadthFirstSearch : 
	public Agent::Pathfinding
{
public:
	BreadthFirstSearch(Graph* graph,Agent* agent, Vector2D coinPos);
	~BreadthFirstSearch();
	void findPath(Graph* graph,Agent* agent, Vector2D coinPos);

};

