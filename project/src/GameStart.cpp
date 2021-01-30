#include "header.h"
#include "GameStart.h"

#include "ImageManager.h"

#include "Scyyz4TileManager.h"

#include "DisplayableObject.h"

#include "ImageObject.h"
#include "MappableImageObject.h"
#include "BouncingObject.h"


GameStart::GameStart(Scyyz4Engine* pEngine) :
	m_engine(pEngine)
	, rotator(0.0), m_iOffset(0)
{
	//printf("()start generate\n");
	bkImage = ImageManager::loadImage("images/startBK.png", true);
}

void GameStart::virtSetupBackgroundBuffer()
{
	m_engine->fillBackground(0x000000);
	virtInitialiseObjects();

	m_engine->lockBackgroundForDrawing();

	//bkImage.renderImageWithMask(m_engine->getBackgroundSurface(), 0, 0, 0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	m_engine->copyBackgroundPixels(0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());

	SimpleImage starfield = ImageManager::loadImage("images/starfield.png", true);
	starfield.renderImage(m_engine->getBackgroundSurface(), 0, 0, 0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight());
	m_engine->unlockBackgroundForDrawing();


}

int GameStart::virtInitialiseObjects()
{
	printf("GameStart debug: background update\n");
	// Destroy any existing objects
	m_engine->drawableObjectsChanged();
	m_engine->destroyOldObjects(true);

	m_engine->createObjectArray(1);

	ob = new MappableImageObject(&rotator, m_engine->getWindowWidth()/2-20, m_engine->getWindowHeight() / 2 - 20, m_engine, "images/rotate1.png", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	m_engine->storeObjectInArray(0, ob);

	copyAllBackgroundBuffer();
	return 0;
}

void GameStart::virtMainLoopDoBeforeUpdate()
{
	++m_iOffset;
	int iOffset = m_engine->getModifiedTime() / 5;

	rotator.setRotation((double)iOffset / 100.0);

	m_engine->redrawDisplay();
	
}


void GameStart::copyAllBackgroundBuffer()
{
	DrawingSurface* m_pBackgroundSurface = m_engine->getBackgroundSurface();
	DrawingSurface* m_pForegroundSurface = m_engine->getForegroundSurface();

	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, m_engine->getWindowWidth(), m_engine->getWindowHeight(), m_iOffset, 0);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, m_engine->getWindowHeight() - m_iOffset, m_engine->getWindowWidth(), m_engine->getWindowHeight(), m_iOffset - m_engine->getWindowWidth(), 0);
}

void GameStart::virtMouseDown(int button, int x, int y) {
	if (button != 1)
		return;

	if (x >= m_engine->getWindowWidth()-20 && y >= m_engine->getWindowHeight() - 20 && x < m_engine->getWindowWidth()+100 && y < m_engine->getWindowHeight()+100) {
		printf("gamestart debug--------\n");
	}
	m_engine->StageSwitch(0);
}

bool GameStart::mapCoordinates(double& x, double& y, const SimpleImage& image)
{
	return true;
}