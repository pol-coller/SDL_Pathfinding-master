#include "PatrolState.h"
#include "ChaseState.h"
void PatrolState::enter(Agent* agent)
{
	agent->setMaxVelocity(110);

	maze = agent->getBlackboard()->getMaze();
	graph = agent->getBlackboard()->getGraph();

	//pos sense decimals//
	Vector2D posToCells = pix2cell(agent->getPosition());
	agent->setPosition(cell2pix(posToCells));

	while ((!maze->isValidCell(patrolPosition)) /*|| (Vector2D::Distance(patrolPosition, rand_cell) < 3)*/)
		patrolPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	agent->setTarget(patrolPosition); //En CellPosition!
	//std::cout << "PatrolInitPos:  X = " << patrolPosition.x << "  Y= " << patrolPosition.y << std::endl;
	//std::cout << "AgentInitPos:  X = " << agent->getPosition().x << "  Y= " << agent->getPosition().y << std::endl;
	agent->setPathBehavior(new A_Star(graph, agent, maze->cell2pix(patrolPosition)));

}

FSM_State* PatrolState::update(Agent* agent, float dtime)
{
	//Comprobar isPlayerVisible() de Blackboard a traves de getter.
	//Si visible retornem directament punter a ChaseState;
	bool isPlayerVisible = agent->getBlackboard()->getIsPlayerVisible();
	if (isPlayerVisible) 
	{ 
		return new ChaseState(); 
	}
	//else{
	
		//std::cout << "Player Visible desde PatrolState : " << isPlayerVisible << std::endl;

	//Si no visible actu logica del patrol i return nullptr;
	if ((agent->getCurrentTargetIndex() == -1) && (maze->pix2cell(agent->getPosition()) == patrolPosition))
	{
		agent->setPosition(maze->cell2pix(patrolPosition));
		//patrolPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(patrolPosition)) || (Vector2D::Distance(patrolPosition, maze->pix2cell(agent->getPosition())) < 3))
			patrolPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		agent->setPathBehavior(new A_Star(graph, agent, maze->cell2pix(patrolPosition)));
		
	}
	//}
	//LLOGICA DEL PATROL//
	return nullptr;
}

void PatrolState::exit(Agent* agent)
{
	agent->clearPath();
	//agent->setVelocity(agent->getVelocity() * 2);
	//agent->clearPath() etc...
}
