#pragma once
#include "Agent.h"

class EnemySensorySystem :
	public Agent::SensorySystem
{
public:
	EnemySensorySystem(Scene* world);
	~EnemySensorySystem();

	void update(Agent *agent);

private:
	float maxSightDistance;
	float halfFOV;
	//Vector2D cell2pix(Vector2D cell); //Pasat a utils.h/cpp
	//Vector2D pix2cell(Vector2D pix);
};

