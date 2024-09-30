#pragma once
//#include "Agent.h"
#include "FSM_State.h"
class FSM : 
	public Agent::DecisionMakingAlgorithm
{
public:
	FSM();
	FSM(Agent* agent);
	~FSM();
	void update(Agent* agent, float dtime);

private:
	FSM_State* currentState;
	void changeState(Agent* agent, FSM_State* newState);
	//bool initFlag;
};

