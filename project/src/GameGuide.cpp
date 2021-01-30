#include "header.h"
#include "Scyyz4Engine.h"
#include "GameGuide.h"

using namespace std;


GameGuide::GameGuide(Scyyz4Engine* pEngine)
	:Stage(pEngine)
	, p_mainEngine(pEngine)
	, guideUI(pEngine->loadImage("images/gameGuide.png", true))

{
	sg1 = ImageManager::loadImage("images/soliders.png", true);
	p_mainEngine->sf1.createSurface(1300, 800);
	p_mainEngine->sf2.createSurface(1300, 800);
	p_mainEngine->sf3.createSurface(1300, 800);
	p_mainEngine->sf4.createSurface(1300, 800);
	p_mainEngine->sf5.createSurface(1300, 800);
	p_mainEngine->sf6.createSurface(1300, 800);
	p_mainEngine->sf7.createSurface(1300, 800);
	p_mainEngine->sf8.createSurface(1300, 800);
	p_mainEngine->sf9.createSurface(1300, 800);
	//printf("()Guide generate\n");
}

GameGuide::~GameGuide()
{
	//printf(")(Guide release\n");
}

void GameGuide::virtSetupBackgroundBuffer()
{
//	printf("Guide setback\n");
	p_mainEngine->fillBackground(0xeffaff);
	p_mainEngine->lockBackgroundForDrawing();


	p_mainEngine->sf1.fillSurface(0xeffaff);
	p_mainEngine->sf2.fillSurface(0xeffaff);
	p_mainEngine->sf3.fillSurface(0xeffaff);
	p_mainEngine->sf4.fillSurface(0xeffaff);
	p_mainEngine->sf5.fillSurface(0xeffaff);
	p_mainEngine->sf6.fillSurface(0xeffaff);
	p_mainEngine->sf7.fillSurface(0xeffaff);
	p_mainEngine->sf8.fillSurface(0xeffaff);
	p_mainEngine->sf9.fillSurface(0xeffaff);

	p_mainEngine->sf1.mySDLLockSurface();
	p_mainEngine->sf2.mySDLLockSurface();
	p_mainEngine->sf3.mySDLLockSurface();
	p_mainEngine->sf4.mySDLLockSurface();
	p_mainEngine->sf5.mySDLLockSurface();
	p_mainEngine->sf6.mySDLLockSurface();
	p_mainEngine->sf7.mySDLLockSurface();
	p_mainEngine->sf8.mySDLLockSurface();
	p_mainEngine->sf9.mySDLLockSurface();

	guideUI.renderImage(p_mainEngine->getBackgroundSurface(), 0, 0, 0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());

	sg1.renderImageWithMask(&p_mainEngine->sf1, sg1.getWidth() / 9 * 0, sg1.getHeight() / 2,
		1200, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf2, sg1.getWidth() / 9 * 1, sg1.getHeight() / 2,
		1198, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf3, sg1.getWidth() / 9 * 2, sg1.getHeight() / 2,
		1196, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf4, sg1.getWidth() / 9 * 3, sg1.getHeight() / 2,
		1194, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf5, sg1.getWidth() / 9 * 4, sg1.getHeight() / 2,
		1192, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf6, sg1.getWidth() / 9 * 5, sg1.getHeight() / 2,
		1190, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf7, sg1.getWidth() / 9 * 6, sg1.getHeight() / 2,
		1188, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf8, sg1.getWidth() / 9 * 7, sg1.getHeight() / 2,
		1186, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);
	sg1.renderImageWithMask(&p_mainEngine->sf9, sg1.getWidth() / 9 * 8, sg1.getHeight() / 2,
		1184, 700, sg1.getWidth() / 9, sg1.getHeight() / 2);

	p_mainEngine->sf1.mySDLUnlockSurface();
	p_mainEngine->sf2.mySDLUnlockSurface();
	p_mainEngine->sf3.mySDLUnlockSurface();

	p_mainEngine->sf4.mySDLUnlockSurface();

	p_mainEngine->sf5.mySDLUnlockSurface();

	p_mainEngine->sf6.mySDLUnlockSurface();

	p_mainEngine->sf7.mySDLUnlockSurface();

	p_mainEngine->sf8.mySDLUnlockSurface();
	p_mainEngine->sf9.mySDLUnlockSurface();
	p_mainEngine->unlockBackgroundForDrawing();

	p_mainEngine->copyBackgroundPixels(0, 0, p_mainEngine->getWindowWidth(), p_mainEngine->getWindowHeight());
	
	p_mainEngine->redrawDisplay();
}

void GameGuide::virtMouseDown(int button, int x, int y) {
	if (button != 1)
		return;

	if (x >= 1120 && y >= 630 && x < 1220&& y < 730) {
		p_mainEngine->StageSwitch(6);
		p_mainEngine->redrawDisplay();
	}

}

void GameGuide::virtKeyDown(int iKeyCode)
{

	if (iKeyCode == SDLK_RETURN)
	{
		p_mainEngine->StageSwitch(6);
		p_mainEngine->virtSetupBackgroundBuffer();
		p_mainEngine->redrawDisplay();
	}
}

void GameGuide::virtMainLoopDoBeforeUpdate() {
	
	int iTick = p_mainEngine->getModifiedTime() / 100; // 1 per 100ms
	int iFrame = iTick % 10;
	
	switch (iFrame) {
	case 0:
		p_mainEngine->setBackgroundSurface(m_engine->getBackgroundSurface());
		break;
	case 1:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf1);
		break;
	case 2:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf2);
		break;
	case 3:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf3);
		break;
	case 4:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf4);
		break;
	case 5:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf5);
		break;
	case 6:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf6);
		break;
	case 7:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf7);
		break;
	case 8:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf8);
		break;
	case 9:
		p_mainEngine->setBackgroundSurface(&p_mainEngine->sf9);
		break;

	}
	virtSetupBackgroundBuffer();
}