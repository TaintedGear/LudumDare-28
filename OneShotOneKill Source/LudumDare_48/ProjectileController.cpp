#include "ProjectileController.h"

ProjectileController::ProjectileController() : m_projectileBuffer(30), m_fireType(0)
{
}

ProjectileController::~ProjectileController()
{

}

bool ProjectileController::LoadContent(ResourceManager& resources)
{
	for(unsigned int i = 0; i < m_projectileBuffer; i++)
	{
		ProjectileObject newProjectile;

		if(!newProjectile.LoadContent(resources))
		{
			return false;
		}
		newProjectile.SetShown(false);
		m_projectiles.push_back(newProjectile);
	}

	return true;
}

void ProjectileController::UnloadContent()
{
	for(unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		m_projectiles[i].UnloadContent();
	}
}

void ProjectileController::Update(float dt, Camera cam)
{
	for(unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if(m_projectiles[i].GetShown())
		{
			m_projectiles[i].Update(dt, cam);
		}
	}
}

void ProjectileController::Render(SDL_Renderer* renderer, Camera cam)
{	
	for(unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if(m_projectiles[i].GetShown())
		{
			m_projectiles[i].Render(renderer, cam);
		}
	}
}

void ProjectileController::Fire(int fireType, int startX, int startY, float angle)
{
	bool fired = false;
	for(unsigned int i = 0; i < m_projectiles.size(); i++)
	{
		if(!m_projectiles[i].GetShown())
		{
			switch(fireType)
			{
			case PISTOL:
				m_projectiles[i].SetPosX(startX);
				m_projectiles[i].SetPosY(startY);
				m_projectiles[i].SetStartPosX(startX);
				m_projectiles[i].SetStartPosY(startY);
				m_projectiles[i].SetAngle(angle);
				m_projectiles[i].SetFireSpeed(40.0f);
				m_projectiles[i].SetRange(500);
				m_projectiles[i].SetShown(true);
				fired = true;
				break;

			case SHOTGUN:

				break;

			case ROCKET_LAUNCHER:

				break;

			case RAIL_GUN:

				break;
			};
		}

		if(fired)
		{
  			break;
		}
	}
}

ProjectileObject& ProjectileController::GetProjectile( int projectile)
{
	if(projectile < m_projectiles.size())
	{
		return m_projectiles[ projectile ];
	}
}

int ProjectileController::GetProjectileBuffer()
{
	return m_projectiles.size();
}