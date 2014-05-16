#include "FlashbackBarObject.h"

FlashbackBarObject::FlashbackBarObject() : GameObject()
{
}

FlashbackBarObject::~FlashbackBarObject()
{
}

bool FlashbackBarObject::LoadContent(ResourceManager& resources, int windowWidth)
{
	m_image = resources.GetImages().GetImage("Hud");
	
	if(m_image.m_imageLabel == "ERROR" || m_image.m_imageLabel == "NULL")
	{
		return false;
	}
	
	m_scale = 2;
	m_startX = 0;
	m_startY = 17 * 2;
	m_width = 68;
	m_height = 17;
	m_originX = m_width/2;
	m_originY = m_height/2;
	m_show = true;
	m_frameX = 0;
	m_frameY = 0;
	m_angle = 0.0f;

	m_position.x = windowWidth - 150;
	m_position.y = 50;

	for(unsigned int s = 0; s < 5; s++)
	{
		FlashbackBarSegementObject newSegement;

		if(!newSegement.LoadContent(resources))
		{
			return false;
		}

		newSegement.SetPosX(m_position.x + (s*25));
		newSegement.SetScale(2);
		newSegement.SetPosY(50);

		m_segements.push_back(newSegement);
	}

	GameObject::LoadContent(resources);

	return true;
}

void FlashbackBarObject::UnloadContent()
{
	for(unsigned int i = 0; i < m_segements.size(); i++)
	{
		m_segements[i].UnloadContent();
	}

	GameObject::UnloadContent();
}

void FlashbackBarObject::Update(float dt, int flashBackRemaining)
{

	for(unsigned int i = 0; i < m_segements.size(); i++)
	{
		if(flashBackRemaining > (i*20.0f))
		{
			m_segements[i].SetShown(true);

			if(flashBackRemaining > (i*20.0f) + i*3.0f)
			{
				if(m_segements[i].GetFrameX() <= 2)
				{
					m_segements[i].SetFrameX(m_segements[i].GetFrameX() + 1);
				}
			}
			else
			{
				if(m_segements[i].GetFrameX() > 0)
				{
					m_segements[i].SetFrameX(m_segements[i].GetFrameX() - 1);
				}
			}
		}
		else
		{

			m_segements[i].SetShown(false);
		}

		m_segements[i].Update(dt);
	}

	GameObject::Update(dt);
}

void FlashbackBarObject::Render(SDL_Renderer* renderer)
{
	Camera cam;

	GameObject::Render(renderer, cam);

	for(unsigned int i = 0; i < m_segements.size(); i++)
	{
		if(m_segements[i].GetShown())
		{
			m_segements[i].Render(renderer);
		}
	}
}