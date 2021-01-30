#include "header.h"
#include "Scyyz4Engine.h"
#include "ImageManager.h"
#include "Ally.h"
#include "CollisionDetection.h"



Ally::Ally(Scyyz4Engine* pEngine, GamePlay* stage, std::string image_path, Scyyz4Object* object)
	: DisplayableObject(pEngine)
	,object(object)
	, image(image_path)
	, gameStage(stage)
	, p_mainEngine(pEngine)
	, xSize(34)
	, ySize(60)
{
	printf("ally generate\n");
	hOutlineW = 100;
	hOutlineH = 15;
	maxHealth = 100;

	int i = rand() % 4;
	int j = rand() % 5;

	xPosition = 40*i+50*j; // Starting position on the screen
	yPosition = 40*i+50*j;


	m_iDrawWidth = 100; // Width of drawing area
	m_iDrawHeight = 100; // Height of drawing area
	health = 100;
}



Ally::~Ally()
{
	printf("ally release\n");
}


void Ally::drawHP(int x, int y)
{
	hOutlineX = x - 10;
	hOutlineY = (int)(y - 1.5 * healthH - 1);

	float healthPercentage = (float)health / (float)maxHealth;

	healthX = hOutlineX + 1;
	healthY = hOutlineY + 1;
	healthW = (int)((hOutlineW - 2) * healthPercentage);
	healthH = hOutlineH - 2;


	getEngine()->drawForegroundRectangle(hOutlineX, hOutlineY, hOutlineX + hOutlineW - 1, hOutlineY + hOutlineH - 1, 0xFFFFFF);
	if (healthW > 0)
		getEngine()->drawForegroundRectangle(healthX, healthY, healthX + healthW - 1, healthY + healthH - 1, 0X00FF00);
	else {
		p_mainEngine->StageSwitch(3);
	}

}


void Ally::virtDraw()
{

	SimpleImage r_image = ImageManager::loadImage(image, true);
	//weapeon = ImageManager::loadImage("images/arrow.png", true);
	HP = ImageManager::loadImage("images/HP.png", true);
	HP.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, hOutlineX - 50, hOutlineY - 20, HP.getWidth(), HP.getHeight());


	int iTick = getEngine()->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 8;


	if (!dir)
		r_image.renderImageWithMask(getEngine()->getForegroundSurface(), r_image.getWidth() / 9 * iFrame, 0,
			xPosition, yPosition, r_image.getWidth() / 9, r_image.getHeight() / 2);
	else
		r_image.renderImageWithMask(getEngine()->getForegroundSurface(), r_image.getWidth() / 9 * iFrame, r_image.getHeight() / 2,
			xPosition, yPosition, r_image.getWidth() / 9, r_image.getHeight() / 2);

	//drawHP(50, 80);



}


void Ally::virtDoUpdate(int iCurrentTime)
{
	xPosition += dX;
	yPosition += dY;

	detectCollision();
	attackMonster();

	int x_now = this->getXCentre();
	int y_now = this->getYCentre();


	if (x_last != x_now) {
		x_last = x_now;
		y_last = y_now;
	}



	//xPosition = x_now;
	//yPosition = y_now;

	redrawDisplay();
}




void Ally::detectCollision()
{
	//¡ì¡ìprintf("snake size:%d\n",tempsnake.size());
	tempsnake = gameStage->getSnake();
	int allyID=0;

	if (CollisionDetection::checkCircles(object->getXCentre(),
		object->getYCentre(), xPosition, yPosition, 100))
		object->findAlly(true);
	else
		object->findAlly(false);


	if (tempsnake.size()==0)
	{
		if (CollisionDetection::checkCircles(object->getXCentre(),
			object->getYCentre(), xPosition, yPosition, 100))
		{
			//printf("0 Player:%d, follower:%d\n", object->getXCentre(), xPosition);
			//printf("snake numbers:%d\n", tempsnake.size());
			controlMovement(object);
			if (!hasAdded) {
				gameStage->addAlly(this);
				hasAdded = true;
			}

		}

	}
	else if (tempsnake.size()!=0) {

		if (CollisionDetection::checkCircles(object->getXCentre(),
			object->getYCentre(), xPosition, yPosition, 100))
		{

			for (int i = 0; i < tempsnake.size(); i++)
			{
				if (this == tempsnake[allyID]) {
					hasAdded = true;
					allyID = i;
					break;
				}
			}

			if (!hasAdded) {
				gameStage->addAlly(this);
				hasAdded = true;
			}

			//printf("aaaaaaa%d  Player:%d, follower:%d\n", allyID,object->getXCentre(), xPosition);
			//printf("snake numbers:%d\n", tempsnake.size());
			if(allyID==0)
				controlMovement(object);
			if(allyID!=0)
				controlMovement(tempsnake[allyID - 1]);

		}
	
	}

	int tileValue_UpperLeft = gameStage->getTileValue(xPosition, yPosition);
	int tileValue_UpperRight = gameStage->getTileValue(xPosition + xSize, yPosition);
	int tileValue_LowerRight = gameStage->getTileValue(xPosition + xSize, yPosition + ySize);
	int tileValue_LowerLeft = gameStage->getTileValue(xPosition, yPosition + ySize);

	int tileValue_LeftMiddle = gameStage->getTileValue(xPosition, yPosition + ySize / 2);
	int tileValue_RightMiddle = gameStage->getTileValue(xPosition + xSize, yPosition + ySize / 2);

	//printf("tileValue---:%d\n", tileValueRight);
	if (tileValue_UpperLeft == 1 && tileValue_UpperRight == 1)
	{
		dY =1;
	}
	if (tileValue_UpperLeft == 2 || tileValue_LowerLeft == 2 || tileValue_LeftMiddle == 2)
	{
		dX=1;
	}
	if (tileValue_UpperRight == 2 || tileValue_LowerRight == 2 || tileValue_RightMiddle == 2)
	{
		dX=-1;
	}
	if (tileValue_LowerRight == 1 && tileValue_LowerRight == 1)
	{
		dY=-1;
	}
	if (tileValue_LowerRight == 2 && tileValue_LowerRight == 2)
	{
		dY=-1;
	}
	if (tileValue_UpperRight == 2 && tileValue_UpperRight == 2)
	{
		dY=1;
	}

}

