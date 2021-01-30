#pragma once
#include "Monster.h"
#include "Scyyz4Object.h"

class BossMonster :
	public Monster
{
public:
	BossMonster(Scyyz4Engine* pEngine, Stage* stage, int indexInArray, int xSize, int ySize, int worldXPos, int worldYPos, Scyyz4Object* player, std::string imageName);
	~BossMonster() 
	{
		//printf("bossmonster release\n");
	}

	virtual void genMonster();
	virtual void PerformMovement();
	virtual void drawHP();
	virtual void minusHP();

	void detectCollision();

	virtual int getXPosition();
	virtual int getYPosition();

	void insideBoundary();

private:
	Scyyz4Engine* m_pMainEngine;
	Scyyz4Object* player;
	Scyyz4TileManager* myTm;
	Stage* stage;
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


