#include "TileObject.h"

TileObject::TileObject() : GameObject(), m_tileId(0)
{
}

TileObject::~TileObject()
{
}

bool TileObject::LoadTile(string filename, ResourceManager& resource, int posX, int posY, int srcX, int srcY,
	int size)
{
	m_image = resource.GetImages().GetImage("TileSheet");

	if(m_image.m_imageLabel == "ERROR" || m_image.m_imageLabel == "NULL")
	{
		return false;
	}

	m_position.x = posX;
	m_position.y = posY;
	m_startX = srcX;
	m_startY = srcY;
	m_width = size;
	m_height = size;
	m_originX = m_width/2;
	m_originY = m_height/2;
	m_show = true;
	m_frameX = 0;
	m_angle = 0.0f;

	if(srcX == 0)
	{
		m_tileId = 0;
	}
	else if(srcX == (size * 1))
	{
		m_tileId = 1;
	}
	else if(srcX == (size * 2))
	{
		m_tileId = 2;
	}

	return true;
}

void TileObject::UnloadTile()
{
}

void TileObject::Update( float dt, Camera cam )
{
	//Update the collisionBox
	m_collisionBox.x = m_position.x - cam.GetPosX(); /*+ (m_width / 4)*/;
	m_collisionBox.y = m_position.y - cam.GetPosY(); /*+ (m_height / 4)*/;
	m_collisionBox.w = m_width * m_scale /*- (m_width / 4)*/;
	m_collisionBox.h = m_height * m_scale /*- (m_height / 4)*/;

	GameObject::Update(dt);
}

void TileObject::Render( SDL_Renderer* renderer, Camera cam)
{
	GameObject::Render(renderer, cam);
}

int TileObject::GetTileId()
{
	return m_tileId;
}