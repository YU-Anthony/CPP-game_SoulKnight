#include "header.h"
#include "Scyyz4Engine.h"
#include "ImageManager.h"
#include "Scyyz4Object.h"
#include "CollisionDetection.h"


using namespace std;

extern map <int, string, less<int>> highscores;
extern int finalTime;
extern bool isNewRecord;
//extern int level;

Scyyz4Object::Scyyz4Object(Scyyz4Engine* pEngine, GamePlay* stage,const char* image_path)
	:DisplayableObject(pEngine)
	,image(image_path)
	,gameStage(stage)
	,p_mainEngine(pEngine)
	,xSize(34)
	,ySize(60)
{
	//printf("player generate\n");
	m_pTileManager = gameStage->getTileManager();
	hOutlineW = 200;
	hOutlineH = 15;
	maxHealth = 100;


	scores = 0;
	m_iCurrentScreenX = 300; // Starting position on the screen
	m_iCurrentScreenY = 500;
	m_iDrawWidth = 100; // Width of drawing area
	m_iDrawHeight = 100; // Height of drawing area
}



void Scyyz4Object::drawHP(int x,int y)
{
	hOutlineX = x - 10;
	hOutlineY = (int)(y - 1.5 * healthH - 1);

	float healthPercentage = (float)health / (float)maxHealth;

	healthX = hOutlineX + 1;
	healthY = hOutlineY + 1;
	healthW = (int)((hOutlineW - 2) * healthPercentage);
	healthH = hOutlineH - 2;


		p_mainEngine->drawForegroundRectangle(hOutlineX, hOutlineY, hOutlineX + hOutlineW - 1, hOutlineY + hOutlineH - 1, 0xFFFFFF);
		if (healthW > 0)
			p_mainEngine->drawForegroundRectangle(healthX, healthY, healthX + healthW - 1, healthY + healthH - 1, 0X00FF00);
		else {
			/*gameStage->destroyTiles();*/
			p_mainEngine->StageSwitch(3);
			
		}

}


void Scyyz4Object::virtDraw()
{
	SimpleImage r_image = ImageManager::loadImage(image, true);
	weapeon = ImageManager::loadImage("images/arrow.png", true);
	HP = ImageManager::loadImage("images/HP.png",true);
	HP.renderImageWithMask(p_mainEngine->getForegroundSurface(), 0, 0, hOutlineX-50, hOutlineY - 20, HP.getWidth(), HP.getHeight());

	int iTick = p_mainEngine->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 8;
	insideBoundary();

	if(!dir)
		r_image.renderImageWithMask(p_mainEngine->getForegroundSurface(), r_image.getWidth() / 9*iFrame, 0,
			m_iCurrentScreenX, m_iCurrentScreenY, r_image.getWidth()/9, r_image.getHeight()/2);
	else
		r_image.renderImageWithMask(p_mainEngine->getForegroundSurface(), r_image.getWidth() / 9 * iFrame, r_image.getHeight()/2, 
			m_iCurrentScreenX, m_iCurrentScreenY, r_image.getWidth() / 9, r_image.getHeight() / 2);
	
	drawHP(830, 785);

	SimpleImage door = ImageManager::loadImage("images/door.png",true);
	int tick = p_mainEngine->getModifiedTime() / 300; // 1 per 100ms
	int time = tick % 4;
	if(isdoorOpen)
		door.renderImageWithMask(p_mainEngine->getForegroundSurface(), door.getWidth() / 4 * time, 0, 1100, 90, door.getWidth() / 4, 63);
	else
		door.renderImageWithMask(p_mainEngine->getForegroundSurface(), door.getWidth() / 4 * 0, 0, 1100, 90, door.getWidth() / 4, 63);

}


