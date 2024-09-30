#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"
#include "GreedyBestFirstSearch.h"

class ScenePathFindingGreedyBFS :
	public Scene
{
public:
	ScenePathFindingGreedyBFS();
	~ScenePathFindingGreedyBFS();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
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

