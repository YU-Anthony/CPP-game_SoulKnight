#include "header.h"
#include "Stage.h"
#include "Scyyz4Engine.h"
#include "SimpleImage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <SDL_mixer.h>
#include "Scyyz4Object.h"

using namespace std;

Stage::Stage(Scyyz4Engine* pEngine)
{
	//printf("()stage generate\n");
	m_engine = pEngine;
	//m_engine->virtSetupBackgroundBuffer();
}


Stage::~Stage()
{
	//printf(")(stage release\n");
	/*for (int i = 0; i < screenTileHeight; i++)
		delete &currentView[i];

	currentView.clear();*/

	for (int i = 0; i < mapHeight; i++)
		delete &mapData[i];

	mapData.clear();
}

void Stage::LoadMapData(char* filename){ //Load in the tile data for the background
	ifstream mapFile;
	string line;
	int itemCount = 0;
	int mapLine = 0;

	mapFile.open(filename,ios::in);
	
	if (!mapFile.is_open()){
		cout << "File failed to open!" << endl;
		return;
	}

	cout << "Reading map data..." << endl;

	while (getline(mapFile, line,',')){


		if (line.substr(0, 1) == "\n")
			line.erase(0, 1);	//ERASE THE NEW LINE CHAR
		mapData.push_back(line);
		/*printf("push map values\n");*/
	}

	screenTileWidth = mapData[1].length();
	screenTileHeight = mapData.size();

	mapFile.close();
}

void Stage::UpdateCurrentView(){ //Update the vector that contains the currently visible part of the map
	currentView.clear();
	/*for (int y = 0; y < screenTileHeight; y++){
		string mapLine(mapData[cameraPosY + y]);
		string currentLine(mapLine.substr(cameraPosX,screenTileWidth));
		currentView.push_back(currentLine);
	}*/
	/*printf("Update current view\n");*/
	currentView = mapData;
}


void Stage::PrintCurrentView(){ //Prints the current view vector
	system("cls");
	for (int y = 0; y < screenTileHeight; y++)
		cout << currentView[y] << endl;
}

void Stage::UpdateMapData(int x, int y, char value){ //Updates the map at a given position
	mapData[y].at(x) = value;
}

float Stage::GetDistance(float x1, float y1, Scyyz4Object* object2) { //Calculates the SLD between coordinates and two characters
	return GetDistance(x1, y1, object2->getXTile(object2->getXPosition()), object2->getYTile(object2->getYPosition()));
}

float Stage::GetDistance(float x1, float y1, float x2, float y2){ //Calculates the SLD between coordinates
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

