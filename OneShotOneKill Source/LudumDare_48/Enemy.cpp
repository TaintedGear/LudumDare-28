#include "Enemy.h"

Enemy::Enemy() : PhysicsObject(), m_newAngle(0.0f), m_chaseRange(200), m_respawnTimer(),
	m_isAlive(true), m_deathAlpha(255)
{
}

Enemy::~Enemy()
{
}

bool Enemy::LoadContent(ResourceManager& resources, int posX, int posY)
{
	m_image = resources.GetImages().GetImage("Enemy");

	if(m_image.m_imageLabel == "ERROR" || m_image.m_imageLabel == "NULL")
	{
		return false;
	}

	m_position.x = posX;
	m_position.y = posY;

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

	m_speed = 100.0f;
	m_maxSpeed = 250.0f;
	//m_drag = 0.99f;

	GameObject::LoadContent(resources);

	return true;
}

void Enemy::UnloadContent()
{
	GameObject::UnloadContent();
}

void Enemy::Update(float dt, Player& player, Level& level, Camera cam)
{
	float loNum = -6.28318531f;
	float hiNum = 6.28318531;

	GameObject::CycleAnimation(0, 4, 50.0f);

	int targX = player.GetPosition().x;
	int targY = player.GetPosition().y;

	//Get the distance to the target
	int distX = targX - m_position.x;
	int distY = targY - m_position.y;
	int distanceToTarget = sqrt((double)distX*distX + distY*distY);

	//If the player is within the range of the enemy then chase
	if(m_isAlive)
	{
		if(distanceToTarget <= m_chaseRange)
		{
			//Move enemy in the players direction
			m_angle = atan2( (double)targY - (double) m_position.y,
				(double)targX- (double)m_position.x) + DegreesToRadians(90.0f);
		}
		else
		{
			//This can be changed to make them seem a little better
			if((m_angle >= m_newAngle - DegreesToRadians(10)) && (m_angle <= m_newAngle + DegreesToRadians(10)))
			{
				//Make a new random angle for 360 agrees
				m_newAngle = loNum + (float)rand()/((float)RAND_MAX/(hiNum-loNum));
			}

			m_angle = Lerp(m_angle, m_newAngle, 0.01f);
		}

		m_acceleration.x = m_forwardVec.x * m_speed;
		m_acceleration.y = m_forwardVec.y * m_speed;
	}
	else // ENEMY IS DEAD
	{
		m_frameX = 4;
		//GameObject::SetAlpha(m_deathAlpha);
		//m_deathAlpha -= 10;

		//if(m_deathAlpha >= 1)
		//{
		//	m_deathAlpha = 1;
		//}
	}

	//Restrict to the level
	if(m_position.x >= (level.GetMapSize()*32) - (m_width * m_scale))
	{
		m_velocity.x *= -1.0f;
	}
	if(m_position.x <= 0)
	{
		m_velocity.x *= -1.0f;
	}
	if(m_position.y >= (level.GetMapSize()*32) - (m_height * m_scale))
	{
		m_velocity.y *= -1.0f;
	}
	if(m_position.y <= 0)
	{
		m_velocity.y *= -1.0f;
	}

	//Update the collisionBox
	m_collisionBox.x = m_position.x - cam.GetPosX(); /*+ (m_width / 4)*/;
	m_collisionBox.y = m_position.y - cam.GetPosY(); /*+ (m_height / 4)*/;
	m_collisionBox.w = m_width * m_scale /*- (m_width / 4)*/;
	m_collisionBox.h = m_height * m_scale /*- (m_height / 4)*/;


	PhysicsObject::Update(dt);

};

void Enemy::Render(SDL_Renderer* renderer, Camera cam)
{
	GameObject::Render(renderer, cam);
}

Timer& Enemy::GetRespawnTimer()
{
	return m_respawnTimer;
}

void Enemy::SetIsAlive( bool alive )
{
	m_isAlive = alive;
}
bool Enemy::GetIsAlive()
{
	return m_isAlive;
}