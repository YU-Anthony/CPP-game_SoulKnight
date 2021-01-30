#pragma once
#include "Monster.h"
#include "Scyyz4Object.h"


class RedMonster :
	public Monster
{
public: 
	RedMonster(Scyyz4Engine* pEngine, Stage* stage, int indexInArray, int xSize, int ySize, int worldXPos, int worldYPos, Scyyz4Object* player,std::string imageName);
	~RedMonster() 
	{
		//printf("redmonster delete\n");
	}

	virtual void genMonster();
	virtual void PerformMovement();
	virtual void drawHP();
	virtual void minusHP() { health -= 20; }

	void detectCollision();

	virtual int getXPosition() { return mx_position; }
	virtual int getYPosition() {return my_position;}
	int getHealth() { return health; }
	

	void setXPosition(int i) { mx_position = i; }
	void setYPosition(int i) { my_position = i; }
	void setHealth(int i) { health = i; }

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


