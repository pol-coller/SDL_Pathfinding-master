#pragma once
#include "Agent.h"
class Player
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Player* agent, float dtime) {};
	};

	class Pathfinding
	{
	protected:
		Pathfinding() {};
		virtual ~Pathfinding() {};
		//virtual Vector2D findPath(Graph graph);
		virtual void findPath(Graph graph, Player* agent) {};
		int frontierCount = 0;
	public:
		inline int getFrontierCount() const& { return frontierCount; };
	};
private:
	Pathfinding* pathfinding;
	SteeringBehavior* steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture* sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Player();
	~Player();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior* behavior);
	void setPathBehavior(Pathfinding* pathfind);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event* event);
	void draw();
	bool Player::loadSpriteTexture(char* filename, int num_frames = 1);
	inline float getOrientation() const& { return orientation; };
};

