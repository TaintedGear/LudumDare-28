#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <ctime>

#include "MathHelper.h"
#include "PhysicsObject.h"
#include "Player.h"

using namespace MathHelper;

class Enemy : public PhysicsObject
{
public:
	Enemy();
	~Enemy();

	bool LoadContent(ResourceManager& resources, int posX, int posY);
	void UnloadContent();

	void Update(float dt, Player& player, Level& level,
		Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);
	
	bool GetIsAlive();

	Timer& GetRespawnTimer();
	void SetIsAlive( bool alive );
private:
	float m_newAngle;
	int m_chaseRange,
		m_deathAlpha;
	bool m_isAlive;

	Timer m_respawnTimer;
};

#endif