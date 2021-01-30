#include "header.h"
#include "Scyyz4Engine.h"
#include "ImageManager.h"
#include "Weapon.h"
#include "Scyyz4Object.h"
#include "CollisionDetection.h"
#include "RedMonster.h"

Weapon::Weapon(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path,Scyyz4Object* moveCharacter)
	:DisplayableObject(pEngine)
	,pEngine(pEngine)
	, image(image_path)
	, gameStage(stage)
	,moveCharacter(moveCharacter)
{
	//printf("Weapon generate\n");
	xPosition = moveCharacter->getXCentre() - 40;
	yPosition = moveCharacter->getYCentre() - 30;
	m_pTileManager = gameStage->getTileManager();

	m_iDrawWidth = 100; // Width of drawing area
	m_iDrawHeight = 100; // Height of drawing area
}

//Weapon::Weapon(Scyyz4Engine* pEngine)
//	:DisplayableObject(pEngine)
//{
//
//}




void Weapon::virtDraw()
{
	dir = moveCharacter->attDirection();
	r_image = ImageManager::loadImage(image, true);

	int iTick = getEngine()->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 8;
	r_image.renderImageWithMask(getEngine()->getForegroundSurface(), r_image.getWidth() / 8 * dir, 0, xPosition, yPosition, r_image.getWidth() / 8, r_image.getHeight());

}


void Weapon::virtDoUpdate(int iCurrentTime)
{
	if (dir == 0)
		yPosition -= dY;
	else if (dir == 1)
	{
		xPosition -= dX;
		yPosition += dY;
	}else if (dir==2)
	{
		xPosition += dX;
	}else if (dir == 3) {
		xPosition += dX;
		yPosition += dY;
	}else if (dir ==4)
		yPosition += dY;
	else if (dir == 5) {
		xPosition -= dX;
		yPosition += dY;
	}else if (dir == 6)
		xPosition -= dX;
	else if (dir == 7) {
		xPosition -= dX;
		yPosition -= dY;
	}

	findObstacles();
	detectCollision();
	//printf("weapon debug:3\n");
	/*if(this!=NULL)
		redrawDisplay();*/
}

int Weapon::getXPosition()
{
	return xPosition;
}

int Weapon::getYPosition()
{
	return yPosition;
}

void Weapon::detectCollision()
{
	RedMonster* pObject;
	int iObjectId = 3;

	while(iObjectId<=9) {
		if ((pObject = (RedMonster*)getEngine()->getDisplayableObject(iObjectId)) != NULL)
		{
	/*		printf("yposition;%d\n", yPosition);*/
			if (CollisionDetection::checkCircles(pObject->getXPosition(),
				pObject->getYPosition(),
				xPosition, yPosition,
				50))
			{
				pObject->minusHP();
				//delete this;
				pEngine->storeObjectInArray(1, NULL);
				//setVisible(false);
				//delete this;
			}
		}
		iObjectId++;
	}
}

void Weapon::findObstacles()
{
	int tileValue_UpperLeft = gameStage->getTileValue(xPosition+5, yPosition);
	int tileValue_UpperRight = gameStage->getTileValue(xPosition + 30, yPosition);
	int tileValue_LowerRight = gameStage->getTileValue(xPosition + r_image.getWidth() / 8, yPosition + 10);
	int tileValue_LowerLeft = gameStage->getTileValue(xPosition+5, yPosition + 10);

	int tileValue_LeftMiddle = gameStage->getTileValue(xPosition, yPosition + 5);
	int tileValue_RightMiddle = gameStage->getTileValue(xPosition + 10, yPosition + 5);

	if (tileValue_UpperLeft == 1 && tileValue_UpperRight == 1)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	else if (tileValue_UpperLeft == 2 || tileValue_LowerLeft == 2 || tileValue_LeftMiddle == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	else if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	else if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	else if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}
	else if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		pEngine->storeObjectInArray(1, NULL);
	}

	//Find the treasure
	if (tileValue_UpperLeft == 8 || tileValue_UpperRight==8) {
		//printf("Weapon debug:%d, %d, %d\n", tileValue_UpperLeft, tileValue_UpperRight, tileValue_LowerLeft);
		//line1;
		int iTileX;
		if(tileValue_UpperRight == 8)
			iTileX = m_pTileManager->getMapXForScreenX(xPosition + 30);
		else 
			iTileX = m_pTileManager->getMapXForScreenX(xPosition+10);
		int iTileY = m_pTileManager->getMapYForScreenY(yPosition);
		int iCurrentTile = m_pTileManager->getMapValue(iTileX, iTileY);

		int index = rand() % 4;
		if (index <3 ) {
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile + 1, getEngine(), getEngine()->getBackgroundSurface());
			moveCharacter->plusTreasure();

		}else if (index == 3 || index == 4) {
			m_pTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile - 5, getEngine(), getEngine()->getBackgroundSurface());
		}
		
	}
}