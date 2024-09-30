#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Player.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "A_Star.h"
#include "EnemySensorySystem.h"
#include "FSM.h"
//#include "Player.h"
class SceneDecisions : public Scene
{
public:
	SceneDecisions();
	~SceneDecisions();
	void update(float dtime, SDL_Event* event);
	void draw();

	//GETTERS
	const char* getTitle();
	const Vector2D getCharacterPos();
	const bool getPlayerHaveWeapon();

private:
	std::vector<Agent*> agents;
	Agent* player;
	Vector2D coinPosition;

	Grid* maze;
	Graph* graph;
	bool draw_grid;

	void drawMaze();
	void drawCoin();
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);
};

