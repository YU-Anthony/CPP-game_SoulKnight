#pragma once
#include "Stage.h"
#include "SimpleImage.h"
class GameOver :
	public Stage
{
public:
	GameOver(Scyyz4Engine* pEngine);
	~GameOver();

	void virtDrawStringsOnTop();
	char** GetBackground() { return background; }
	void virtKeyDown(int keyCode);
	void virtMouseDown(int button, int x, int y);
	void ProcessMouseMovement(int x, int y);
	void virtSetupBackgroundBuffer();

protected:
	Scyyz4Engine* m_engine;
	char** background;
	int overSelection = 0;
	int selectionBaseY = 340;
	//int selectionY = selectionBaseY;

private:
	SimpleImage overImage;
};
