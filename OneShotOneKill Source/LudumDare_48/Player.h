#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include "PhysicsObject.h"
#include "Input.h"
#include "Level.h"
#include "WeaponObject.h"

class Player : public PhysicsObject
{
public:
	Player();
	~Player();

	bool LoadContent( ResourceManager& resources);
	void UnloadContent();

	void Update(float dt, Input& input, Camera cam, Level& level);
	void Render(SDL_Renderer* renderer, Camera cam);

	void Hit(Vector2D oppositeVec);

	bool GetHasWeapon();
	bool GetAlive();
	int GetLives();
	void SetAlive( bool alive );
	void SetHasWeapon( bool hasWep);

	WeaponObject& GetWeapon();

private:
	void Move(Input& input, Camera cam, Level& level);

	int m_lives;

	bool m_isAlive,
		m_hit,
		m_hasWeapon,
		m_hitImmune;

	int m_knockBack,
		m_hitImmunity,
		m_hitAlpha;

	Timer m_hitTimer;
	Vector2D m_hitDirection;

	WeaponObject m_weapon;
};

#endif