#include "header.h"
#include "GamePlay.h"
#include "Scyyz4Engine.h"
#include "DrawingSurface.h"
#include "Scyyz4Object.h"
#include "RedMonster.h"
#include "HellMonster.h"
#include "BossMonster.h"
#include "Ally.h"
#include <fstream>
#include <iostream>
#include <map>
#include "Audio.h"



using namespace std;

map <int, string, less<int>> highscores;
int finalTime = 0;
bool isNewRecord = false;


GamePlay::GamePlay(Scyyz4Engine* pEngine, bool load)
	:Stage(pEngine)
	,m_engine(pEngine)
	,load(load)
{
	//printf("()play generate\n");
	//Audio::stopBgm();
	s_tiles = new Scyyz4TileManager();
	xMax = mapWidth - 1;
	xMin = 1;
	yMax = mapHeight - 1;
	yMin = 1;

}

GamePlay::~GamePlay()
{
	printf(")(play release\n");
	//delete player;
	//delete allyPlayer;
	//if (gameLevel > 1) {
	//	delete monster1;
	//	delete monster2;
	//}
	if (gameLevel >= 1 && startGame==true) {
		delete arrow;
		delete fireball;
	}

	/*if (gameLevel >=2)
	{
		delete hellmonster1;
		delete hellmonster2;
		delete hellmonster3;
	}*/
	//delete fireball;

	delete s_tiles;
}

void GamePlay::virtSetupBackgroundBuffer()
{
	Audio::playBgm(gameLevel);
	startGame = true;
	printf("GamePlay:Setup\n");
	m_engine->fillBackground(0x000000);
	virtInitialiseObjects();
	//m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	if (load)
		loadGame();

	if (gameLevel == 1) {
		LoadMapData("resources/map.txt");
	}
	else if (gameLevel == 2) {
		LoadMapData("resources/map2.txt");
	}
	else if (gameLevel == 3) {
		LoadMapData("resources/map3.txt");	
	}

	UpdateCurrentView();

	{



		// Set up the tiles
		int xSize = this->GetScreenTileWidth();
		int ySize = this->GetScreenTileHeight();

		std::vector<std::string> data = this->GetCurrentView();
		s_tiles->setMapSize(xSize, ySize);

		for (int x = 0; x < xSize; x++)
			for (int y = 0; y < ySize; y++)
				s_tiles->setMapValue(x, y, data[y].at(x) - 'a');

	
			// Specify the screen x,y of top left corner
		s_tiles->setTopLeftPositionOnScreen(0, 0);


		s_tiles->drawAllTiles(m_engine, m_engine->getBackgroundSurface());
	}

	m_engine->lockBackgroundForDrawing();
	SimpleImage bar = ImageManager::loadImage("images/bar.png",true);
	bar.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 0, m_engine->getWindowHeight()-51, bar.getWidth(), bar.getHeight());

	SimpleImage pauseButton = ImageManager::loadImage("images/restartButton.png",true).resizeTo(40,40);
	pauseButton.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 1080, 750, pauseButton.getWidth(), pauseButton.getHeight());

	SimpleImage restartButton = ImageManager::loadImage("images/pauseButton.png", true).resizeTo(40, 40);
	restartButton.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 1130, 750, restartButton.getWidth(), restartButton.getHeight());

	if (gameLevel <= 1) {
		SimpleImage save = ImageManager::loadImage("images/saveButton.png", true).resizeTo(45, 45);
		save.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 1180, 750, save.getWidth(), save.getHeight());
	}

	SimpleImage exitButton = ImageManager::loadImage("images/exitButton.png", true).resizeTo(40, 40);
	exitButton.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 1230, 750, exitButton.getWidth(), exitButton.getHeight());
	m_engine->unlockBackgroundForDrawing();

	m_engine->lockForegroundForDrawing();
	
	m_engine->unlockForegroundForDrawing();
	/*SimpleImage statue1 = ImageManager::loadImage("images/statue_angel.png");
	SimpleImage statue2 = ImageManager::loadImage("images/statue_centaur.png");
	SimpleImage golden_statue1 = ImageManager::loadImage("images/golden_statue_1.png");
	SimpleImage golden_statue2 = ImageManager::loadImage("images/golden_statue_2.png");
	SimpleImage statue3 = ImageManager::loadImage("images/statue_sigmund.png");
	SimpleImage statue4 = ImageManager::loadImage("images/statue_archer.png");
	SimpleImage tree = ImageManager::loadImage("images/tree.png");

	statue1.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth()/2-160, m_engine->getWindowHeight() / 2 +30, statue1.getWidth(), statue1.getHeight());
	statue2.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth() / 2 - 160, m_engine->getWindowHeight() / 2 -120, statue1.getWidth(), statue1.getHeight());
	statue3.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth() / 2 +140, m_engine->getWindowHeight() / 2 +30, statue1.getWidth(), statue1.getHeight());
	statue4.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth() / 2 + 140, m_engine->getWindowHeight() / 2 -120, statue1.getWidth(), statue1.getHeight());
	
	golden_statue1.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth() / 2 +50, m_engine->getWindowHeight() / 2 -45, golden_statue1.getWidth(), golden_statue1.getHeight());
	golden_statue2.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, m_engine->getWindowWidth() / 2 - 70, m_engine->getWindowHeight() / 2 - 45, golden_statue1.getWidth(), golden_statue1.getHeight());
	
	tree.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 200, 300, tree.getWidth(), tree.getHeight());*/

	//m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), 50);
	printf("GamePlay:  draw\n");
	int cWidth = m_engine->getWindowWidth();
	int cHeight = m_engine->getWindowHeight();


	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());

}

