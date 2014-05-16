#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Player.h"
#include "Level.h"
#include "EnemyController.h"

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	bool LoadContent(ResourceManager& resources, Level& level);
	void UnloadContent();

	void Update(float dt, Input& input, Camera cam, Level& level,
		EnemyController& enemy);
	void Render(SDL_Renderer* renderer, Camera cam);

	Player& GetPlayer();
private:

	float m_testFlashback;

	Player m_player;
	Vector2D m_previousPosition;
	Vector2D m_reverseVelocity;
};

#endif