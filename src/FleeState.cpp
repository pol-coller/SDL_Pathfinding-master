#include "FleeState.h"
#include "ChaseState.h"
#include "PatrolState.h"

void FleeState::enter(Agent* agent)
{
	agent->setMaxVelocity(180);

	maze = agent->getBlackboard()->getMaze();
	graph = agent->getBlackboard()->getGraph();
	playerPosition = agent->getBlackboard()->getPlayerPos(); //posicio en pixels

	Vector2D posToCells = pix2cell(agent->getPosition());

	//1-1(adalat esquerra), 38-1 (adlat dreta) , 1-22 (baix esquerra , 38-22 (abaix dreta)
	float minDist = 1000.f;
	float distTemp = 0.f;
	Vector2D posTemp(0,0);
	Vector2D cellPosToGo(1,1);

	//posTemp = Vector2D(1, 1) - agent->getPosition();
	minDist = distTemp = posTemp.Distance(Vector2D(1, 1), posToCells);

	distTemp = posTemp.Distance(Vector2D(38, 1), posToCells);
	if (distTemp < minDist) { minDist = distTemp; cellPosToGo = Vector2D(38, 1); }

	distTemp = posTemp.Distance(Vector2D(1, 22), posToCells);
	if (distTemp < minDist) { minDist = distTemp; cellPosToGo = Vector2D(1, 22); }

	distTemp = posTemp.Distance(Vector2D(38, 22), posToCells);
	if (distTemp < minDist) { cellPosToGo = Vector2D(38, 22); }

	agent->setPosition(cell2pix(posToCells));

	//Vector2D playerPosToCells = pix2cell(playerPosition);


	//playerPosition = cell2pix(playerPosToCells);
	agent->setTarget(cellPosToGo);

	agent->setPathBehavior(new A_Star(graph, agent, maze->cell2pix(cellPosToGo)));
	//std::cout << "playerPositionCell:  X = " << playerPosToCells.x << "  Y= " << playerPosToCells.y << std::endl;
	//std::cout << "AgentPositionCell:  X = " << posToCells.x << "  Y= " << posToCells.y << std::endl;
	//std::cout << "DistPosTarget:  X = " << playerPosition.x << "  Y= " << playerPosition.y <<  std::endl;
}

FSM_State* FleeState::update(Agent* agent, float dtime)
{
	bool isPlayerVisible = agent->getBlackboard()->getIsPlayerVisible();
	bool haveGun = agent->getBlackboard()->getPlayerHaveGun();

	//Aixo no funcionara perque el con de visio esta devant agent, fer un derrere? com o plantejem?
	if (!isPlayerVisible && agent->getCurrentTargetIndex() == -1 /*&& currentTime >= maxTime*/)
	{
		return new PatrolState();
	}
	else if (!haveGun && isPlayerVisible && agent->getCurrentTargetIndex() == -1) return new ChaseState;




	return nullptr;
}

void FleeState::exit(Agent* agent)
{
	agent->clearPath();
}
