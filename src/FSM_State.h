#pragma once
#include "Agent.h"
class FSM_State
{
public:
	virtual void enter(Agent *agent) = 0;
	virtual FSM_State* update(Agent* agent, float dtime) = 0;
	virtual void exit(Agent* agent) = 0;
};

