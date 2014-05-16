#include "PlayerController.h"

PlayerController::PlayerController() : m_player(), m_testFlashback(0.0f)
{
}

PlayerController::~PlayerController()
{
}

bool PlayerController::LoadContent(ResourceManager& resources, Level& level)
{
	if(!m_player.LoadContent(resources))
	{
		return false;
	}

	m_player.SetPosX((level.GetMapSize()*32)/2 + m_player.GetWidth());
	m_player.SetPosY((level.GetMapSize()*32)/2 + m_player.GetHeight());

	return true;
}

void PlayerController::UnloadContent()
{
	m_player.UnloadContent();
}

void PlayerController::Update(float dt, Input& input, Camera cam, Level& level,
	EnemyController& enemyController)
{
	m_testFlashback += dt;

	//Check to see if the enemy hit the player
	for(unsigned int e = 0; e < enemyController.GetEnemyAmount(); e++)
	{
		//check collision with the enemies if they are alive
		if(m_player.CheckCollision(m_player.GetCollisionBox(),
			enemyController.GetEnemy(e).GetCollisionBox()) && 
			(enemyController.GetEnemy(e).GetIsAlive()))
		{
			m_player.Hit(enemyController.GetEnemy(e).GetForwardVec());
		}
	}

	//check to see if the player picked up a weapon or pickup item
	for(unsigned int p = 0; p < enemyController.GetLootAmount(); p++)
	{
		//check to see if the player collided with the loot if its alive
		if(m_player.CheckCollision(m_player.GetCollisionBox(), 
			enemyController.GetLoot(p).GetCollisionBox())
			&& (enemyController.GetLoot(p).GetShown()))
		{
			//If the pick up is a weapon then pick the weapon up
			if(enemyController.GetLoot(p).GetType() <= 4)
			{
				if(!m_player.GetHasWeapon())
				{
					m_player.GetWeapon().SetWeaponId(enemyController.GetLoot(p).GetType());
					m_player.SetHasWeapon( true );

					enemyController.GetLoot(p).SetShown(false);
				}
			}

			
			break;
		}
	}

	if(m_player.GetLives() <= 0)
	{
		m_player.SetFrameX(4);
		m_player.SetAlive(false);
	}
	
	if(m_player.GetAlive())
	{
		m_player.Update(dt, input, cam, level);
	}
}

void PlayerController::Render( SDL_Renderer* renderer, Camera cam)
{

	m_player.Render( renderer, cam );
}

Player& PlayerController::GetPlayer()
{
	return m_player;
}