#include "header.h"
#include "GameOver.h"
#include "Scyyz4Engine.h"
#include "Audio.h"

GameOver::GameOver(Scyyz4Engine* pEngine) : m_engine(pEngine)
{
	//printf("()over generated\n");
	//Audio::stopBgm();
	overImage = ImageManager::loadImage("images/gameover1.png", true);
}


GameOver::~GameOver()
{
//	printf(")(over released\n");
}

void GameOver::virtDrawStringsOnTop() {
	m_engine->lockBackgroundForDrawing();
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	
	if (overSelection == 0)
		m_engine->drawForegroundString(550, 600, "YES", 0xFF0000, NULL);
	else
		m_engine->drawForegroundString(550, 600, "YES", 0xFFFFFF, NULL);

	if (overSelection == 1)
		m_engine->drawForegroundString(650, 600, "NO", 0xFF0000, NULL);
	else
		m_engine->drawForegroundString(650, 600, "NO", 0xFFFFFF, NULL);

	m_engine->unlockBackgroundForDrawing();	
}

void GameOver::virtSetupBackgroundBuffer() {
	printf("GameOver:  draw\n");
	Audio::playBgm(0);
	//m_engine->lockBackgroundForDrawing();
	int cWidth = m_engine->getWindowWidth();
	int cHeight = m_engine->getWindowHeight();

	overImage.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 0, 0, cWidth, cHeight);
	//m_engine->unlockBackgroundForDrawing();
}

void GameOver::ProcessMouseMovement(int x, int y) { //Change menu selection based on mouse location
	if (x >= 550 && y >= 600 && x < 600 && y < 620) {
		overSelection = 0;
		m_engine->redrawDisplay();
	}
	if (x >= 650 && y >= 600 && x < 700 && y < 620) {
		overSelection = 1;
		m_engine->redrawDisplay();
	}
};

void GameOver::virtMouseDown(int button, int x, int y) {
	printf("overe: process input\n");
	if (button != 1)
		return;

	if (x >= 550 && y >= 600 && x < 600 && y < 620) {
		overSelection = 0;
		m_engine->redrawDisplay();
	}
	if (x >= 650 && y >= 600 && x < 700 && y < 620) {
		overSelection = 1;
		m_engine->redrawDisplay();
	}


	if (overSelection == 0)
			m_engine->StageSwitch(6);
	else
		exit(0);
}

void GameOver::virtKeyDown(int keyCode) {
	switch (keyCode) {
	case SDLK_RIGHT:
		if (overSelection < 1)
			overSelection++;
		break;
	case SDLK_LEFT:
		if (overSelection > 0)
			overSelection--;
		break;
	case SDLK_RETURN:
		if (overSelection == 0)
				m_engine->StageSwitch(6);
		else
			exit(0);
		break;
	case SDLK_ESCAPE:
		exit(0);
		break;
	}

	//selectionY = selectionBaseY + (overSelection * 25);
	m_engine->redrawDisplay();
}

