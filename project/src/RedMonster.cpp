#include "header.h"
#include "Scyyz4Engine.h"
#include "RedMonster.h"
#include <cmath>
#include "Scyyz4TileManager.h"
#include "CollisionDetection.h"


RedMonster::RedMonster(Scyyz4Engine* pEngine, Stage* stage, int indexInArray,int xSize, int ySize, int worldXPos, int worldYPos, Scyyz4Object* player,std::string imageName)
	:Monster(pEngine, stage, xSize, ySize, worldXPos, worldYPos,player,imageName)
	,player(player)
	,xSize(xSize)
	,ySize(ySize)
	,image_path(imageName)
	,m_pMainEngine(pEngine)
	,stage(stage)
	,index(indexInArray)
{
	/*mx_position = this->getXPosition();
	my_position = this->getYPosition();
*/
	//printf("Redmonster generate\n");
	gameStage = (GamePlay*)stage;
	hOutlineW = 50;
	hOutlineH = 10;
	maxHealth = 100;

	mx_position = worldXPos;
	my_position = worldYPos;
	monster1=ImageManager::loadImage(image_path);
	perceptionDistance = 0;


}


void RedMonster::genMonster()
{
	int iTick = getEngine()->getModifiedTime() / 150; // 1 per 150ms
	int iFrame = iTick % 7;
	if(dir)
		monster1.renderImageWithMask(getEngine()->getForegroundSurface(), monster1.getWidth() / 8 * iFrame, 0, mx_position, my_position, monster1.getWidth() / 8, monster1.getHeight()/2);
	else
		monster1.renderImageWithMask(getEngine()->getForegroundSurface(), monster1.getWidth() / 8 * iFrame, monster1.getHeight()/2, mx_position, my_position, monster1.getWidth() / 8, monster1.getHeight() / 2);
}

void RedMonster::PerformMovement()
{
	/*detectCollision();*/
	findPlayer(mx_position,my_position);

	px_position = player->getXPosition();
	py_position = player->getYPosition();

	if (mx_position < 30)
	{
		dir = 1;
		dX = 1;
		mx_position = 30;
	}
	if (mx_position >= getEngine()->getWindowWidth()-xSize-30)
	{
		dir = 0;
		dX = -1;
		mx_position = getEngine()->getWindowWidth() - xSize-30;
	}		
	if (my_position < 30)
	{
		dY = 1;
		my_position = 30;
	}
	if (my_position >= getEngine()->getWindowHeight()-ySize-30)
	{
		dY = -1;
		my_position = getEngine()->getWindowHeight() - ySize-30;
	}

	int xDistance = mx_position-px_position;
	int yDistance = my_position-py_position;

	int distance = (int)sqrt(xDistance*xDistance + yDistance*yDistance);

	
}

void RedMonster::drawHP()
{

	hOutlineX = mx_position-10 ;
	hOutlineY = (int)(my_position - 1.5 * healthH - 1);

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

			gameStage->killMonster();
			gameStage->destoryObject(index);
		}
	}
}

void RedMonster::detectCollision()
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
			60))
		{
		/*	printf("detected\n");*/
			mx_position -= 1;
			my_position -= 1;
		}

		if (CollisionDetection::checkCircles(pObject->getXCentre(),
			pObject->getYCentre(),
			mx_position, my_position,
			60) && iObjectId == 0)
		{
			*player = *player - 15;
		}
	}

	RedMonster* monster;
	for (int iObjectId = 3; (monster =(RedMonster*) m_pMainEngine->getDisplayableObject(iObjectId)) != NULL; iObjectId++)
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
			mx_position -= 1;
			my_position -= 1;
		}
	}
}

void RedMonster::insideBoundary()
{
	int tileValue_UpperLeft = gameStage->getTileValue(mx_position, my_position);
	int tileValue_UpperRight = gameStage->getTileValue(mx_position + xSize, my_position);
	int tileValue_LowerRight = gameStage->getTileValue(mx_position + xSize, my_position + ySize);
	int tileValue_LowerLeft = gameStage->getTileValue(mx_position, my_position + ySize);

	int tileValue_LeftMiddle = gameStage->getTileValue(mx_position, my_position + ySize / 2);
	int tileValue_RightMiddle = gameStage->getTileValue(mx_position + xSize, my_position + ySize / 2);

	//printf("tileValue---:%d\n", tileValueRight);
	if (tileValue_UpperLeft == 1 && tileValue_UpperRight == 1)
	{
		my_position += 5;
	}
	if (tileValue_UpperLeft == 2 || tileValue_LowerLeft == 2 || tileValue_LeftMiddle == 2)
	{
		mx_position += 5;
	}
	if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle == 2)
	{
		mx_position -= 5;
	}
	if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		my_position -= 5;
	}
	if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		my_position -= 5;
	}
	if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		my_position += 5;
	}
}