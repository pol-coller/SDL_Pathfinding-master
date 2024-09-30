#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <map>
#include <queue>

class GreedyBestFirstSearch :
	public Agent::Pathfinding
{
public:
	GreedyBestFirstSearch(Graph* graph, Agent* agent, Vector2D coinPos);
	~GreedyBestFirstSearch();
	void findPath(Graph* graph, Agent* agent, Vector2D coinPos);
	int heuristicManhattan(Vector2D pos, Vector2D targetPos);
};


