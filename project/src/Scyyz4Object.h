#pragma once
#include "DisplayableObject.h"
#include "GamePlay.h"

class GamePlay;


class Scyyz4Object :
	public DisplayableObject
{
public:
	Scyyz4Object(Scyyz4Engine* pEngine, GamePlay* stage, const char* image_path);
	~Scyyz4Object() 
	{	
		//printf("player release\n");
	};
	virtual void virtDraw() override;
	virtual void virtDoUpdate(int iCurrentTime) override;
	virtual int getXPosition() { return xPosition; }
	virtual int getYPosition() { return yPosition; }
	virtual int attDirection() { return att_direction; }
	int getHealth() { return health; }

	int getXLast() { return x_last; }
	int getYLast() { return y_last; }

	int getXTile(int x) {
		int iTileX = m_pTileManager->getMapXForScreenX(x);
		return iTileX;
	}
	int getYTile(int y) {
		int iTileY = m_pTileManager->getMapYForScreenY(y);
		return iTileY;
	}
	void findAlly(bool isFind) {
		isfindAlly = isFind;
	}

	void increaseScores(int score) { scores += score; }
	virtual void minusHP(int dHP) { health -= dHP; }
	int getScores() { return scores; }
	virtual void drawHP(int x, int y);
	void insideBoundary();
	void plusTreasure();
	int getTreasure();

	int xPosition=0;
	int yPosition=0;

	int getMoveDirection() { return move_direction; }

	void setMoveDirection(int i) { move_direction = i; }
	void setXPosition(int i) { m_iCurrentScreenX = i; }
	void setYPosition(int i) { m_iCurrentScreenY = i; }
	void setHealth(int i) { health = i; }
	void setScores(int i) { scores = i; }


	friend Scyyz4Object&  operator-(Scyyz4Object& so ,int n) {
		so.health -= n;
		return so;
	}

	bool isGameWin() {
		return isWin;
	}
	void gameWin() {
		isWin = true;
	}

private:
	int dX = 0;
	int dY = 0;

	int x_last=0;
	int y_last=0;
	int xSize, ySize;

	bool attack = false;
	bool animated = false;
	int frame = 0;
	int speed = 100;

	const char* image;
	int dir = 0;
	SimpleImage weapeon;
	SimpleImage HP;
	int att_direction = 0;

	bool isdoorOpen = false;
	bool isfindAlly = false;
	bool isWin = false;
	int weaponID = 1;
	int scores=0;

	unsigned int health=100;
	int hOutlineX, hOutlineY, hOutlineW, hOutlineH;
	int healthX, healthY, healthW, healthH;
	int maxHealth;

	int numOfTreausre=0;
	int levelCode = 0;
	int move_direction=0;

protected:
	Scyyz4TileManager* m_pTileManager;
	GamePlay* gameStage;
	Scyyz4Engine* p_mainEngine;
};

