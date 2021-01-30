#include "header.h"
#include "Scyyz4Engine.h"
#include "FireBall.h"
#include "Scyyz4Object.h"
#include "CollisionDetection.h"
#include "RedMonster.h"


FireBall::FireBall(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path, Scyyz4Object* moveCharacter)
	:Weapon(pEngine,stage, image_path, moveCharacter)
	, image(image_path)
	, moveCharacter(moveCharacter)
{
	//printf("Fireball generate\n");
	gameStage=stage;
	m_pTileManager = gameStage->getTileManager();
	xPosition = moveCharacter->getXCentre()-40;
	yPosition = moveCharacter->getYCentre()-30;

	m_iDrawWidth = 100; // Width of drawing area
	m_iDrawHeight = 100; // Height of drawing area
}


void FireBall::virtDraw()
{
	SimpleImage r_image = ImageManager::loadImage("images/fireball.png", true);
	SimpleImage l_image = ImageManager::loadImage("images/fireballleft.png", true);

	int iTick = getEngine()->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 10;

	dir = moveCharacter->attDirection();
	if(dir==2)
		r_image.renderImageWithMask(getEngine()->getForegroundSurface(), r_image.getWidth() / 10*iFrame , 0, xPosition, yPosition, r_image.getWidth() / 10, r_image.getHeight());
	else if(dir==6)
		l_image.renderImageWithMask(getEngine()->getForegroundSurface(), l_image.getWidth() / 10 * iFrame, 0, xPosition, yPosition, l_image.getWidth() / 10, l_image.getHeight());
}


void FireBall::virtDoUpdate(int iCurrentTime)
{
	if (dir == 6)
		xPosition -= dX;
	else if (dir == 2)
		xPosition += dX;

	findObstacles();
	detectCollision();
	redrawDisplay();
}

void FireBall::detectCollision()
{
	RedMonster* pObject;
	int iObjectId = 3;

	while (iObjectId <= 9) {
		if ((pObject = (RedMonster*)getEngine()->getDisplayableObject(iObjectId)) != NULL)
		{
			/*		printf("yposition;%d\n", yPosition);*/
			if (CollisionDetection::checkCircles(pObject->getXPosition(),
				pObject->getYPosition(),
				xPosition, yPosition,
				50))
			{
				pObject->minusHP();
				/*printf("xposition:%d\n", pObject->getXCentre());
				printf("detected collision\n");*/
				pEngine->storeObjectInArray(1, NULL);
			}
		}
		iObjectId++;
	}
}

void FireBall::findObstacles()
{
	int tileValue_UpperLeft = gameStage->getTileValue(xPosition + 5, yPosition);
	int tileValue_UpperRight = gameStage->getTileValue(xPosition + 30, yPosition);
	int tileValue_LowerRight = gameStage->getTileValue(xPosition +30, yPosition + 10);
	int tileValue_LowerLeft = gameStage->getTileValue(xPosition + 5, yPosition + 10);

	int tileValue_LeftMiddle = gameStage->getTileValue(xPosition, yPosition + 5);
	int tileValue_RightMiddle = gameStage->getTileValue(xPosition + 10, yPosition + 5);

	if (tileValue_UpperLeft == 1 && tileValue_UpperRight == 1)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	if (tileValue_UpperLeft == 2 || tileValue_LowerLeft == 2 || tileValue_LeftMiddle == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}

	//Find the treasure
	if (tileValue_UpperLeft == 8 || tileValue_UpperRight == 8) {
		//printf("Weapon debug:%d, %d, %d\n", tileValue_UpperLeft, tileValue_UpperRight, tileValue_LowerLeft);
		pEngine->storeObjectInArray(1, NULL);
		int iTileX;
		if (tileValue_UpperRight == 8)
			iTileX = m_pTileManager->getMapXForScreenX(xPosition + 30);
		else
			iTileX = m_pTileManager->getMapXForScreenX(xPosition + 10);
		int iTileY = m_pTileManager->getMapYForScreenY(yPosition);
		int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);

		int index = rand() % 4;
		if (index < 3) {
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile + 1, getEngine(), getEngine()->getBackgroundSurface());
			moveCharacter->plusTreasure();

		}
		else if (index == 3 || index == 4) {
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile - 5, getEngine(), getEngine()->getBackgroundSurface());
		}

	}
}