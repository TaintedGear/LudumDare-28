#include "PickupObject.h"

PickupObject::PickupObject() : GameObject(), m_typeId(0), m_pickedUp(false)
{
}

PickupObject::~PickupObject()
{
}

bool PickupObject::LoadContent(ResourceManager& resources)
{
	m_image = resources.GetImages().GetImage("Pickups");

	if(m_image.m_imageLabel == "ERROR" || m_image.m_imageLabel == "NULL")
	{
		return false;
	}

	m_scale = 3;
	m_startX = 0;
	m_startY = 0;
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

void PickupObject::UnloadContent()
{
	GameObject::UnloadContent();
}

void PickupObject::Update(float dt, Camera cam)
{
	//rotate the pick up
	m_angle += DegreesToRadians(2);

	//Update the collisionBox
	m_collisionBox.x = m_position.x - cam.GetPosX() + (m_width / 4);
	m_collisionBox.y = m_position.y - cam.GetPosY() + (m_height / 4);
	m_collisionBox.w = m_width * m_scale - (m_width * m_scale / 4);
	m_collisionBox.h = m_height * m_scale - (m_height * m_scale / 4);

	GameObject::Update(dt);
}

void PickupObject::Render(SDL_Renderer* renderer, Camera cam)
{

	GameObject::Render(renderer, cam);
}

int PickupObject::GetType()
{
	return m_typeId;
}

void PickupObject::SetType( int type )
{
	m_typeId = type;
	m_frameX = m_typeId;
}

void PickupObject::SetPicked( bool picked )
{
	m_pickedUp = picked;
}