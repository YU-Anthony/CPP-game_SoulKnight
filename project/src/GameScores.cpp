#include "header.h"
#include "GameScores.h"

using namespace std;

extern map <int, string, less<int>> highscores;
extern int finalTime;
extern bool isNewRecord;
extern int gameLevel;

GameScores::GameScores(Scyyz4Engine* pEngine)
	:Stage(pEngine)
	,p_mainEngine(pEngine)
	,scoreUI(pEngine->loadImage("images/highscore.png", true))

{
	//printf("()scores generate\n");
}

GameScores::~GameScores()
{
	//printf(")(scores release\n");
}



int GameScores::virtInitialiseObjects()
{
	p_mainEngine->drawableObjectsChanged();
	p_mainEngine->destroyOldObjects(true);

	return 0;
}

void GameScores::virtSetupBackgroundBuffer()
{
	virtInitialiseObjects();
	p_mainEngine->fillBackground(0xeffaff);
	//p_mainEngine->copyBackgroundPixels(0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());
	scoreUI.renderImage(p_mainEngine->getBackgroundSurface(), 0, 0, 0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());
	p_mainEngine->redrawDisplay();
}

void GameScores::virtDrawStringsOnTop()
{
	int hight = 360;
	//int i = level - 1;
	char buff[128];
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), 50);
	p_mainEngine->drawForegroundString(p_mainEngine->getWindowWidth() / 2 - 90, 320, "High Scores", 0x26597c, m_engine->getFont("resources/m5x7.ttf", 40));
	for (const auto &record : highscores) {

		sprintf(buff, "Name: %s, Time: %d", record.second.c_str(), record.first);
		p_mainEngine->drawForegroundString(p_mainEngine->getWindowWidth() / 2 - 130, hight, buff, 0x89afab, m_engine->getFont("resources/m5x7.ttf", 40));
		hight = hight + 30;
	}
	
	p_mainEngine->drawForegroundString(450, 550, "Press 'Enter' to start screen", 0x46748e, m_engine->getFont("resources/m5x7.ttf", 50));;

	
}

void GameScores::virtKeyDown(int iKeyCode)
{

	if (iKeyCode == SDLK_RETURN)
	{
		p_mainEngine->StageSwitch(6);
		p_mainEngine->virtSetupBackgroundBuffer();
		p_mainEngine->redrawDisplay();
	}
}