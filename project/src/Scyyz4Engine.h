#pragma once
#include "BaseEngine.h"
#include "Stage.h"
#include "Menu.h"
#include "Scyyz4TileManager.h"
#include <map>
#include "DrawingSurface.h"


class Scyyz4Engine :
	public BaseEngine
{
public:
	Scyyz4Engine();
	~Scyyz4Engine();

	virtual void virtSetupBackgroundBuffer() override;
	void UnDrawStrings();
	void virtKeyDown(int iKeyCode);
	void StageSwitch(int stageCode);

	virtual int virtInitialise() override;
	//int virtInitialiseObjects() override;
	void virtMainLoopDoBeforeUpdate() override;
	void copyAllBackgroundBuffer() override;
	void virtMouseMoved(int iX, int iY) override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtMouseWheel(int x, int y, int which, int timestamp);
	void virtDrawStringsOnTop() override;

	int getPlayingTime()
	{
		return getModifiedTime() - startPlayTime;
	}

	int getStartTime()
	{
		return startTime;
	}

	void compress() {m_filterScaling.compress();
	}

	void stretch() { m_filterScaling.stretch();
	}


	void changeOffset(int x, int y) 
	{
		
		m_filterTranslation.changeOffset(x, y);
		virtSetupBackgroundBuffer();
		redrawDisplay();
	}

	FilterPointsTranslation getFilterTranslation() { return m_filterTranslation;
	}
	
	void setBackgroundSurface(DrawingSurface* ds) {
		m_pBackgroundSurface = ds;
	}

	DrawingSurface sf1;
	DrawingSurface sf2;
	DrawingSurface sf3;
	DrawingSurface sf4;
	DrawingSurface sf5;
	DrawingSurface sf6;
	DrawingSurface sf7;
	DrawingSurface sf8;
	DrawingSurface sf9;

private:
	int startPlayTime;
	int startTime;
	int lastStageCode;
	FilterPointsScaling m_filterScaling;
	FilterPointsTranslation m_filterTranslation;
	Menu* menu;

	Stage* currentStage;

	Stage* stages[10];
};