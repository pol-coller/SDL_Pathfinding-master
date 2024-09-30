#include "SceneDecisions.h"

using namespace std;

SceneDecisions::SceneDecisions()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");
	int temp = 0;

	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				temp++;
			}
		}
	}
	graph = new Graph(temp, maze);

	loadTextures("../res/maze.png", "../res/coin.png");

	//srand((unsigned int)time(NULL));	/////////////////////////////////////

	Agent* agent = new Agent(Agent::AgentType::ENEMY);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agent->setBehavior(new PathFollowing);
	agent->setSensorySystem(new EnemySensorySystem(this)); //Pasem * de l'scene
	agent->getBlackboard()->setMaze(maze);
	agent->getBlackboard()->setGraph(graph);
	//agent->setBrain(new FSM()); //init amb flag per no necesitar agent al constructor
	agent->setBrain(new FSM(agent)); //Amb agent al construct
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);
	agent = new Agent(Agent::AgentType::ENEMY);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agent->setBehavior(new PathFollowing);
	agent->setSensorySystem(new EnemySensorySystem(this)); //Pasem * de l'scene
	agent->getBlackboard()->setMaze(maze);
	agent->getBlackboard()->setGraph(graph);
	//agent->setBrain(new FSM()); //init amb flag per no necesitar agent al constructor
	agent->setBrain(new FSM(agent)); //Amb agent al construct
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);
	player = new Agent(Agent::AgentType::PLAYER);
	player->loadSpriteTexture("../res/soldier.png", 4);
	player->setBehavior(new PathFollowing);
	player->setTarget(Vector2D(-20, -20));
	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	//agents[0]->setPosition(maze->cell2pix(rand_cell));
	//player->setPosition(maze->cell2pix(rand_cell));
	player->setPosition(maze->cell2pix(Vector2D(38, 22)));
	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	//agents[0]->setTarget(coinPosition);
	//agents[0]->setPathBehavior(new A_Star(graph, agents[0], maze->cell2pix(coinPosition)));
}

SceneDecisions::~SceneDecisions()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneDecisions::update(float dtime, SDL_Event* event)
{

	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) 
			{
				player->clearPath(); //netejem cami per construir un de nou
				
				Vector2D tempCellPos = pix2cell(player->getPosition());//pasem pos player a celes.
				player->setPosition(maze->cell2pix(tempCellPos)); //de celes pasem a pixels per aconseguir numero sense decimals, sino algoh de pathfollow no funciona
				
				player->setPathBehavior(new A_Star(graph, player, maze->cell2pix(cell)));

				//std::cout << "Player:  X = " << player->getPosition().x << "  Y= " << player->getPosition().y << std::endl;
				//std::cout << "Cell:  X = " << cell.x << "  Y= " << cell.y << std::endl;
			}
		}
		break;
	default:
		break;
	}

	player->update(dtime,event);
	for(int i = 0;i<agents.size();i++)
	agents[i]->update(dtime, event);

	if ((player->getCurrentTargetIndex() == -1)) {
		Vector2D tempCellPos = pix2cell(player->getPosition());
		player->setPosition(maze->cell2pix(tempCellPos));		
		//Vector2D posToInt = ((int)player->getPosition().x, (int)player->getPosition().y);	//Sempre retorna 0!
		//player->setPosition(posToInt);
	}

	if (/*(agents[0]->getCurrentTargetIndex() == -1) && */(maze->pix2cell(player->getPosition()) == coinPosition))
	{
		player->setHaveWeapon(true);
		//agents[0]->setPosition(maze->cell2pix(coinPosition));
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition))/* || (Vector2D::Distance(coinPosition, maze->pix2cell(agents[0]->getPosition())) < 3)*/)
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		
	}
	
}

void SceneDecisions::draw()
{
	drawMaze();
	drawCoin();

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}
	for (int i = 0; i < agents.size(); i++)
	agents[i]->draw();
	player->draw();
}

const char* SceneDecisions::getTitle()
{
	return "SDL Path Finding :: A*";
}

const Vector2D SceneDecisions::getCharacterPos()
{
	return player->getPosition();
}

const bool SceneDecisions::getPlayerHaveWeapon()
{
	return player->getHaveWeapon();//player->getWeapon();
}

//Agent* SceneDecisions::getPlayer()
//{
//	return player;
//}

void SceneDecisions::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else if (maze->getCellWeight(Vector2D((float)i, (float)j)) == 2)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 127, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else if (maze->getCellWeight(Vector2D((float)i, (float)j)) == 3)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 0, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else if (maze->getCellWeight(Vector2D((float)i, (float)j)) == 5)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 50, 205, 50, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else if (maze->getCellWeight(Vector2D((float)i, (float)j)) == 10)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 107, 142, 35, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else if (maze->getCellWeight(Vector2D((float)i, (float)j)) == 20)
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 85, 107, 47, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else {
				// Do not draw if it is not necessary (bg is already black)
			}


		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneDecisions::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool SceneDecisions::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}
