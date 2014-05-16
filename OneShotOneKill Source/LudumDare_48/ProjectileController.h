#ifndef PROJECTILE_CONTROLLER_H
#define PROJECTILE_CONTROLLER_H

#include <iostream>
#include <vector>

#include "ProjectileObject.h"

using std::vector;

class ProjectileController
{
public:
	ProjectileController();
	~ProjectileController();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	void Fire(int fireType, int startX, int startY, float angle);

	ProjectileObject& GetProjectile( int projectile );
	int GetProjectileBuffer();

private:
	int m_projectileBuffer,
		m_fireType;
	vector<ProjectileObject> m_projectiles;

	enum m_fireTypes { PISTOL = 0, SHOTGUN = 1, ROCKET_LAUNCHER = 2, RAIL_GUN = 3};
};

#endif