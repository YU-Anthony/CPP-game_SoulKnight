#include "header.h"
#include "Scyyz4Engine.h"
#include "Monster.h"
#include <algorithm>
#include <stack>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

Monster::Monster(Scyyz4Engine* pEngine,Stage* stage,int xSize,int ySize,int worldXPos,int worldYPos, Scyyz4Object* player,std::string imageName)
	:DisplayableObject(pEngine)
	,player(player)
	,mx_position(worldXPos)
	,my_position(worldYPos)
{
	//printf("monster generate\n");
	playStage = (GamePlay*)stage;
	m_pTileManager = playStage->getTileManager();
	currMonster = &monster1;
	hOutlineW = 50;
	hOutlineH = 10;
	maxHealth = 100;
}


void Monster::virtDraw()
{
	genMonster();
	drawHP();
}

void Monster::virtDoUpdate(int iCurrentTime)
{

	if (dead) {
		setVisible(false);
		UndrawHUD();
		getEngine()->removeDisplayableObject(this);
		return;
	}
	detectCollision();

	PerformMovement();

	int x_now = getEngine()->getMouseXClickedDown();
	int y_now = getEngine()->getMouseYClickedDown();

}

void Monster::UndrawHUD() { //Undraw the text and health bars of enemies
	if (drawHealth)
		getEngine()->copyBackgroundPixels(hOutlineX, hOutlineY, hOutlineW, hOutlineH);
}

bool Monster::CanDraw(int x, int y, int w, int h) { //Checks to see if the Enemy is on screen
	return (w > 0 && x >= 0 && x < getEngine()->getWindowWidth() - w && y >= m_iDrawHeight * 2 && y < getEngine()->getWindowHeight() - h);
}

void Monster::PerformMovement() {};

void Monster::genMonster() {};

void Monster::detectCollision() {};

void Monster::drawHP() {};

int Monster::getXPosition()
{
	return mx_position;
}

int Monster::getYPosition()
{
	return my_position;
}


void Monster::randomMove(int&x, int&y,int& position)
{
	int dir = (rand() + x + y) % 4;
	int move = 80;

	if (requiredPos >= move) {
		requiredPos = 0;
		newChoice = dir;
	}
	else
	{
		newChoice = lastChoice;
	}
	switch (newChoice)
	{
	case 0:
		x -= 1;
		requiredPos++;
		position = 0;
		break;
	case 1:
		x += 1;
		requiredPos++;
		position = 1;
		break;
	case 2:
		y -= 1;
		requiredPos++;
		break;
	case 3:
		y += 1;
		requiredPos++;
		break;
	}
	lastChoice = newChoice;
}

void Monster::findPlayer(int&x,int&y)
{
	float distance[4];
	float sDistance[4];
	bool isMoveLeft = moveLEFT(x, y);
	bool isMoveUp=moveUP(x,y);

	int previousX, previousY, nowX, nowY;
	//if (isMoveLeft)
	//	cout << "left ";
	//else
	//	cout << "right ";

	//if (isMoveUp)
	//	cout << "Up ";
	//else
	//	cout << "down "<<endl;

	int iTileX = m_pTileManager->getMapXForScreenX(x);
	int iTileY = m_pTileManager->getMapYForScreenY(y);

	nowX = x;
	nowY = y;


	/*int a = playStage->GetMapValue(iTileX-1, iTileY);
	int b= playStage->GetMapValue(iTileX, iTileY);
	cout << "a:" << a << " b:" << b << endl;*/

	for (int i = 0; i < 4; i++)
		distance[i] = FLT_MAX;
	float greedyDist;

	if (iTileY - 1 >= 0)
		distance[UP] =(float) playStage->GetDistance(iTileX, iTileY - 1, player);
	//if (iTileY + 1 < playStage->GetMapHeight() - 1)
		distance[DOWN] = (float)playStage->GetDistance(iTileX, iTileY + 2, player);
	if (iTileX - 1 >= 0)
		distance[LEFT] = (float)playStage->GetDistance(iTileX - 1, iTileY , player);
//	if (iTileX + 1 < playStage->GetMapWidth() - 1)
		distance[RIGHT] =(float) playStage->GetDistance(iTileX + 2, iTileY, player);

	memcpy(sDistance, distance, sizeof(float) * 4);
	sort(sDistance, sDistance + 4);

	for (int i = 0; i < 4; i++) {
		greedyDist = sDistance[i];
		if (greedyDist == INT_MAX) {
			cout << "greedyDist==FLTMAX" << endl;
			continue;
		}
		if (distance[UP] == greedyDist && playStage->GetMapValue(iTileX, iTileY - 1) >= 3) {
			y--;
			return;
		}
		if (distance[DOWN] == greedyDist && playStage->GetMapValue(iTileX, iTileY + 2) >= 3 && playStage->GetMapValue(iTileX+2, iTileY + 2) >= 3) {
			y++;
			return;
		}
		if (distance[RIGHT] == greedyDist && playStage->GetMapValue(iTileX + 2, iTileY) >= 3 && playStage->GetMapValue(iTileX + 2, iTileY+2) >= 3){
			x++;
			return;
		}
		if (distance[LEFT] == greedyDist && playStage->GetMapValue(iTileX - 1, iTileY) >= 3) {
			x--;
			return;
		}
		previousX = x;
		previousY = y;
	}
}


bool Monster::moveUP(int x, int y) {
	int iTileX = m_pTileManager->getMapXForScreenX(x);
	int iTileY = m_pTileManager->getMapYForScreenY(y);

	int up = 0,down=0;

	while (playStage->GetMapValue(iTileX, iTileY -up) >= 3 && iTileY-up>0)
		up++;

	while (playStage->GetMapValue(iTileX, iTileY +down) >= 3)
		down++;

	if (up - down > 0)
		return true;
	else
		return false;

}

bool Monster::moveLEFT(int x, int y) {
	int iTileX = m_pTileManager->getMapXForScreenX(x);
	int iTileY = m_pTileManager->getMapYForScreenY(y);

	int left = 0, right = 0;

	while (playStage->GetMapValue(iTileX-left, iTileY) >= 3 && iTileX-left>0)
		left++;

	while (playStage->GetMapValue(iTileX+right, iTileY) >= 3)
		right++;

	if (left - right > 0)
		return true;
	else
		return false;

}
