#include "Player.h"

Player::Player() : PhysicsObject(), m_lives(3), m_isAlive(true), m_knockBack(100000.0f),
	m_hitAlpha(255), m_hitTimer(), m_hit(false), m_hitImmunity(2), m_hasWeapon(true),
	m_weapon(), m_hitImmune(false)
{
}

Player::~Player()
{
}

bool Player::LoadContent( ResourceManager& resources )
{
	m_image = resources.GetImages().GetImage("Player");

	if(m_image.m_imageLabel == "ERROR")
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

	m_speed = 1000.0f;
	m_maxSpeed = 250.0f;
	m_drag = 0.90f;

	m_position.x = 200;
	m_position.y = 200;

	//Initalise the weapon class
	if(!m_weapon.LoadContent(resources))
	{
		return false;
	}

	return true;
}

void Player::UnloadContent()
{
}

void Player::Update( float dt, Input& input, Camera cam, Level& level )
{
	//Move Player
	Move(input, cam, level);

	//Checking to see if hit
	if(m_hit)
	{
		if(m_hitTimer.IsStarted())
		{
			if((m_hitTimer.GetTicks() / 1000) >= m_hitImmunity)
			{
				//m_lives -=1;
				m_hit = false;
				m_hitAlpha = 255;
				GameObject::SetAlpha(255);
				m_hitImmune = false;
				m_hitTimer.Stop();
			}
			else
			{
				GameObject::SetAlpha(m_hitAlpha);
				if(m_hitAlpha <= 30)
				{
					m_hitAlpha = 255;
				}
				m_hitAlpha -= 10;
			}
		}
		else
		{
			m_hitTimer.Start();
		}
	}
	
	//Turn off the weapon if you dont have one
	if(!m_hasWeapon)
	{
		m_weapon.SetShown(false);
	}
	else
	{
		m_weapon.SetShown(true);
	}

	//Update the collisionBox
	m_collisionBox.x = m_position.x - cam.GetPosX(); /*+ (m_width / 4)*/;
	m_collisionBox.y = m_position.y - cam.GetPosY(); /*+ (m_height / 4)*/;
	m_collisionBox.w = m_width * m_scale /*- (m_width / 4)*/;
	m_collisionBox.h = m_height * m_scale /*- (m_height / 4)*/;

	PhysicsObject::Update(dt);

	//Update the weapon if the player has one
	m_weapon.Update(dt, m_position, m_angle, cam);
}

void Player::Render(SDL_Renderer* renderer, Camera cam)
{
	GameObject::Render(renderer, cam);

	//If the player has the weapon then draw it
	m_weapon.Render(renderer, cam);
}

void Player::Hit(Vector2D oppositeVec)
{
	if(!m_hitImmune)
	{
		m_lives -= 1;
		m_hitImmune = true;
		m_hit = true;
	}

	if(m_velocity.x <= 2000.0f && m_velocity.y <= 2000.0f)
	{
		m_acceleration.x = oppositeVec.x * m_knockBack / 10;
		m_acceleration.y = oppositeVec.y * m_knockBack / 10;
	}
	else
	{
		m_acceleration.x = oppositeVec.x * m_knockBack;
		m_acceleration.y = oppositeVec.y * m_knockBack;
	}
}

void Player::Move(Input& input, Camera cam, Level& level)
{
	// Move when input
	if(input.GetKeyState(SDL_SCANCODE_W))
	{
		m_acceleration.y -=  m_speed;

		GameObject::CycleAnimation(0, 4, 50.0f); // walk anim
	}
	if(input.GetKeyState(SDL_SCANCODE_S))
	{
		m_acceleration.y +=  m_speed;

		GameObject::CycleAnimation(0, 4, 50.0f); // walk anim
	}
	if(input.GetKeyState(SDL_SCANCODE_A))
	{
		m_acceleration.x -= m_speed;

		GameObject::CycleAnimation(0, 4, 50.0f); // walk anim
	}
	if(input.GetKeyState(SDL_SCANCODE_D))
	{
		m_acceleration.x += m_speed;

		GameObject::CycleAnimation(0, 4, 50.0f); // walk anim
	}


	//Make the player always look at the mouse X and Y
	int mouseX = input.GetMouseX() + cam.GetPosX();
	int mouseY = input.GetMouseY() + cam.GetPosY();

	m_angle = (float)atan2((double) mouseY - (double)m_position.y, 
		(double) mouseX - (double)m_position.x) + DegreesToRadians(90.0f);


	//Restrict the player to the confides of the map
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

	//Fire the weapon
//	if(input.GetKeyState(SDL_SCANCODE_SPACE))
	if(input.GetMouseButtonState(1))
	{
		if(m_hasWeapon)
		{
			m_weapon.GetProjectiles().Fire(m_weapon.GetWeaponId(), 
				m_position.x, m_position.y, m_angle);
			m_hasWeapon = false;
		}
	}
}

int Player::GetLives()
{
	return m_lives;
}

void Player::SetAlive( bool alive )
{
	m_isAlive = alive;
}

bool Player::GetAlive()
{
	return m_isAlive;
}

bool Player::GetHasWeapon()
{
	return m_hasWeapon;
}

WeaponObject& Player::GetWeapon()
{
	return m_weapon;
}

void Player::SetHasWeapon( bool hasWep )
{
	m_hasWeapon = hasWep;
}