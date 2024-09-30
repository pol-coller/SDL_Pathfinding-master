#include "FSM.h"
#include "PatrolState.h"
FSM::FSM()// : initFlag(true)
{
	currentState = new PatrolState();
	//currentState->enter();
}

FSM::FSM(Agent* agent)// : initFlag(true)
{
	currentState = new PatrolState();
	currentState->enter(agent);
}

FSM::~FSM()
{
}

void FSM::update(Agent* agent, float dtime)
{
	//if (initFlag)
	//{
	//	currentState->enter(agent);
	//	initFlag = false;
	//}

	FSM_State* newState = currentState->update(agent, dtime);
	if (newState != nullptr) changeState(agent, newState);
}

void FSM::changeState(Agent* agent, FSM_State* newState)
{
	currentState->exit(agent); 
	currentState = newState;
	currentState->enter(agent); 
}
