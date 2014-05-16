#include "EnemyController.h"

EnemyController::EnemyController() : m_spawnDistance(200), m_score(0), m_respawnTime(2)
{
}

EnemyController::~EnemyController()
{
}

bool EnemyController::LoadContent(ResourceManager& resources, Player& player, Level& level)
{
	srand(time(NULL));

	int loNum = (17 * 3);
	int hiNum = (level.GetMapSize()*32) - (17 * 3);

	for( unsigned int e = 0; e < level.GetEnemyCount(); e++)
	{
		bool canSpawn = false;
		int randSpawnX = 0;
		int randSpawnY = 0;

		//loop untill it finds a good spawn location thats not close to the player
		while(!canSpawn)
		{
			//Spawns the enemies randomly around the level
			randSpawnX = loNum + (float)rand()/((float)RAND_MAX/(hiNum-loNum));
			randSpawnY = loNum + (float)rand()/((float)RAND_MAX/(hiNum-loNum));

			Vector2D spawnVector;
			spawnVector.x = randSpawnX;
			spawnVector.y = randSpawnY;

			if(DistanceFromTarget(spawnVector, player.GetPosition()) >= m_spawnDistance)
			{
				canSpawn = true;
			}
		}

		Enemy newEnemy;
		newEnemy.LoadContent(resources, randSpawnX, randSpawnY);
		newEnemy.SetShown(true);
		m_enemies.push_back(newEnemy);
	}

	for( unsigned int e = 0; e < level.GetEnemyCount(); e++)
	{
		PickupObject newLoot;
		newLoot.LoadContent(resources);
		newLoot.SetShown(false);
		m_loot.push_back(newLoot);
	}

	return true;
}

void EnemyController::UnloadContent()
{
}

void EnemyController::Update(float dt, Player& player, Level& level, Camera cam)
{
	//flag to check if the loot has already been dropped;
	bool alreadyDropped = false;

	for(unsigned int i = 0; i < m_enemies.size(); i++)
	{
		for(unsigned int p = 0; p < player.GetWeapon().GetProjectiles().GetProjectileBuffer(); p++)
		{
			//Check collision with enemies and projectiles
			if(m_enemies[i].CheckCollision(m_enemies[i].GetCollisionBox(),
				player.GetWeapon().GetProjectiles().GetProjectile(p).GetCollisionBox())
				&& (m_enemies[i].GetIsAlive()))
			{
				//Spawn the loot
				for(unsigned int p = 0; p < m_loot.size(); p++)
				{
					if(!m_loot[p].GetShown() && !(alreadyDropped) &&
						(player.GetWeapon().GetProjectiles().GetProjectile(p).GetShown()))
					{
						m_loot[p].SetPosX(m_enemies[i].GetPosition().x);
						m_loot[p].SetPosY(m_enemies[i].GetPosition().y);
						m_loot[p].SetType(/*rand()%4*/ 0 );
						m_loot[p].SetShown(true);
						alreadyDropped = true;
						break;
					}
				}

				//Stop projectile dependant on projectile type
				//ALL THIS CODE IS SOOOOO BAD RUSH RUSH RUSH RUSH
				if(player.GetWeapon().GetProjectiles().GetProjectile(p).GetShown())
				{
					switch(player.GetWeapon().GetProjectiles().GetProjectile(p).GetProjectileType())
					{
					case 0:
						player.GetWeapon().GetProjectiles().GetProjectile(p).SetShown(false);
						m_enemies[i].SetIsAlive(false);
						//Increase score
						m_score += 10;
						break;
					case 1:
						player.GetWeapon().GetProjectiles().GetProjectile(p).SetShown(false);
						m_enemies[i].SetIsAlive(false);
						//Increase score
						m_score += 10;
						break;
					}
				}

				//Kill enemy and start respawn timer
				m_enemies[i].GetRespawnTimer().Start();

			}
		}
	}

	//Update all the enmies as long as they are alive
	for(unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if(!m_enemies[i].GetIsAlive())
		{
			if(m_enemies[i].GetRespawnTimer().IsStarted())
			{
				if(m_enemies[i].GetRespawnTimer().GetTicks() / 1000 >= m_respawnTime)
				{
					int loNum = (17 * 3);
					int hiNum = (level.GetMapSize()*32) - (17 * 3);

					Vector2D spawnPos;
					spawnPos.x = loNum + (float)rand()/((float)RAND_MAX/(hiNum-loNum));
					spawnPos.y = loNum + (float)rand()/((float)RAND_MAX/(hiNum-loNum));

					if(DistanceFromTarget(spawnPos, player.GetPosition()) >= m_spawnDistance)
					{
						m_enemies[i].SetPosX(spawnPos.x);
						m_enemies[i].SetPosY(spawnPos.y);
						m_enemies[i].SetFrameX(0);
						m_enemies[i].SetIsAlive(true);
						m_enemies[i].GetRespawnTimer().Stop();
					}
				}
			}
		}

		if(m_enemies[i].GetShown())
		{
			m_enemies[i].Update(dt, player, level, cam);
		}
	}

	//Update all the pickups as long as they are alive
	for(unsigned int p = 0; p < m_loot.size(); p++)
	{
		if(m_loot[p].GetShown())
		{
			m_loot[p].Update(dt, cam);
		}
	}
}

void EnemyController::Render(SDL_Renderer* renderer, Camera cam)
{
	//render all the enemies as long as they are alive
	for(unsigned int i = 0; i < m_enemies.size(); i++)
	{
		if(m_enemies[i].GetShown())
		{
			m_enemies[i].Render(renderer, cam);
		}
	}

	//render all the loot as long as they are alive
	for(unsigned int p = 0; p < m_loot.size(); p++)
	{
		if(m_loot[p].GetShown())
		{
			m_loot[p].Render(renderer, cam);
		}
	}
}

Enemy& EnemyController::GetEnemy(int enemy)
{
	if(enemy < m_enemies.size())
	{
		return m_enemies[enemy];
	}
}

PickupObject& EnemyController::GetLoot( int loot )
{
	if(loot < m_loot.size())
	{
		return m_loot[loot];
	}
}

int EnemyController::GetEnemyAmount()
{
	return m_enemies.size();
}

int EnemyController::GetLootAmount()
{
	return m_loot.size();
}

int EnemyController::GetScore()
{
	return m_score;
}