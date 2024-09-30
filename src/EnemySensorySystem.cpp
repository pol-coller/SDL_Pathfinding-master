#include "EnemySensorySystem.h"
#include "utils.h"

using namespace Vector2DUtils;

EnemySensorySystem::EnemySensorySystem(Scene* _world) : maxSightDistance(11.0f), halfFOV(60.0f)
{
	world = _world;
}

EnemySensorySystem::~EnemySensorySystem() {}

void EnemySensorySystem::update(Agent* agent)
{
	bool canSeePlayer = false;
	Vector2D agentPosCell = pix2cell(agent->getPosition()); //Pasem a celes
	Vector2D playerPosCell = pix2cell(world->getCharacterPos()); //Pasem a celes
	//Comrpovem si player dintre de max distancia//
	int dist = (int)Vector2D::Distance(agentPosCell, playerPosCell);
	//std::cout << "DistPosTarget:  X = " << world->getCharacterPos().x << "  Y= " << world->getCharacterPos().y <<  std::endl;

	if (dist <= maxSightDistance) { canSeePlayer = true; /*std::cout << "InRange! dist:  " << dist << std::endl;*/}
	else 
	{ 
		//std::cout << "CellPosTarget:  X = " << world->getCharacterPos().x << "  Y= " << world->getCharacterPos().y << std::endl;
		//std::cout << "CellPosAgent:  X = " << agentPosCell.x << "  Y= " << agentPosCell.y << std::endl;
		/*Escrivim FALSE a la blackboard!*/ 
		agent->getBlackboard()->setIsPlayerVisible(false);
		return; 
	}

	//Comprovem si esta dintre del FOV//
	Vector2D coneBase;
	coneBase.x = agentPosCell.x + maxSightDistance * cos(agent->getOrientation() * DEG2RAD);
	coneBase.y = agentPosCell.y + maxSightDistance * sin(agent->getOrientation() * DEG2RAD);
	if (Vector2DUtils::IsInsideCone(playerPosCell, agentPosCell, coneBase, halfFOV))	{/*std::cout << "InsideCone" << std::endl;*/}
	else 
	{
		//std::cout << "outsideCone" << std::endl;		
		agent->getBlackboard()->setIsPlayerVisible(false); /*Escrivim FALSE a la blackboard!*/
		return;
	}
	//Comprovem si tenim linea de visio//
	std::vector<Grid::pointsLine> walls = agent->getBlackboard()->getMaze()->getWalls();
	for (int i = 0; i < walls.size(); i++)
	{
		bool intersection = SegmentSegmentIntersection(agentPosCell, playerPosCell, walls[i].initPoint, walls[i].endPoint);
		if (intersection)
		{
			agent->getBlackboard()->setIsPlayerVisible(false); /*Escrivim FALSE a la blackboard!*/
			return;
		}
	}
	//canSeePlayer = SegmentSegmentIntersection(); //Es la funcio que posa en el pdf de la practica, no se com funciona s'ha de mirar
	//if (Vector2DUtils::SegmentSegmentIntersection()){}
	//	//Escrivim a la blackboard TRUE
		agent->getBlackboard()->setIsPlayerVisible(true);
		agent->getBlackboard()->setPlayerPos(world->getCharacterPos()/*agent->getPosition()*/);
		agent->getBlackboard()->setPlayerHaveGun(world->getPlayerHaveWeapon()/*agent->getPosition()*/);
		
	//else{}
	//   /*Escrivim FALSE a la blackboard!*/

	//std::cout << "UpdateAgentSensorSystem: " << world->getTitle() << std::endl;
}

//Vector2D EnemySensorySystem::cell2pix(Vector2D cell) 
//{
//	int offset = CELL_SIZE / 2;
//	return Vector2D(cell.x * CELL_SIZE + offset, cell.y * CELL_SIZE + offset);
//}
//
//Vector2D EnemySensorySystem::pix2cell(Vector2D pix)
//{
//	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
//}