void GamePlay::virtDrawStringsOnTop()
{

	m_engine->lockBackgroundForDrawing();
	char buf1[128];
	char buf2[128];
	char buf3[128];
	char buf4[128];
	sprintf(buf1, "MONSTERS:  %d", noOfMonsters);
	//sprintf(buf1, "SCORES:  %d",playerScore+player->getScores());
	if(gameLevel<3)
		sprintf(buf2, "Still need to find %d diamonds", 3-player->getTreasure());
	else
		sprintf(buf2, "Beat the final BOSS");
	sprintf(buf3, "GAME LEVEL:%d", gameLevel);
	sprintf(buf4, "TIME:%d", m_engine->getModifiedTime()/1000-m_engine->getStartTime());
	m_engine->drawForegroundString(2, 745, buf1, 0xffffff, m_engine->getFont("resources/m5x7.ttf",30));
	m_engine->drawForegroundString(350, 760, buf2, 0xffffff, m_engine->getFont("resources/m5x7.ttf", 35));
	m_engine->drawForegroundString(2, 770, buf3, 0xffffff, m_engine->getFont("resources/m5x7.ttf", 30));
	m_engine->drawForegroundString(180, 760, buf4, 0xffffff, m_engine->getFont("resources/m5x7.ttf", 30));

	m_engine->unlockBackgroundForDrawing();
}

int GamePlay::virtInitialiseObjects() {

	printf("GamePlay debug\n");
	//m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);
	m_engine->createObjectArray(15);

	player = new Scyyz4Object(m_engine, this, "images/soliders.png");
	m_engine->storeObjectInArray(0, player);
	
	
	if (gameLevel > 1) {
		delete arrow;
		delete fireball;
	}
	arrow = new Weapon(m_engine, this, "images/arrow.png", player);
	fireball = new FireBall(m_engine, this, "images/fireball.png", player);

	int xPos, yPos;
	xPos = rand() % (xMax - xMin + 1) + xMin;
	yPos = rand() % (yMax - yMin + 1) + yMin;


	allyPlayer = new Ally(m_engine, this, "images/soliders.png", player);
	m_engine->storeObjectInArray(10, allyPlayer);



	if (gameLevel == 2) {
		noOfMonsters = 3;
		hellmonster1 = new HellMonster(m_engine, this, 6, 50, 50, m_engine->getWindowWidth() - 150, 150, player, "images/mMonster1.png");
		hellmonster2 = new HellMonster(m_engine, this, 7, 50, 50, 150, 150, player, "images/mMonster2.png");
		hellmonster3 = new HellMonster(m_engine, this, 8, 50, 50, m_engine->getWindowWidth() - 150, m_engine->getWindowHeight() - 150, player, "images/mMonster3.png");

		m_engine->storeObjectInArray(6, hellmonster1);
		m_engine->storeObjectInArray(7, hellmonster2);
		m_engine->storeObjectInArray(8, hellmonster3);
	}
	if (gameLevel == 1) {
		noOfMonsters = 2;
		monster1 = new RedMonster(m_engine, this, 4, 50, 50, 300, 300, player, "images/redmonster.png");
		monster2 = new RedMonster(m_engine, this, 3, 50, 50, 400, 450, player, "images/goblin.png");
		m_engine->storeObjectInArray(4, monster1);
		m_engine->storeObjectInArray(3, monster2);
	}

	if (gameLevel == 3) {
		noOfMonsters = 1;
		boss = new BossMonster(m_engine, this, 9, 60, 60, m_engine->getWindowWidth() / 2, m_engine->getWindowHeight() / 2, player, "images/boss.png");
		m_engine->storeObjectInArray(9, boss);
	}


	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());

	return 0;

}
void GamePlay::virtKeyDown(int iKeyCode)
{
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		exit(0);
		break;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT: // shift Pauses
		m_engine->pause();
		m_engine->StageSwitch(4);
		m_engine->redrawDisplay();
		break;
	case SDLK_q:
		saveGame();
		m_engine->StageSwitch(6);
	}
}



