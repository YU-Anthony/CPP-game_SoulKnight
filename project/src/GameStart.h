#pragma once
#include "Stage.h"
#include "Scyyz4Engine.h"
#include "DragableObject.h"
#include "CoordinateMapping.h"

class Scyyz4Engine;
class CoordinateMapping;
class RedMonster;
class MappableImageObject;

class GameStart :
	public Stage, public CoordinateMapping
{
public: 
	GameStart(Scyyz4Engine* pEngine);
	~GameStart() 
	{
		//printf(")(start released\n");
		//delete ob;
	}

	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtMainLoopDoBeforeUpdate();
	void copyAllBackgroundBuffer();
	void virtMouseDown(int button, int x, int y);
	bool mapCoordinates(double& x, double& y, const SimpleImage& image);

private:
	MappableImageObject* ob;

protected:
	Scyyz4Engine* m_engine;
	CoordinateMappingRotate rotator;
	SimpleImage bkImage;
	int m_iOffset;
};

