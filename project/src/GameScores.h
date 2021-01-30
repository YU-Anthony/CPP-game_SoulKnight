#pragma once
#include "Stage.h"
#include "Scyyz4Engine.h"

class GameScores : public Stage
{
public:
	GameScores(Scyyz4Engine* pEngine);
	~GameScores();
	//void Draw();
	void virtSetupBackgroundBuffer() ;
	int virtInitialiseObjects() ;
	void virtDrawStringsOnTop() ;
	void virtKeyDown(int iKeyCode) ;

private:
	Scyyz4Engine* p_mainEngine;
	SimpleImage scoreUI;
};
