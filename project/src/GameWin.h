#pragma once
#include "Stage.h"
#include "Scyyz4Engine.h"


class GameWin : public Stage
{
public:
	GameWin(Scyyz4Engine* pEngine);
	~GameWin();
	//void Draw();
	virtual void virtSetupBackgroundBuffer();
	virtual void virtDrawStringsOnTop();
	virtual void virtKeyDown(int iKeyCode);
	int virtInitialiseObjects();
	virtual void virtMouseDown(int iButton, int iX, int iY);

private:
	std::string name;
	Scyyz4Engine* p_mainEngine;
	SimpleImage	enterUI;
};