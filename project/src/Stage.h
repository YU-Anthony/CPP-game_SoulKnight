#pragma once

#include "Scyyz4TileManager.h"

class Character;
class Scyyz4Engine;
class Scyyz4Object;

class Stage
{
public:
	Stage(){};
	Stage(Scyyz4Engine* pEngine);
	virtual ~Stage();

	virtual void virtDrawStringsOnTop(){};
	virtual void UndrawStrings(){};

	std::vector<std::string> GetCurrentView(){ return currentView; }
	void UpdateCurrentView();
	void UpdateMapData(int x, int y, char value);

	void LoadMapData(char* filename);
	void LoadGame(char* filename){};

	virtual void InitialiseObjects(){};
	//virtual int virtInitialiseObjects() { return 0; }
	virtual void virtMainLoopDoBeforeUpdate() {};
	virtual void copyAllBackgroundBuffer() {};
	virtual int virtInitialise() { return 0; }
	virtual void virtKeyDown(int keyCode){};
	virtual void virtMouseDown(int button, int x, int y){};
	virtual void virtMouseWheel(int x, int y, int which, int timestamp) {};
	virtual void ProcessMouseMovement(int x, int y){};
	virtual void virtSetupBackgroundBuffer(){};
	
	int GetScreenTileHeight(){ return screenTileHeight; }
	int GetScreenTileWidth(){ return screenTileWidth; }

	int GetTileManagerStartX(){ return tileStartX; }
	int GetTileManagerStartY(){ return tileStartY; }

	int GetMapHeight(){ return mapHeight; }
	int GetMapWidth(){ return mapWidth; }

	int GetCameraX(){ return cameraPosX; }
	int GetCameraY(){ return cameraPosY; }

	int GetMapValue(int x, int y){return mapData[y][x] - 'a';}
	std::vector<std::string> GetMapData() { return mapData; }

	/*float GetDistance(Character* object1, Character* object2);
	float GetDistance(float x1, float y1, Character* object2);*/
	float GetDistance(float x1, float y1, Scyyz4Object* object2);
	float GetDistance(float x1, float y1, float x2, float y2);


	
	virtual void DoUpdate(int iCurrentTime){};

	virtual void destoryObject(int objectID) {};

	/*virtual int getTime()
	{
		return gametime;
	}
*/

protected:
	int gametime;
	BaseEngine* m_engine;
	std::vector<std::string> currentView;
	std::vector<std::string> mapData;
	char* mapName;
	int mapHeight = 0, mapWidth = 0;
	int screenTileHeight= 0, screenTileWidth = 0;
	int cameraPosX=0, cameraPosY =0;
	int wPlayerPosX=0, wPlayerPosY=0, lPlayerPosX=0, lPlayerPosY=0;
	int tileStartX = 0, tileStartY = 0;

	//void PrintVariables();
	void PrintCurrentView();
};

