#pragma once
#include "Stage.h"
#include "SimpleImage.h"
#include "DrawingFilters.h" 

class Scyyz4Engine;
class BaseEngine;

class Menu :
	public Stage
{
public:
	Menu(Scyyz4Engine* pEngine);
	~Menu() 
	{
		//printf(")(menu released\n");
	};

	void virtDrawStringsOnTop();
	void virtKeyDown(int keyCode);
	void virtMouseDown(int button, int x, int y);
	void virtMouseWheel(int x, int y, int which, int timestamp);
	void ProcessMouseMovement(int x, int y);
	void virtSetupBackgroundBuffer();


protected:
	Scyyz4Engine* m_engine;
	BaseEngine base_engine;
	int menuSelection = 0;
	int selectionBaseY = 340;
	int selectionY = selectionBaseY;

private:
	SimpleImage titleImage;
	int startTime = 0;

};

