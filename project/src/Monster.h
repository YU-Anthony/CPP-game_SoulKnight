#pragma once
#include "DisplayableObject.h"
#include "Scyyz4Object.h"
#include "Stage.h"

class GamePlay;
class Scyyz4Object;

class Monster :
	public DisplayableObject
{
public:
	Monster(Scyyz4Engine* pEngine, Stage* stage, int xSize, int ySize, int worldXPos, int worldYPos,Scyyz4Object* player,std::string imageName);
	virtual ~Monster() 
	{
		//printf("monster release\n");
		//delete currMonster;
	};

	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void UndrawHUD();
	bool CanDraw(int x, int y, int w, int h);
	void randomMove(int& x, int& y,int& dir);
	virtual void PerformMovement();
	virtual void genMonster();
	virtual void drawHP();
	virtual void detectCollision();
	virtual int getXPosition();
	virtual int getYPosition();

	int mx_position;
	int my_position;

	virtual void findPlayer(int& x,int&y);
	bool moveUP(int x,int y);
	bool moveLEFT(int x, int y);

protected:
	bool drawHealth = false;
	Scyyz4TileManager* m_pTileManager;
	SimpleImage monster1;
	SimpleImage monster2;
	SimpleImage* currMonster;
	GamePlay* playStage;
	Scyyz4Object* player;
	int perceptionDistance = 5;
	int frame = 0;
	int frameWait = 50;
	int speed = 10;


private:
	int x_last = 0;
	int y_last = 0;
	int hOutlineX, hOutlineY, hOutlineW, hOutlineH;
	int healthX, healthY, healthW, healthH;
	unsigned int health = 100;
	int maxHealth;
	bool dead = false;
	int requiredPos=0;
	int lastChoice = 0, newChoice;

};