void Scyyz4Object::virtDoUpdate(int iCurrentTime)
{
	finalTime = p_mainEngine->getModifiedTime() / 1000 - p_mainEngine->getStartTime();

	p_mainEngine->lockBackgroundForDrawing();
	// The condition here need to be changed-------------------------
	//printf("level:%d\n", gameStage->getLevel());
	if ((gameStage->getLevel())==3 && (isWin ==true))
	{
		if (highscores.size() < 5)
		{
			printf("highscores size:%d\n",highscores.size());
			highscores.insert({ finalTime, "Anonymous" });
			isNewRecord = true;
			p_mainEngine->StageSwitch(5);
			return;
		}
		if (highscores.size() >= 5)
		{
			if (finalTime < prev(highscores.end())->first)
			{
				printf("score size:%d\n",highscores.size());
				highscores.insert({ finalTime, "Anonymous" });
				highscores.erase(prev(highscores.end()));
				isNewRecord = true;
				p_mainEngine->StageSwitch(5);
				return;
			}
			else {
				p_mainEngine->StageSwitch(7);
				return;
			}
		}
		p_mainEngine->StageSwitch(5);
		return;
	}
	p_mainEngine->unlockBackgroundForDrawing();

	m_iCurrentScreenX += dX;
	m_iCurrentScreenY += dY;

	//if (scores>=30) {
	//	//numOfTreausre = 0;
	//	gameStage->LevelSwitch();
	//}
	// Change position if player presses a key
	if (p_mainEngine->isKeyPressed(SDLK_w)) {
		att_direction = 0;
		move_direction = 0;
		dX = 0;
		dY = -1;
	}
	else if (p_mainEngine->isKeyPressed(SDLK_s)) {
		move_direction = 1;
		att_direction = 4;
		dX = 0;
		dY = 1;
	}
	else if (p_mainEngine->isKeyPressed(SDLK_a)) {
		move_direction = 2;
		att_direction = 6;
		dX = -1;
		dY = 0;

		dir = 1;
	}
	else if (p_mainEngine->isKeyPressed(SDLK_d)) {
		move_direction = 3;
		att_direction = 2;
		dX = 1;
		dY = 0;
		dir = 0;
	}
	else if (p_mainEngine->isKeyPressed(SDLK_1))
		weaponID = 1;
	else if (p_mainEngine->isKeyPressed(SDLK_2))
		weaponID = 2;
	else if (p_mainEngine->isKeyPressed(SDLK_j)) {
		gameStage->storeWeapon(weaponID);
	}

	

	/*if (p_mainEngine->isKeyPressed(SDLK_d) && p_mainEngine->isKeyPressed(SDLK_w)) {
		att_direction = 1;
	}else if (p_mainEngine->isKeyPressed(SDLK_s) && p_mainEngine->isKeyPressed(SDLK_w)) {
		att_direction = 3;
	}else if (p_mainEngine->isKeyPressed(SDLK_a) && p_mainEngine->isKeyPressed(SDLK_s)) {
		att_direction = 5;
	}else if (p_mainEngine->isKeyPressed(SDLK_a) && p_mainEngine->isKeyPressed(SDLK_w)) {
		att_direction = 7;
	}*/



	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= p_mainEngine->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = p_mainEngine->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= p_mainEngine->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = p_mainEngine->getWindowHeight() - m_iDrawHeight;

	if (x_last != m_iCurrentScreenX) {
		x_last = m_iCurrentScreenX;
		y_last = m_iCurrentScreenY;
	}

	xPosition = m_iCurrentScreenX;
	yPosition = m_iCurrentScreenY;

	/*printf("xPosition:%d,yPosition:%d\n", xPosition, yPosition);*/
	if (gameStage->returnMonsterNum() == 0 && numOfTreausre == 3) {
		isdoorOpen = true;
	}

	if (isdoorOpen == true && (xPosition > 1100 & xPosition < 1150) && (yPosition > 90 && yPosition < 150) && isfindAlly == true) {
		gameStage->LevelSwitch();
	}else 
		redrawDisplay();
}



void Scyyz4Object::insideBoundary()
{
	int tileValue_UpperLeft = gameStage->getTileValue(xPosition, yPosition);
	int tileValue_UpperRight = gameStage->getTileValue(xPosition + xSize, yPosition);
	int tileValue_LowerRight = gameStage->getTileValue(xPosition+xSize, yPosition+ySize);
	int tileValue_LowerLeft= gameStage->getTileValue(xPosition, yPosition + ySize);

	int tileValue_LeftMiddle = gameStage->getTileValue(xPosition, yPosition + ySize/2);
	int tileValue_RightMiddle = gameStage->getTileValue(xPosition+xSize, yPosition + ySize / 2);

	//printf("tileValue---:%d\n", tileValueRight);
	if (tileValue_UpperLeft == 1&& tileValue_UpperRight==1)
	{
		m_iCurrentScreenY += 5;
	}
	if (tileValue_UpperLeft == 2 || tileValue_LowerLeft==2 || tileValue_LeftMiddle == 2 ||tileValue_LeftMiddle == 12)
	{
		m_iCurrentScreenX += 5;
	}
	if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle==2 || tileValue_RightMiddle == 12)
	{
		m_iCurrentScreenX -= 5;
	}
	if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		m_iCurrentScreenY -= 5;
	}
	if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		m_iCurrentScreenY -= 5;
	}
	if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		m_iCurrentScreenY += 5;
	}
}


void Scyyz4Object::plusTreasure()
{
	if (numOfTreausre < 3)
		numOfTreausre += 1;
	else
		numOfTreausre = 3;

}

int Scyyz4Object::getTreasure()
{
	return numOfTreausre;
}
