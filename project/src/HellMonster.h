#pragma once
#include "Monster.h"
#include "Scyyz4Object.h"

class HellMonster :
	public Monster
{
public:
	HellMonster(Scyyz4Engine* pEngine, Stage* stage, int indexInArray, int xSize, int ySize, int worldXPos, int worldYPos, Scyyz4Object* player, std::string imageName);
	~HellMonster() 
	{
		//printf("hellmonster release\n");
	};

	virtual void genMonster();
	virtual void PerformMovement();
	virtual void drawHP();
	virtual void minusHP() { health -= 10; }

	void detectCollision();

	int getHealth() { return health; }
	virtual int getXPosition() { return mx_position; }
	virtual int getYPosition() { return my_position; }

	void setHealth(int i) { health = i; }
	void setXPosition(int i) { mx_position = i; }
	void setYPosition(int i) { my_position = i; }

	void insideBoundary();

private:
	Scyyz4Engine* m_pMainEngine;
	Scyyz4Object* player;
	Scyyz4TileManager* myTm;
	std::string image_path;
	GamePlay* gameStage;
	int index;

	unsigned int health = 100;
	int hOutlineX, hOutlineY, hOutlineW, hOutlineH;
	int healthX, healthY, healthW, healthH;
	int maxHealth;

	int px_position;
	int py_position;
	int mx_position;
	int my_position;

	int xSize, ySize;
	int dX = 1;
	int dY = 1;
	int dir = 1;

};


