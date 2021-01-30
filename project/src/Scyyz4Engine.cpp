#include "header.h"
#include "Scyyz4Engine.h"
#include "ImageManager.h"
#include "Scyyz4Object.h"
#include "ImageManager.h"

#include "Scyyz4TileManager.h"
#include "GamePlay.h"
#include "GameOver.h"
#include "GamePaused.h"
#include "GameWin.h"
#include "GameScores.h"
#include "GameStart.h"
#include "GameGuide.h"

using namespace std;

extern map <int, string> highscores;

Scyyz4Engine::Scyyz4Engine()
	: BaseEngine()
	, startPlayTime(0)
	, m_filterScaling(0, 0, this), m_filterTranslation(0, 0, &m_filterScaling)
	,sf1(this), sf2(this), sf3(this), sf4(this), sf5(this), sf6(this), sf7(this), sf8(this), sf9(this)
{
	stages[0] = new GamePlay(this, false);
	stages[1] = new GamePlay(this, true);
	stages[3] = new GameOver(this);
	stages[4] = new GamePaused(this);
	stages[5] = new GameWin(this);
	stages[6] = new Menu(this);
	stages[7] = new GameScores(this);
	stages[8] = new GameStart(this);
	stages[9] = new GameGuide(this);

	menu = (Menu*)stages[6];
	currentStage = stages[6];
	//currentStage = menu;
}

Scyyz4Engine::~Scyyz4Engine()
{


	delete (GamePlay*)stages[0];
	
	//delete (GamePlay*)stages[1];
	if(stages[1]!=NULL)
		delete (GamePlay*)stages[1];
	delete (GameOver*)stages[3];
	delete (GamePaused*)stages[4];
	delete (GameWin*)stages[5];
	delete (Menu*)stages[6];
	delete (GameScores*)stages[7];
	delete (GameStart*)stages[8];
	delete (GameGuide*)stages[9];

	//delete s_tiles;
	highscores.clear();

}



void Scyyz4Engine::virtSetupBackgroundBuffer()
{
		currentStage->virtSetupBackgroundBuffer();
}

void Scyyz4Engine::virtMainLoopDoBeforeUpdate() {
	currentStage->virtMainLoopDoBeforeUpdate();
	this->copyBackgroundPixels(0, 0, this->getWindowWidth(), this->getWindowHeight());
}

void Scyyz4Engine::copyAllBackgroundBuffer()
{
	currentStage->copyAllBackgroundBuffer();
	
}

int Scyyz4Engine::virtInitialise()
{
	getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);

	return BaseEngine::virtInitialise();
}


void Scyyz4Engine::virtDrawStringsOnTop() {
	currentStage->virtDrawStringsOnTop();
}

void Scyyz4Engine::UnDrawStrings() {
	currentStage->UndrawStrings();
}


void Scyyz4Engine::virtMouseDown(int iButton, int iX, int iY) {
	currentStage->virtMouseDown(iButton, iX, iY);
}

void  Scyyz4Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	currentStage->virtMouseWheel(x, y, which, timestamp);
}

void Scyyz4Engine::virtMouseMoved(int iX, int iY) {
	currentStage->ProcessMouseMovement(iX, iY);
}

void Scyyz4Engine::virtKeyDown(int iKeyCode) {
	currentStage->virtKeyDown(iKeyCode);
}

void Scyyz4Engine::StageSwitch(int stageCode) {

	if (stageCode == 2) {
		printf("Game Exit\n");
		exit(0);
	}
	/*if (stageCode == 1) {
		stages[1] = new GamePlay(this, true);
	}*/
	int isPaused=0;
	
	if (lastStageCode==4) {
			isPaused = 1;
	}
	if(stageCode ==1)
		startTime = this->getModifiedTime() / 1000;
	if (lastStageCode == 8) {
		startTime = this->getModifiedTime()/1000;
	}

	currentStage = stages[stageCode];
	if (stageCode == 0 && isPaused == 1) {
		printf("is Paused\n");
	}
	else {
		lockAndSetupBackground();
	}

	lastStageCode = stageCode;
	redrawDisplay();
}

