#include "header.h"
#include "Menu.h"
#include "Scyyz4Engine.h"
#include "BaseEngine.h"
#include "Audio.h"

Menu::Menu(Scyyz4Engine* pEngine) :
	m_engine(pEngine)
	,base_engine()
	,titleImage(ImageManager::loadImage("images/SoulKnight.png", true))
{
	//printf("()menu generate\n");
	Audio::playBgm(0);
}



void Menu::ProcessMouseMovement(int x, int y){ //Change menu selection based on mouse location
	if (x >= 575 && y >= 700 && x < 800 && y < 740){
		menuSelection = 0;
		m_engine->redrawDisplay();
}
	if (x >= 275 && y >= 700 && x < 500 && y < 740){
		menuSelection = 1;
		m_engine->redrawDisplay();
	}
	if (x >= 875 && y >= 700 && x < 1100 && y < 740){
		menuSelection = 2;
		m_engine->redrawDisplay();
	}

}


void Menu::virtDrawStringsOnTop(){
	//printf("Menu: draw strings\n");
	m_engine->lockBackgroundForDrawing();
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), 50);
	if (menuSelection == 0)
		m_engine->drawForegroundString(575, 700, "NEW GAME", 0xFFFFFF, m_engine->getFont("resources/m5x7.ttf", 55));
	else
		m_engine->drawForegroundString(575, 700, "NEW GAME", 0x000000, m_engine->getFont("resources/m5x7.ttf", 40));

	if (menuSelection == 1)
		m_engine->drawForegroundString(275, 700, "LOAD GAME", 0xFFFFFF, m_engine->getFont("resources/m5x7.ttf", 55));
	else
		m_engine->drawForegroundString(275, 700, "LOAD GAME", 0x000000, m_engine->getFont("resources/m5x7.ttf", 40));

	if (menuSelection == 2)
	m_engine->drawForegroundString(875, 700, "QUIT", 0xFFFFFF, m_engine->getFont("resources/m5x7.ttf", 55));
	else
		m_engine->drawForegroundString(875, 700, "QUIT", 0x000000, m_engine->getFont("resources/m5x7.ttf", 40));

	m_engine->unlockBackgroundForDrawing();
}

void Menu::virtSetupBackgroundBuffer(){
	printf("Menu:  draw\n");
	m_engine->lockBackgroundForDrawing();
	m_engine->fillBackground(0x000000);
	int cWidth = m_engine->getWindowWidth();
	int cHeight = m_engine->getWindowHeight();

	titleImage.renderImage(m_engine->getBackgroundSurface(), 0, 0,0,0, cWidth, cHeight);

	SimpleImage help = ImageManager::loadImage("images/help.png", true).resizeTo(105,70);
	help.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 1100, 60, help.getWidth(), help.getHeight());

	m_engine->unlockBackgroundForDrawing();
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
}

void Menu::virtMouseDown(int button, int x, int y) {
	printf("Menue: process input\n");
	if (button != 1)
		return;

	if (x >= 575 && y >= 700 && x < 800 && y < 740) {
		Audio::stopBgm();
		menuSelection = 0;
		startTime = m_engine->getModifiedTime() / 1000;
		m_engine->StageSwitch(8);
		m_engine->redrawDisplay();
	}
	if (x >= 275 && y >= 700 && x < 500 && y < 740) {
		menuSelection = 1;
		startTime = m_engine->getModifiedTime() / 1000;
		m_engine->StageSwitch(1);
		m_engine->redrawDisplay();
	}
	if (x >= 875 && y >= 700 && x < 1100 && y < 740) {
		menuSelection = 2;
		m_engine->redrawDisplay();
		exit(0);
	}
	if (x >= 1100 && y >= 60 && x < 1200 && y < 130) {
		m_engine->StageSwitch(9);
	}

}

void Menu::virtKeyDown(int keyCode){
	switch (keyCode){
	case SDLK_RIGHT:
		if (menuSelection == 0)
			menuSelection = 2;
		else if (menuSelection == 1)
			menuSelection = 0;
		else if(menuSelection == 2)
			menuSelection = 1;
		//if (menuSelection < 2)
		//	menuSelection++;
		break;
	case SDLK_LEFT:
		if (menuSelection == 0)
			menuSelection = 1;
		else if (menuSelection == 1)
			menuSelection = 2;
		else if (menuSelection == 2)
			menuSelection = 0;
		/*if (menuSelection > 0)
			menuSelection--;*/
		break;
	case SDLK_RETURN:
		//Audio::stopBgm();
		if(menuSelection == 0)
			m_engine->StageSwitch(0);
		else
			m_engine->StageSwitch(menuSelection);
		break;
	case SDLK_ESCAPE:
		exit(0);
		break;
	case SDLK_w:
		m_engine->changeOffset(0,-15);
		break;
	case SDLK_a:
		m_engine->changeOffset(-15, 0);
		break;
	case SDLK_s:
		m_engine->changeOffset(0, 15);
		break;
	case SDLK_d:
		m_engine->changeOffset(15, 0);
		break;

	}

	selectionY = selectionBaseY + (menuSelection * 25);
	m_engine->redrawDisplay();
}

void Menu::virtMouseWheel(int x, int y, int which, int timestamp) {
	int iOldCentreX = m_engine->convertClickedToVirtualPixelXPosition(m_engine->getWindowWidth() / 2);
	int iOldCentreY = m_engine->convertClickedToVirtualPixelYPosition(m_engine->getWindowHeight() / 2);

	if (y < 0)
		m_engine->compress();
	else if (y > 0)
		m_engine->stretch();

	int iNewCentreX = m_engine->convertClickedToVirtualPixelXPosition(m_engine->getWindowWidth() / 2);
	int iNewCentreY = m_engine->convertClickedToVirtualPixelYPosition(m_engine->getWindowHeight() / 2);

	m_engine->changeOffset(iNewCentreX - iOldCentreX, iNewCentreY - iOldCentreY);
	m_engine->virtSetupBackgroundBuffer();

	m_engine->redrawDisplay();
}