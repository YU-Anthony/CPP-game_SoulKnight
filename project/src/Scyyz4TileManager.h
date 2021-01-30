#pragma once
#include "TileManager.h"


class Sprite;
class Scyyz4Engine;

class Scyyz4TileManager :
	public TileManager
{
public:
	Scyyz4TileManager::Scyyz4TileManager()
		: TileManager(30, 30)
	{
		wallUp = ImageManager::loadImage("images/wall_up.png", true);
		wallNormal = ImageManager::loadImage("images/wall_normal.png", true);
		floorNormal = ImageManager::loadImage("images/floor_normal.png", true);
		floorDark = ImageManager::loadImage("images/floor_dark.png", true);
		floorShadow = ImageManager::loadImage("images/floor_shadow.png", true);
		dirtyWater = ImageManager::loadImage("images/dirty_water.png", true);
		treasure = ImageManager::loadImage("images/treasure.png", true);
		diamond = ImageManager::loadImage("images/diamond.png", true);
		stair = ImageManager::loadImage("images/stair.png", true);
		sand = ImageManager::loadImage("images/sand.png", true);
		lava = ImageManager::loadImage("images/lava.png", true);


		water1 = ImageManager::loadImage("images/water1.png", true);
		water2 = ImageManager::loadImage("images/water2.png", true);
		water3 = ImageManager::loadImage("images/water3.png", true);
		water4 = ImageManager::loadImage("images/water4.png", true);
		waterUp = ImageManager::loadImage("images/water_up.png", true);
		waterLeft = ImageManager::loadImage("images/water_left.png", true);
		waterRight = ImageManager::loadImage("images/water_right.png", true);
		waterDown = ImageManager::loadImage("images/water_down.png", true);
		printf("<> tile generate\n");

	}

	~Scyyz4TileManager(void) 
	{
		printf("><tile release\n");
	};


	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;

	int GetValueAt(int x, int y);

private:
	Scyyz4Engine* m_engine;



	SimpleImage wallUp;
	SimpleImage wallNormal;
	SimpleImage floorNormal;
	SimpleImage floorDark;
	SimpleImage floorShadow;
	SimpleImage dirtyWater;
	SimpleImage treasure;
	SimpleImage diamond;
	SimpleImage stair;
	SimpleImage sand;
	SimpleImage lava;
	SimpleImage water1;
	SimpleImage water2;
	SimpleImage water3;
	SimpleImage water4;
	SimpleImage waterUp;
	SimpleImage waterLeft;
	SimpleImage waterRight;
	SimpleImage waterDown;
};

