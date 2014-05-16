#include "Level.h"

Level::Level() : m_image(), m_mapSize(0), m_enemyCount(0)
{
}

Level::~Level()
{
}

bool Level::LoadLevel(string filename, ResourceManager& resources, int mapSize, int enemyCount)
{
	m_mapSize = mapSize;
	m_enemyCount = enemyCount;

	m_levelFormat = new int[mapSize*mapSize];

	FILE *file;

	string filePath = "Data/Levels/" + filename + ".txt";

	file = fopen(filePath.c_str(), "rb");
	
	if(file != NULL)
	{

		for(int y = 0; y < mapSize; y++)
		{
			for(int x = 0; x < mapSize; x++)
			{
				fscanf(file, "%d", &m_levelFormat[x + (y * mapSize)]);
			}
		}

		int i = 0;
		for(int y = 0; y < mapSize; y++)
		{
			for(int x = 0; x < mapSize; x++)
			{
				if(m_levelFormat[x + (y * mapSize)] == NO_TILE)
				{

				}
				if(m_levelFormat[x + (y * mapSize)] == FLOOR_TILE)
				{
					TileObject newTile;
					newTile.LoadTile("TileSheet", resources, (x*32), (y*32), 0, 0, 32);
					m_levelTiles.push_back(newTile);
				}
				if(m_levelFormat[x + (y * mapSize)] == WALL_TILE)
				{
					TileObject newTile;
					newTile.LoadTile("TileSheet", resources, (x*32), (y*32), 32, 0, 32);
					m_levelTiles.push_back(newTile);
				}
			}
		}
	}

	fclose(file);

	return true;
}

void Level::UnloadLevel()
{
	delete m_levelFormat;
}

void Level::Update( float dt, Camera cam )
{
	for(unsigned int t = 0; t < m_levelTiles.size(); t++)
	{
		m_levelTiles[t].Update(dt, cam);
	}
}

void Level::Render( SDL_Renderer* renderer, Camera cam)
{
	for(unsigned int t = 0; t < m_levelTiles.size(); t++)
	{
		m_levelTiles[t].Render(renderer, cam);
	}
}

TileObject Level::GetTiles(int tile)
{
	if(tile < m_levelTiles.size())
	{
		return m_levelTiles[tile];
	}
}

int Level::GetMapSize()
{
	return m_mapSize;
}
int Level::GetTileAmount()
{
	return m_levelTiles.size();
}
int Level::GetEnemyCount()
{
	return m_enemyCount;
}