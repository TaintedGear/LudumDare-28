#ifndef PROJECTILE_OBJECT_H
#define PROJECTILE_OBJECT_H

#include "PhysicsObject.h"

class ProjectileObject : public GameObject
{
public:
	ProjectileObject();
	~ProjectileObject();
	
	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	void Reset();

	int GetProjectileType();
	void SetProjectileType( int type );
	void SetRange( int range );
	void SetStartPosX( int x );
	void SetStartPosY( int y );
	void SetFireSpeed( float fireSpeed );
private:

	float m_fireSpeed;

	int m_projectileType,
		m_range,
		m_startPosX,
		m_startPosY;
};

#endif