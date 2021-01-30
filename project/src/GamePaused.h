#pragma once
#include "Stage.h"
#include "Scyyz4Engine.h"

class GamePaused :
	public Stage
{
public:
	GamePaused(Scyyz4Engine* pEngine);
	~GamePaused() {}
	virtual void virtDrawStringsUnderneath();
	virtual void virtDrawStringsOnTop();
	virtual void virtKeyDown(int iKeyCode);

private:
	Scyyz4Engine* pEngine;
};

