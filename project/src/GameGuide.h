#pragma once
#include "Stage.h"
#include "Scyyz4Engine.h"

class Scyyz4Engine;

class GameGuide : public Stage
{
public:
	GameGuide(Scyyz4Engine* pEngine);
	~GameGuide();
	void virtSetupBackgroundBuffer();
	void virtMouseDown(int button, int x, int y);
	void virtKeyDown(int iKeyCode);
	void virtMainLoopDoBeforeUpdate();

private:
	Scyyz4Engine* p_mainEngine;
	SimpleImage guideUI;
	SimpleImage sg1;
};
