#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <iostream>
#include <vector>
#include <ctime>

#include "Enemy.h"
#include "PickupObject.h"

using std::vector;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	bool LoadContent(ResourceManager& resources, Player& player, Level& level);
	void UnloadContent();

	void Update(float dt, Player& player, Level& level, Camera cam);
	void Render(SDL_Renderer* renderer, Camera cam);

	Enemy& GetEnemy( int enemy );
	PickupObject& GetLoot( int loot );
	int GetEnemyAmount();
	int GetLootAmount();
	int GetScore();

private:
	int m_spawnDistance,
		m_score,
		m_respawnTime;

	vector<Enemy> m_enemies;
	vector<PickupObject> m_loot;
};

#endif