int Ally::getMoveDirection()
{
	if(dY==-1&&dX==0)
		move_direction = 0;
	if (dX == 0 && dY == 1 )
		move_direction = 1;
	if (dX == -1 && dY == 0)
		move_direction = 2;
	if (dX == 1 && dY == 0)
		move_direction = 3;

	return move_direction;
}

void Ally::controlMovement(Scyyz4Object* player)
{
	if (player->getMoveDirection() == 0 && xPosition == player->getXPosition())
	{
		dX = 0;
		dY = -1;
		/*yPosition -= 10;*/
	}
	if (player->getMoveDirection() == 0 && xPosition < player->getXPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 0 && xPosition > player->getXPosition())
	{
		dX = -1;
		dY = 0;
	}

	if (player->getMoveDirection() == 1 && xPosition == player->getXPosition())
	{
		dX = 0;
		dY = 1;
	}
	if (player->getMoveDirection() == 1 && xPosition < player->getXPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 1 && xPosition > player->getXPosition())
	{
		dX = -1;
		dY = 0;
	}

	if (player->getMoveDirection() == 2 && yPosition == player->getYPosition())
	{
		dX = -1;
		dY = 0;
	}
	if (player->getMoveDirection() == 2 && yPosition > player->getYPosition())
	{
		dX = 0;
		dY = -1;
	}
	if (player->getMoveDirection() == 2 && yPosition < player->getYPosition())
	{
		dX = 0;
		dY = 1;
	}

	if (player->getMoveDirection() == 3 && yPosition == player->getYPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 3 && yPosition > player->getYPosition())
	{
		dX = 0;
		dY = -1;
	}
	if (player->getMoveDirection() == 3 && yPosition < player->getYPosition())
	{
		dX = 0;
		dY = 1;
	}
}

void Ally::controlMovement(Ally* player)
{
	if (player->getMoveDirection() == 0 && xPosition == player->getXPosition())
	{
		dX = 0;
		dY = -1;
	}
	if (player->getMoveDirection() == 0 && xPosition < player->getXPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 0 && xPosition > player->getXPosition())
	{
		dX = -1;
		dY = 0;
	}

	if (player->getMoveDirection() == 1 && xPosition == player->getXPosition())
	{
		dX = 0;
		dY = 1;
	}
	if (player->getMoveDirection() == 1 && xPosition < player->getXPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 1 && xPosition > player->getXPosition())
	{
		dX = -1;
		dY = 0;
	}

	if (player->getMoveDirection() == 2 && yPosition == player->getYPosition())
	{
		dX = -1;
		dY = 0;
	}
	if (player->getMoveDirection() == 2 && yPosition > player->getYPosition())
	{
		dX = 0;
		dY = -1;
	}
	if (player->getMoveDirection() == 2 && yPosition < player->getYPosition())
	{
		dX = 0;
		dY = 1;
	}

	if (player->getMoveDirection() == 3 && yPosition == player->getYPosition())
	{
		dX = 1;
		dY = 0;
	}
	if (player->getMoveDirection() == 3 && yPosition > player->getYPosition())
	{
		dX = 0;
		dY = -1;
	}
	if (player->getMoveDirection() == 3 && yPosition < player->getYPosition())
	{
		dX = 0;
		dY = 1;
	}
}



void Ally::attackMonster()
{
	int i = 0;
	/*if(tempsnake.size()!=0)
		gameStage->attackOn();*/
	RedMonster* monster;
	for (int iObjectId = 3; (monster = (RedMonster*)p_mainEngine->getDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		if (monster == nullptr)
			continue;

		if (CollisionDetection::checkCircles(monster->getXCentre(),
			monster->getYCentre(),
			xPosition, yPosition,
			200))
		{
			i++;
			//printf("dected:%d\n",i);
			//gameStage->attackOn(this);
		}
		
		//printf("monsterid:%d\n",iObjectId);
	}
}