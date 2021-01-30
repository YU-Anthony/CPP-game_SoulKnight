#pragma once
#include "DisplayableObject.h"
#include <string>
#include "GamePlay.h"
#include "RedMonster.h"

using namespace std;
class GamePlay;



class Ally :
	public  DisplayableObject
{
public:
	Ally(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path,Scyyz4Object* player);
	//Ally(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path, Ally* player,bool isHead);
	~Ally();
	virtual void virtDraw();
	virtual void virtDoUpdate(int iCurrentTime);
	virtual int getXPosition() { return xPosition; }
	virtual int getYPosition() { return yPosition; }
	virtual int attDirection() { return att_direction; }
	void setXPosition(int x) { xPosition = x; }
	void setYPosition(int y) { yPosition = y; }
	int getXLast() { return x_last; }
	int getYLast() { return y_last; }
	//void increaseScores(int score);
	virtual void drawHP(int x, int y);
	virtual void minusHP(int dHP) { health -= dHP; }

	void detectCollision();
	void attackMonster();

	int getHealth() { return health; }
	void setHealth(int i) { health = i; }

	int getMoveDirection();
	void controlMovement(Scyyz4Object* player);
	void controlMovement(Ally* player);

	int xPosition = 100;
	int yPosition = 100;

private:
	int allyID;
	bool isHead;
	bool detected;
	bool addition = true;
	int move_direction;

	int dX = 0;
	int dY = 0;
	int x_last = 0;
	int y_last = 0;
	int xSize, ySize;

	bool attack = false;
	bool animated = false;
	int frame = 0;
	int speed = 100;

	std::string image;
	int dir = 0;
	SimpleImage weapeon;
	SimpleImage HP;
	int att_direction = 0;

	int weaponID = 1;

	unsigned int health ;
	int hOutlineX, hOutlineY, hOutlineW, hOutlineH;
	int healthX, healthY, healthW, healthH;
	int maxHealth;

	std::vector<Ally*> tempsnake;
	bool hasAdded = false;

protected:
	Scyyz4TileManager* m_pTileManager;
	GamePlay* gameStage;
	Scyyz4Engine* p_mainEngine;
	Scyyz4Object* object;

};

