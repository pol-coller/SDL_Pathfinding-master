#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <map>
#include <queue>

class Dijkstra :
	public Agent::Pathfinding
{
public:
	Dijkstra(Graph* graph, Agent* agent, Vector2D coinPos);
	~Dijkstra();
	void findPath(Graph* graph, Agent* agent, Vector2D coinPos);
};

//PASAT A AGENT.CPP
//struct compareWeight {
//    bool operator()(Node const& n1, Node const& n2)
//    {
//        return n1.costSoFar > n2.costSoFar;
//        //return n1.weight < n2.weight;
//    }
//};
