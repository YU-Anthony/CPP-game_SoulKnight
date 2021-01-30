#pragma once
#include "Stage.h"
#include "SimpleImage.h"
#include "Scyyz4Object.h"
#include "Scyyz4TileManager.h"
#include "Weapon.h"
#include "FireBall.h"

class Scyyz4Engine;
class Scyyz4Object;
class Ally;
class RedMonster;
class HellMonster;
class BossMonster;
class Tool;

class GamePlay :
	public Stage
{
public:
	GamePlay(Scyyz4Engine* pEngine, bool load);
	~GamePlay();

	void virtSetupBackgroundBuffer();
	void virtDrawStringsOnTop();
	virtual void virtKeyDown(int iKeyCode);
	virtual void virtMouseDown(int button, int x, int y);
	int virtInitialiseObjects();
	//void virtMouseWheel(int x, int y, int which, int timestamp);
	//void storeWeapon(int weaponID);
	virtual void destoryObject(int objectID);
	void regenMonster(int index);
	void destroyTiles();
	int getTileValue(int x, int y);
	//void LevelUp();

	void lose();
	//void attackOn();

	void storeWeapon(int weaponID);
	void LevelSwitch();

	int getLevel() { return gameLevel; }
	void setLevel(int i) { gameLevel = i; }
	void saveGame();
	void loadGame();

	/*GamePlay&  operator--(int) {
		this->noOfMonsters--;
		return *this;
	}*/
	void killMonster() {
		if (noOfMonsters > 0) {
			printf("debug killmonster\n");
			noOfMonsters-=1;
		}
		else {
			noOfMonsters = 0;
		}
	}
	int returnMonsterNum() {
		return noOfMonsters;
	}


	void addAlly(Ally* ally) { snake.push_back(ally); }

	std::vector<Ally*> getSnake() { return snake; }

	Scyyz4TileManager* getTileManager() { return s_tiles; }

private:
	Scyyz4TileManager* s_tiles;
	Scyyz4Engine* m_engine;
	SimpleImage mainImage;
	Scyyz4Object* player;
	Ally* allyPlayer;
	RedMonster* monster1;
	RedMonster* monster2;
	HellMonster* hellmonster1;
	HellMonster* hellmonster2;
	HellMonster* hellmonster3;
	BossMonster* boss;

	Weapon* currWeapon;
	Weapon* arrow;
	FireBall* fireball;

	Tool* tool;
	int weaponID;

	bool load;
	bool startGame = false;
	int gameLevel = 1;

	int playerScore=0;
	int noOfMonsters=0;
	int xMax, xMin, yMax, yMin;
	bool playerAttack = false;

	std::vector<Ally*> snake;



};

