#include "header.h"
#include "Scyyz4Engine.h"
#include "BossMonster.h"
#include <cmath>
#include "Scyyz4TileManager.h"
#include "CollisionDetection.h"


BossMonster::BossMonster(Scyyz4Engine* pEngine, Stage* stage, int indexInArray, int xSize, int ySize, int worldXPos, int worldYPos, Scyyz4Object* player, std::string imageName)
	:Monster(pEngine, stage, xSize, ySize, worldXPos, worldYPos, player, imageName)
	, player(player)
	, mx_position(worldXPos)
	, my_position(worldYPos)
	, xSize(xSize)
	, ySize(ySize)
	, image_path(imageName)
	, m_pMainEngine(pEngine)
	, stage(stage)
	, index(indexInArray)
{
	//printf("bossmonster generate\n");
	/*mx_position = this->getXPosition();
	my_position = this->getYPosition();
*/
	gameStage = (GamePlay*)stage;
	hOutlineW = 600;
	hOutlineH = 30;
	maxHealth = 100;

	monster1 = ImageManager::loadImage(image_path);
	perceptionDistance = 0;


	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = 0;

}


void BossMonster::genMonster()
{

	int iTick = getEngine()->getModifiedTime() / 150; // 1 per 150ms
	int iFrame = iTick % 5;
	if (dir)
		monster1.renderImageWithMask(getEngine()->getForegroundSurface(), monster1.getWidth() / 6 * iFrame + 5, 0, mx_position, my_position, monster1.getWidth() / 6 - 10, monster1.getHeight() / 2);
	else
		monster1.renderImageWithMask(getEngine()->getForegroundSurface(), monster1.getWidth() / 6 * iFrame + 5, monster1.getHeight() / 2, mx_position, my_position, monster1.getWidth() / 6 - 10, monster1.getHeight() / 2);
}

void BossMonster::PerformMovement()
{
	/*detectCollision();*/

	px_position = player->getXPosition();
	py_position = player->getYPosition();

	if (mx_position < 30)
	{
		dir = 1;
		dX = 1;
		mx_position = 30;
	}
	if (mx_position >= getEngine()->getWindowWidth() - xSize - 30)
	{
		dir = 0;
		dX = -1;
		mx_position = getEngine()->getWindowWidth() - xSize - 30;
	}
	if (my_position < 30)
	{
		dY = 1;
		my_position = 30;
	}
	if (my_position >= getEngine()->getWindowHeight() - ySize - 30)
	{
		dY = -1;
		my_position = getEngine()->getWindowHeight() - ySize - 30;
	}

	int xDistance = mx_position - px_position;
	int yDistance = my_position - py_position;

	int distance = (int)sqrt(xDistance*xDistance + yDistance * yDistance);

	if (distance < 200)
	{
		if (xDistance > 0)
		{
			dir = 0;
			mx_position -= dX;
		}
		else if (xDistance < 0)
		{
			dir = 1;
			mx_position += dX;
		}


		if (yDistance > 0)
			my_position -= dY;
		else if (yDistance < 0)
			my_position += dY;
	}

}

void BossMonster::drawHP()
{

	hOutlineX = m_pMainEngine->getWindowWidth()/4 ;
	hOutlineY = (int)(100 - 1.5 * healthH - 1);

	float healthPercentage = (float)health / (float)maxHealth;

	healthX = hOutlineX + 1;
	healthY = hOutlineY + 1;
	healthW = (int)((hOutlineW - 2) * healthPercentage);
	healthH = hOutlineH - 2;

	drawHealth = CanDraw(hOutlineX, hOutlineY, hOutlineW, hOutlineH);

	if (drawHealth) {
		getEngine()->drawForegroundRectangle(hOutlineX, hOutlineY, hOutlineX + hOutlineW - 1, hOutlineY + hOutlineH - 1, 0xFFFFFF);
		if (healthW > 0)
			getEngine()->drawForegroundRectangle(healthX, healthY, healthX + healthW - 1, healthY + healthH - 1, 0XFF0000);
		else {
			*player = *player - 30;
			player->gameWin();
			stage->destoryObject(index);
			/*m_pMainEngine->StageSwitch(5);*/

		}
	}
}

void BossMonster::minusHP()
{
	health -= 5;
}

int BossMonster::getXPosition()
{
	return mx_position;
}

int BossMonster::getYPosition()
{
	return my_position;
}

void BossMonster::detectCollision()
{
	insideBoundary();

	DisplayableObject* pObject;
	for (int iObjectId = 0; (pObject = m_pMainEngine->getDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		if (pObject == this)
			continue;
		if (pObject == nullptr)
			continue;

		if (CollisionDetection::checkCircles(pObject->getXCentre(),
			pObject->getYCentre(),
			mx_position, my_position,
			80))
		{
			/*	printf("detected\n");*/
			mx_position -= 10;
			my_position -= 10;
		}

		if (CollisionDetection::checkCircles(pObject->getXCentre(),
			pObject->getYCentre(),
			mx_position, my_position,
			80) && iObjectId == 0)
		{
			player->minusHP(10);
		}
	}

	BossMonster* monster;
	for (int iObjectId = 6; (monster = (BossMonster*)m_pMainEngine->getDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		/*printf("onjectID:%d\n", iObjectId);*/

		if (monster == this)
			continue;
		if (monster == nullptr)
			continue;

		if (CollisionDetection::checkCircles(monster->getXCentre(),
			monster->getYCentre(),
			mx_position, my_position,
			80))
		{
			/*	printf("detected\n");*/
			mx_position -= 10;
			my_position -= 10;
		}
	}
}

void BossMonster::insideBoundary()
{
	gameStage = (GamePlay*)stage;
	int tileValue_UpperLeft = gameStage->getTileValue(mx_position, my_position);
	int tileValue_UpperRight = gameStage->getTileValue(mx_position + xSize, my_position);
	int tileValue_LowerRight = gameStage->getTileValue(mx_position + xSize, my_position + ySize);
	int tileValue_LowerLeft = gameStage->getTileValue(mx_position, my_position + ySize);

	int tileValue_LeftMiddle = gameStage->getTileValue(mx_position, my_position + ySize / 2);
	int tileValue_RightMiddle = gameStage->getTileValue(mx_position + xSize, my_position + ySize / 2);

	//printf("tileValue---:%d\n", tileValueRight);
	if (tileValue_UpperLeft == 1 && tileValue_UpperRight == 1)
	{
		my_position += 10;
	}
	if (tileValue_UpperLeft == 2 || tileValue_LowerLeft == 2 || tileValue_LeftMiddle == 2)
	{
		mx_position += 10;
	}
	if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle == 2)
	{
		mx_position -= 10;
	}
	if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		my_position -= 10;
	}
	if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		my_position -= 10;
	}
	if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		my_position += 10;
	}
}