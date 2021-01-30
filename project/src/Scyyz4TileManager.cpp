#include "header.h"
#include "Scyyz4TileManager.h"
// a-0, b-1, c-2, d-3, e-4,f-5,g-6,h-7,i-8,j-9,
//k-10,l-11,m-12,n-13,o-14,p-15,q-16,r-17,s-18,t-19,
//u-20,v-21,w-22,x-23,y-24,z-25




void Scyyz4TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int value = getMapValue(iMapX, iMapY);

	switch (value)
	{
	case 0: //SPIDER WEB (a)
		floorShadow.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 1: //BLOCKING BRICK (b)
		wallUp.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 2: //BLOCKING BRICK (c)
		wallNormal.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 3: //BLOCKING BRICK (d)
		sand.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 4: //WATER (e)
		dirtyWater.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 5: //GRASS (f)
		lava.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 8: //BRICK (i)
		treasure.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 9: //BRICK (i)
		diamond.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 10: //BRICK (i)
		stair.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 11: //(l)
		water1.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 12: //(m)
		water2.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 13: //(n)
		water3.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 14: //(o)
		water4.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 15: //(p)
		waterUp.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 16: //(q)
		waterDown.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 17: //(r)
		waterLeft.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	case 18: // (s)
		waterRight.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, getTileWidth(), getTileHeight());
		break;
	}
}

int Scyyz4TileManager::GetValueAt(int x, int y) {
	int tileX, tileY;
	tileX = x / getTileWidth();
	tileY = y / getTileHeight();

	return getMapValue(tileX, tileY);
}