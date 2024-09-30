#include "ChaseState.h"
#include "PatrolState.h"
#include "FleeState.h"
void ChaseState::enter(Agent* agent)
{
	agent->setMaxVelocity(180); //Fem que persegueixi mes rapid

	maze = agent->getBlackboard()->getMaze();
	graph = agent->getBlackboard()->getGraph();
	playerPosition = agent->getBlackboard()->getPlayerPos(); //posicio en pixels

	Vector2D posToCells = pix2cell(agent->getPosition());
	agent->setPosition(cell2pix(posToCells));

	Vector2D playerPosToCells = pix2cell(playerPosition);

	//std::cout << "DistPosTarget:  X = " << playerPosition.x << "  Y= " << playerPosition.y <<  std::endl;

	//playerPosition = cell2pix(playerPosToCells);
	std::cout << "playerPositionCell:  X = " << playerPosToCells.x << "  Y= " << playerPosToCells.y << std::endl;
	std::cout << "AgentPositionCell:  X = " << posToCells.x << "  Y= " << posToCells.y << std::endl;
	agent->setTarget(playerPosToCells);

	agent->setPathBehavior(new A_Star(graph, agent, maze->cell2pix(playerPosToCells)));
}

FSM_State* ChaseState::update(Agent* agent, float dtime)
{
	currentTime += dtime;
	//std::cout << "currentTime: "<< currentTime << std::endl;

	bool isPlayerVisible = agent->getBlackboard()->getIsPlayerVisible();
	bool haveGun = agent->getBlackboard()->getPlayerHaveGun();

	//Per sortir fem que vagi a ultima pos on a vist a Player per ferho mes realista 
	if (!isPlayerVisible && agent->getCurrentTargetIndex() == -1 && currentTime >= maxTime)
	{
		return new PatrolState();
	}
	else if (isPlayerVisible && haveGun) return new FleeState;

	//else
	//{
		//std::cout << "Player Visible desde ChaseState : " << isPlayerVisible << std::endl;

		if ((/*agent->getCurrentTargetIndex() == -1 &&*/ currentTime >= maxTime)/* && (maze->pix2cell(agent->getPosition()) == playerPosition)*/)
		{
			currentTime = 0;
			agent->clearPath();

			Vector2D posToCells = pix2cell(agent->getPosition());
			agent->setPosition(cell2pix(posToCells));

			playerPosition = agent->getBlackboard()->getPlayerPos();
			Vector2D playerPosToCells = pix2cell(playerPosition);
			//playerPosition = cell2pix(playerPosToCells);
			agent->setTarget(playerPosToCells);
			//std::cout << "playerPositionCell:  X = " << playerPosToCells.x << "  Y= " << playerPosToCells.y << std::endl;

			//Vector2D posToCells = pix2cell(agent->getPosition());
			//agent->setPosition(cell2pix(posToCells));
			//agent->setPosition(maze->cell2pix(playerPosition));
			//std::cout << "PatrolInitPos:  X = " << agent->getPosition().x << "  Y= " << agent->getPosition().y << std::endl;
			agent->setPathBehavior(new A_Star(graph, agent, maze->cell2pix(playerPosToCells)));

		}
	//}
		return nullptr;
}

void ChaseState::exit(Agent* agent)
{
	agent->clearPath();
}
