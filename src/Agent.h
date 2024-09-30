#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
//#include "Grid.h"
//#include "Graph.h"
#include "Blackboard.h"
#include "SensorySystem.h"
#include "Scene.h"

struct compareWeight {
	bool operator()(Node const& n1, Node const& n2)
	{
		return n1.costSoFar > n2.costSoFar;
		//return n1.weight < n2.weight;
	}
};

class Agent
{
public:
	enum class AgentType
	{
		PLAYER, ENEMY
	};
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};

	class Pathfinding
	{
	protected:
		Pathfinding() {};
		virtual ~Pathfinding() {};
		//virtual Vector2D findPath(Graph graph);
		virtual void findPath(Graph graph, Agent *agent) {};
		int frontierCount = 0;
	public:
		inline int getFrontierCount() const& { return frontierCount; };
	};

	class SensorySystem
	{
	public:
		SensorySystem() {};
		virtual ~SensorySystem() {};
		//virtual ~Pathfinding() {};
		virtual void update(/*Graph graph,*/ Agent* agent) {};
	protected:
		Scene *world;
		//inline int getFrontierCount() const& { return frontierCount; };
	//protected:
	};

	class DecisionMakingAlgorithm
	{
	public:
		DecisionMakingAlgorithm() {};
		virtual ~DecisionMakingAlgorithm() {};
		virtual void update(Agent* agent, float dtime) {};
	};

	SensorySystem *sensory_system; //private maybe?   Al diagrama de clase surt com public
private:
	AgentType type;
	Pathfinding *pathfinding;
	SteeringBehavior *steering_behaviour;
	Blackboard *blackboard;
	DecisionMakingAlgorithm* brain;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	bool haveWeapon;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;
	float maxTime;
	float currentTime;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	Agent(AgentType);
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPathBehavior(Pathfinding  *pathfind);
	void setSensorySystem(SensorySystem *_sensorySystem);
	void setBrain(DecisionMakingAlgorithm *_brain);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	inline void setMaxVelocity(float _max_Velocity) { max_velocity = _max_Velocity; };
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	void setHaveWeapon(bool weapon);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	inline float getOrientation() const& { return orientation; };
	inline float getHaveWeapon() const& { return haveWeapon; };
	inline Blackboard* getBlackboard() const& { return blackboard; };
};
