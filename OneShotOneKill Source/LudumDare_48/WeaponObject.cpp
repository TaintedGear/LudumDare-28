#include "WeaponObject.h"

WeaponObject::WeaponObject() : GameObject(), m_projectiles(), m_weaponId(0)
{
}

WeaponObject::~WeaponObject()
{
}

bool WeaponObject::LoadContent(ResourceManager& resources)
{
	m_image = resources.GetImages().GetImage("Weapons");
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

	//Load all the projectiles
	if(!m_projectiles.LoadContent(resources))
	{
		return false;
	}

	GameObject::LoadContent(resources);
}

void WeaponObject::UnloadContent()
{
	m_projectiles.UnloadContent();
	GameObject::UnloadContent();
}

void WeaponObject::Update(float dt, Vector2D attachPos, float attachAngle, Camera cam)
{
	GameObject::Update(dt);

	//switch to update the offsets diffrently + change the projectile path etc
	switch(m_weaponId)
	{
	case PISTOL:

		m_position.x = attachPos.x;
		m_position.y = attachPos.y;
		m_angle = attachAngle;

		break;
	case SHOTGUN:

		//m_position.x = attachX;
		//m_position.y = attachY;
		//m_angle = attachAngle;
		//m_originX = m_width;
		//m_originY = m_height;
		break;
	case ROCKET_LAUNCHER:

		//m_position.x = attachX;
		//m_position.y = attachY;
		//m_angle = attachAngle;
		//m_originX = m_width;
		//m_originY = m_height;
		break;
	case RAILGUN:

		/*m_position.x = attachX;
		m_position.y = attachY;
		m_angle = attachAngle;*/
		//m_originX = m_width;
		//m_originY = m_height;
		break;
	}

	//Update the projectiles
	m_projectiles.Update(dt, cam);
}

void WeaponObject::Render(SDL_Renderer* renderer, Camera cam)
{
	m_projectiles.Render(renderer, cam);

	if(m_show)
	{
		GameObject::Render(renderer, cam);
	}
}

int WeaponObject::GetWeaponId()
{
	return m_weaponId;
}

void WeaponObject::SetWeaponId(int id)
{
	m_weaponId = id;
	m_frameY = m_weaponId;
}

ProjectileController& WeaponObject::GetProjectiles()
{
	return m_projectiles;
}