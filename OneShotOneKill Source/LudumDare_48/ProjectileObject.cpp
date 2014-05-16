#include "ProjectileObject.h"

ProjectileObject::ProjectileObject() : GameObject(), m_projectileType(0), m_range(0), m_fireSpeed(0.0f),
	m_startPosX(0), m_startPosY(0)
{
}

ProjectileObject::~ProjectileObject()
{
}

bool ProjectileObject::LoadContent(ResourceManager& resources)
{
	m_image = resources.GetImages().GetImage("Projectiles");

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
	m_show = false;
	m_frameX = 0;
	m_frameY = 0;
	m_angle = 0.0f;

	m_position.x = 0;
	m_position.y = 0;

	GameObject::LoadContent(resources);

	return true;
}

void ProjectileObject::UnloadContent()
{
	GameObject::UnloadContent();
}

void ProjectileObject::Update(float dt, Camera cam)
{
    GameObject::Update(dt);

	Vector2D startPos;
	startPos.x = m_startPosX;
	startPos.y = m_startPosY;

	float distanceFromStart = DistanceFromTarget(m_position, startPos);
	
	if(distanceFromStart >= m_range)
	{
		//maybe do some animation
		Reset();
	}

	m_position.x += m_forwardVec.x * m_fireSpeed;
    m_position.y += m_forwardVec.y * m_fireSpeed;

	//Update the collisionBox
	m_collisionBox.x = m_position.x - cam.GetPosX() + (m_width / 4);
	m_collisionBox.y = m_position.y - cam.GetPosY() + (m_height / 4);
	m_collisionBox.w = m_width * m_scale - (m_width * m_scale / 4);
	m_collisionBox.h = m_height * m_scale - (m_height * m_scale / 4);

}

void ProjectileObject::Render(SDL_Renderer* renderer, Camera cam)
{
 	GameObject::Render(renderer, cam);
}

int ProjectileObject::GetProjectileType()
{
	return m_projectileType;
}

void ProjectileObject::SetProjectileType( int type )
{
	m_projectileType = type;
	m_frameX = m_projectileType;
}

void ProjectileObject::SetStartPosX( int x )
{
	m_startPosX = x;
}

void ProjectileObject::SetStartPosY( int y )
{
	m_startPosY = y;
}

void ProjectileObject::SetRange( int range )
{
	m_range = range;
}

void ProjectileObject::SetFireSpeed( float fireSpeed )
{
	m_fireSpeed = fireSpeed;
}

void ProjectileObject::Reset()
{
	m_show = false;
	m_angle = 0.0f;
	m_position.x = 0;
	m_position.y = 0;
	m_startPosX = 0;
	m_startPosY = 0;
	m_fireSpeed = 0.0f;
	m_range = 0;
}