#pragma once
#include <iostream>
#include <SDL.h>
#include "Vector2D.h"


class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const Vector2D getCharacterPos() { return Vector2D(1, 1); };	
	virtual const bool getPlayerHaveWeapon() { return false; };
	//virtual Agent* getPlayer() { return new Agent(); };
	virtual const char* getTitle() { return ""; };
};

