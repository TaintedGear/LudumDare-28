#include "FlashbackBarSegementObject.h"

FlashbackBarSegementObject::FlashbackBarSegementObject() : GameObject()
{
}

FlashbackBarSegementObject::~FlashbackBarSegementObject()
{
}

bool FlashbackBarSegementObject::LoadContent(ResourceManager& resources)
{
	m_image = resources.GetImages().GetImage("Hud");
	
	if(m_image.m_imageLabel == "ERROR" || m_image.m_imageLabel == "NULL")
	{
		return false;
	}
	
	m_scale = 3;
	m_startX = 0;
	m_startY = 17 * 3;
	m_width = 17;
	m_height = 17;
	m_originX = m_width/2;
	m_originY = m_height/2;
	m_show = true;
	m_frameX = 0;
	m_frameY = 0;
	m_angle = 0.0f;

	GameObject::LoadContent(resources);

	return true;
}

void FlashbackBarSegementObject::UnloadContent()
{
	GameObject::UnloadContent();
}

void FlashbackBarSegementObject::Update(float dt)
{
	GameObject::Update(dt);
}

void FlashbackBarSegementObject::Render(SDL_Renderer* renderer)
{
	Camera cam;

	GameObject::Render(renderer, cam);
}