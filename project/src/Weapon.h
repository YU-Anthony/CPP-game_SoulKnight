#pragma once
#include "DisplayableObject.h"
#include <string>

class Scyyz4Object;
class GamePlay;

class Weapon :
	public DisplayableObject
{
public:
	Weapon(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path, Scyyz4Object* moveCharacter);
	//Weapon(Scyyz4Engine* pEngine);
	~Weapon() {
		//std::cout << "arrow release" << std::endl;
	};
	virtual void virtDraw() override;
	virtual void virtDoUpdate(int iCurrentTime) override;
	void detectCollision();
	void findObstacles();

	int getXPosition();
	int getYPosition();
	int xPosition = 0;
	int yPosition = 0;

private:
	int x_last = 0;
	int y_last = 0;

	int dX = 20;
	int dY = 20;

	int frame = 0;
	int speed = 100;

	std::string image;
	int dir = 0;

	SimpleImage r_image;




protected:
	Scyyz4TileManager* m_pTileManager;
	Scyyz4Object* moveCharacter;
	Stage* stage;
	GamePlay* gameStage;

	Scyyz4Engine* pEngine;
};

