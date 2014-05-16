#ifndef TILE_OBJECT_H
#define TILE_OBJECT_H

#include <SDL.h>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Camera.h"

class TileObject : public GameObject
{
public:
	TileObject();
	~TileObject();

	bool LoadTile(string filename, ResourceManager& resource,
		int posX, int posY, int srcX, int srcY, int size);
	void UnloadTile();

	void Update( float dt, Camera cam );
	void Render( SDL_Renderer* renderer, Camera cam);

	int GetTileId();

protected:

	int m_tileId;

};

#endif