void GamePlay::virtMouseDown(int button, int x, int y) {
	if (button != 1)
		return;

	if (x >= 1080 && y >= 750 && x < 1120 && y < 790) {
		m_engine->pause();
		m_engine->StageSwitch(4);
	}
	if (x >= 1130 && y >= 750 && x < 1170 && y < 790) {
		m_engine->StageSwitch(0);
	}
	if (x >= 1180 && y >= 750 && x < 1220 && y < 790&& gameLevel<=1) {
		saveGame();
		m_engine->StageSwitch(6);
	}
	if (x >= 1230 && y >= 750 && x < 1270 && y < 790) {
		exit(0);
	}
	m_engine->redrawDisplay();

}

void GamePlay::storeWeapon(int weaponID)
{
	//arrow = new Weapon(m_engine, this, "images/arrow.png", player);
	//fireball = new FireBall(m_engine, this, "images/fireball.png", player);
	switch (weaponID)
	{
	case 1:
	
		delete arrow;
		arrow = new Weapon(m_engine, this, "images/arrow.png", player);
		m_engine->storeObjectInArray(1, arrow);
		break;
	case 2:
		delete fireball;
		fireball = new FireBall(m_engine, this, "images/fireball.png", player);
		m_engine->storeObjectInArray(1, fireball);
		break;

	}
}


void GamePlay::regenMonster(int index)
{
	int monsterID = rand();
	int numOfMonster = rand() % 2;
	int xPosition = rand() % (m_engine->getWindowWidth() - 100 + 1) + 100;
	int yPosition = rand() % (m_engine->getWindowHeight() - 100 + 1) + 100;

	if (index == 4) {
		delete monster1;
		monster1 = new RedMonster(m_engine, this, index, 50, 50, xPosition, yPosition, player, "images/redmonster.png");
		m_engine->storeObjectInArray(index, monster1);
	}
	else if (index == 3)
	{
		delete monster2;
		monster2 = new RedMonster(m_engine, this, index, 50, 50, xPosition, yPosition, player, "images/redmonster.png");
		m_engine->storeObjectInArray(index, monster2);
	}
	
}

void GamePlay::destoryObject(int objectID) 
{
	if (objectID == 6)
		delete hellmonster1;
	else if (objectID == 7)
		delete hellmonster2;
	else if (objectID == 8)
		delete hellmonster3;
	else if (objectID == 3)
		delete monster2;
	else if (objectID == 4)
		delete monster1;
	/*else if (objectID == 1)
		delete arrow;*/

	m_engine->storeObjectInArray(objectID, NULL);

}

void GamePlay::destroyTiles()
{
	s_tiles->~Scyyz4TileManager();
}

int GamePlay:: getTileValue(int x, int y)
{
	int mapXForScreenX = (x - 0) / s_tiles->getTileWidth();
	int mapYForScreenY = (y-0)/ s_tiles->getTileHeight();
	int tileValue = s_tiles->getMapValue(mapXForScreenX, mapYForScreenY);


	return tileValue;
}

void GamePlay::LevelSwitch()
{
	if (gameLevel < 3) {
		playerScore = player->getScores();
		gameLevel += 1;
		std::vector <std::string>().swap(mapData);
		m_engine->drawableObjectsChanged();
		m_engine->destroyOldObjects(true);

		this->virtSetupBackgroundBuffer();
	}
}

