#pragma once
#include "Weapon.h"
#include <string>

class GamePlay;

class FireBall :
	public Weapon
{
public:
	FireBall(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path, Scyyz4Object* moveCharacter);
	~FireBall()
	{ 
		//printf("fireball release\n");
		//delete m_pTileManager; 
		//delete moveCharacter;
	}
	virtual void virtDraw() override;
	virtual void virtDoUpdate(int iCurrentTime) override;
	void detectCollision();
	void findObstacles();


private:
	std::string image;
	int dir = 1;

	int dX = 20;
	int dY = 20;

protected:
	Scyyz4TileManager* m_pTileManager;
	GamePlay* gameStage;
	Scyyz4Object* moveCharacter;
};

