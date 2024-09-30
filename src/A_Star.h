#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <map>
#include <queue>

class A_Star :
	public Agent::Pathfinding
{
public:
	A_Star(Graph* graph, Agent* agent, Vector2D coinPos);
	~A_Star();
	void findPath(Graph* graph, Agent* agent, Vector2D coinPos);
	int heuristicManhattan(Vector2D pos, Vector2D targetPos);
};
