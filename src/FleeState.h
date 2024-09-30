#pragma once
#include "FSM_State.h"
#include "A_Star.h"

class FleeState :
	public FSM_State
{
public:
	// Heredado vía FSM_State
	void enter(Agent* agent);
	FSM_State* update(Agent* agent, float dtime);
	void exit(Agent* agent);

private:
	Grid* maze;
	Graph* graph;
	Vector2D playerPosition;

};

