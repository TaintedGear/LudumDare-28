#ifndef WEAPON_OBJECT_H
#define WEAPON_OBJECT_H

#include "GameObject.h"
#include "MathHelper.h"
#include "ProjectileController.h"

using namespace MathHelper;

enum{PISTOL = 0, SHOTGUN = 1, ROCKET_LAUNCHER = 2, RAILGUN = 3};

class WeaponObject : public GameObject
{
public:
	WeaponObject();
	~WeaponObject();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt, Vector2D attachPos, float attachAngle, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	ProjectileController& GetProjectiles();

	int GetWeaponId();
	void SetWeaponId( int id );

private:
	int m_weaponId;

	ProjectileController m_projectiles;
};

#endif