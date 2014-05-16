#ifndef GAME_H
#define GAME_H

#include "System.h"
#include "ResourceManager.h"

#include "PlayerCamera.h"
#include "PlayerController.h"
#include "EnemyController.h"
#include "Level.h"
#include "FlashbackController.h"
#include "GameHud.h"
#include "Menu.h"

class Game
{
public:
	Game();
	~Game();

	bool Initialise();
	void Run();
	void Shutdown();

private:
	int m_state;

	void Update();
	void Render();

	System m_system;
	ResourceManager m_resourceManager;

	PlayerCamera m_playerCam,
		m_resetCam;
	PlayerController m_playerController,
		m_resetPlayerController;
	EnemyController m_enemyController,
		m_resetEnemyController;
	Level m_level;


	FlashbackController m_flashback,
		m_resetFlash;

	GameHud m_gameHud,
		m_resetHud;

	Menu m_menu;

	float m_deltaTicks;
};

#endif