#pragma once
//#include "SceneDecisions.h"
#include "Vector2D.h"
#include "Graph.h"

class Blackboard
{
private:
	Vector2D playerPos;
	//Vector2D enemyPos; Dada per si volem fer que es considerin obstacles entre ells i no colisionin.
	Grid* maze;
	Graph* graph;
	bool isPlayerVisible;
	bool playerHaveGun;

public:
	Blackboard();
	//Getters
	inline bool getIsPlayerVisible() const& { return isPlayerVisible; };
	inline bool getPlayerHaveGun() const& { return playerHaveGun; };
	inline Vector2D getPlayerPos() const& { return playerPos; };
	inline Grid* getMaze() const& { return maze; };
	inline Graph* getGraph() const& { return graph; };

	//Setters
	inline void setIsPlayerVisible(bool _isPlayerVisible) { isPlayerVisible = _isPlayerVisible; };
	inline void setPlayerHaveGun(bool _playerHaveGun) { playerHaveGun = _playerHaveGun; };
	inline void setPlayerPos(Vector2D _playerPos)  { playerPos = _playerPos; };
	inline void setMaze(Grid* _maze)  { maze = _maze; };
	inline void setGraph(Graph* _graph)  { graph = _graph; };
};

