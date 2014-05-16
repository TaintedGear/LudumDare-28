#ifndef LEVEL_H
#define LEVEL_H

#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ResourceManager.h"
#include "TileObject.h"
#include "Camera.h"

using std::string;
using std::ifstream;
using std::vector;
using std::ios;
using std::getline;

class Level
{
public:
	Level();
	~Level();

	bool LoadLevel(string filename, ResourceManager& resources, int mapSize, int enemyCount);
	void UnloadLevel();

	void Update(float dt, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	TileObject GetTiles(int tile);
	int GetMapSize();
	int GetTileAmount();
	int GetEnemyCount();
private:
	Image m_image;
	vector<TileObject> m_levelTiles;
	int* m_levelFormat;

	int m_mapSize,
		m_enemyCount;

	enum m_tileTypes {NO_TILE = 0, FLOOR_TILE = 1, WALL_TILE = 2};
};

#endif