void GamePlay::lose()
{
	m_engine->StageSwitch(3);
}

void GamePlay::saveGame()
{
	ofstream saveFile1;
	saveFile1.open("resources/gameInfo_player.txt");
	saveFile1 << this->getLevel() << ",";
	saveFile1 << player->getScores() << ",";
	saveFile1 << player->getHealth() << ",";
	saveFile1 << player->getXPosition() << ",";
	saveFile1 << player->getYPosition() << ",";
	saveFile1 << player->getMoveDirection() << ",";
	saveFile1 << allyPlayer->getHealth() << ",";
	saveFile1 << allyPlayer->getXPosition() << ",";
	saveFile1 << allyPlayer->getYPosition();
	saveFile1.close();

	ofstream saveFile2;
	saveFile2.open("resources/gameInfo_monster.txt");
	if (gameLevel == 1&& noOfMonsters==2) {
		saveFile2 << monster1->getHealth() << ",";
		saveFile2 << monster1->getXPosition() << ",";
		saveFile2 << monster1->getYPosition() << ",";
		saveFile2 << monster2->getHealth() << ",";
		saveFile2 << monster2->getXPosition() << ",";
		saveFile2 << monster2->getYPosition();
	}
	else if (gameLevel == 1 && monster1 == NULL&& monster2 != NULL) {
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << monster2->getHealth() << ",";
		saveFile2 << monster2->getXPosition() << ",";
		saveFile2 << monster2->getYPosition();
	}
	else if (gameLevel == 1 && monster1 != NULL && monster2 == NULL) {
		saveFile2 << monster1->getHealth() << ",";
		saveFile2 << monster1->getXPosition() << ",";
		saveFile2 << monster1->getYPosition() << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0;
	}
	else if (gameLevel == 1 && noOfMonsters==0) {
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0 << ",";
		saveFile2 << 0;
	}


	else if (gameLevel == 2) {
		saveFile2 << hellmonster1->getHealth() << ",";
		saveFile2 << hellmonster1->getXPosition() << ",";
		saveFile2 << hellmonster1->getYPosition() << ",";
		saveFile2 << hellmonster2->getHealth() << ",";
		saveFile2 << hellmonster2->getXPosition() << ",";
		saveFile2 <<hellmonster2->getYPosition() << ",";
		saveFile2 << hellmonster3->getHealth() << ",";
		saveFile2 << hellmonster3->getXPosition() << ",";
		saveFile2 << hellmonster3->getYPosition();
	}

	saveFile2.close();
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);

}

void GamePlay::loadGame()
{
	ifstream saveFile1;
	string line1;
	int itemCount1 = 0;

	saveFile1.open("resources/gameInfo_player.txt", ios::in);
	if (!saveFile1.is_open())
		return;

	while (getline(saveFile1, line1, ',')) {
		switch (itemCount1++) {
		case 0: this->setLevel(stoi(line1));			break;
		case 1: player->setScores(stoi(line1));			break;
		case 2: player->setHealth(stoi(line1));			break;
		case 3: player->setXPosition(stoi(line1));		break;
		case 4: player->setYPosition(stoi(line1));		break;
		case 5: player->setMoveDirection(stoi(line1));	break;
		case 6: allyPlayer->setHealth(stoi(line1));		break;
		case 7: allyPlayer->setXPosition(stoi(line1));	break;
		case 8: allyPlayer->setYPosition(stoi(line1));	break;
		}
	}
	saveFile1.close();


	ifstream saveFile2;
	string line2;
	int itemCount2 = 0;

	saveFile2.open("resources/gameInfo_monster.txt", ios::in);
	if (!saveFile2.is_open())
		return;

	while (getline(saveFile2, line2, ',')) {
		printf("monster loaded\n");
		switch (itemCount2++) {
		case 0: monster1->setHealth(stoi(line2));			
			if (stoi(line2) == 0)
				destoryObject(4);
				break;
		case 1: monster1->setXPosition(stoi(line2));		break;
		case 2: monster1->setYPosition(stoi(line2));		break;
		case 3: monster2->setHealth(stoi(line2));			
			if (stoi(line2) == 0)
				destoryObject(3);
				break;
		case 4: monster2->setXPosition(stoi(line2));		break;
		case 5: monster2->setYPosition(stoi(line2));		break;
		}
	}
	saveFile2.close();
	load = false;
}