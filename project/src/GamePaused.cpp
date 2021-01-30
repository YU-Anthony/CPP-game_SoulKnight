#include "header.h"
#include "GamePaused.h"


GamePaused::GamePaused(Scyyz4Engine* pEngine)
	:Stage(pEngine)
	,pEngine(pEngine)
{
	//printf("()paused generate\n");
}


void GamePaused::virtDrawStringsUnderneath()
{
	// Build the string to print
	char buf[128];
	sprintf(buf, "Life");
	pEngine->drawForegroundString(20, 10, buf, 0xa63a45, NULL);

}

void GamePaused::virtDrawStringsOnTop()
{
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	// Build the string to print
	//char buf[128];
	//sprintf(buf, "Time %3d", pEngine->getModifiedTime() / 1000 - 0);
	//pEngine->drawForegroundString(pEngine->getWindowWidth() - 150, 10, buf, 0x89afab, NULL);

	pEngine->drawForegroundString(pEngine->getWindowWidth() / 2 - 250, pEngine->getWindowHeight() / 2, "Paused. Press 'shift' to continue", 0x693e0a, m_engine->getFont("resources/m5x7.ttf", 55));
}

void GamePaused::virtKeyDown(int iKeyCode)
{

	// NEW SWITCH on current state
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		exit(0);
		break;
	case SDLK_LSHIFT:
	case SDLK_RSHIFT: // shift Pauses
		pEngine->unpause();
		pEngine->StageSwitch(0);
		pEngine->redrawDisplay();
		break;
	}
}