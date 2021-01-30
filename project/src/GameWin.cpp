#include "header.h"
#include "GameWin.h"
#include <fstream>
#include <iostream>
#include "Audio.h"

using namespace std;

extern map <int, string, less<int>> highscores;
extern int finalTime;
extern bool isNewRecord;
extern int gameLevel;
//int gameLevel = 1;

GameWin::GameWin(Scyyz4Engine* pEngine)
	:Stage(pEngine)
	,p_mainEngine(pEngine)
	,enterUI(pEngine->loadImage("images/entername.png", true/* keep it loaded*/))
{
	//printf("()win generate\n");
}

GameWin::~GameWin(){};



void GameWin::virtSetupBackgroundBuffer()
{
	p_mainEngine->copyBackgroundPixels(0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());
	Audio::playBgm(0);
	name = " ";
	p_mainEngine->fillBackground(0xeffaff);
	enterUI.renderImage(p_mainEngine->getBackgroundSurface(), 0, 0, 0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());
	p_mainEngine->redrawDisplay();
	virtInitialiseObjects();
}

int GameWin::virtInitialiseObjects()
{
	printf("GameWin: initialise objects\n");
	p_mainEngine->drawableObjectsChanged();
	p_mainEngine->destroyOldObjects(true);

	return 0;
}


void GameWin::virtKeyDown(int iKeyCode)
{
	if ((iKeyCode >= 'A' && iKeyCode <= 'z') || iKeyCode == SDLK_SPACE)
	{
		name.push_back(iKeyCode);
	}
	if (iKeyCode == SDLK_BACKSPACE)
	{
		if (name.size() > 1)
		{
			name.erase(name.end() - 1);
		}
	}
	p_mainEngine->redrawDisplay();
}

void GameWin::virtDrawStringsOnTop()
{
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	p_mainEngine->drawForegroundString(550, 450, name.data(), 0x8976b5, NULL);

	p_mainEngine-> drawForegroundString(600, 600, "Submit", 0xe6af04, NULL);
}

void GameWin::virtMouseDown(int iButton, int iX, int iY)
{
	p_mainEngine->lockBackgroundForDrawing();
	if (iX >= 600 && iX <= 670)
	{
		if (iY >= 600 && iY <= 670)
		{
			if (isNewRecord == true) {
				name = name.substr(1, name.length() - 1);
				highscores[finalTime] = name;
				printf("final time:%d\n", finalTime);
				isNewRecord = false;
			}
			// write to file
			ofstream inputfile;
			string ScoreListPath = "resources/highscorelist1.txt";
	

			inputfile.open(ScoreListPath);
			if (!inputfile) {
				cerr << "Failed to open file " << ScoreListPath << endl;
				exit(0);
			}
			else {
				for (const auto &record : highscores)
				{
					inputfile << record.first << " " << record.second << endl;
				}
			}
			inputfile.close();
			p_mainEngine->StageSwitch(7);
			p_mainEngine->virtSetupBackgroundBuffer();
		}
	}
	p_mainEngine->unlockBackgroundForDrawing();
}