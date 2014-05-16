#ifndef FLASHBACK_CONTROLLER_H
#define FLASHBACK_CONTROLLER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "FlashbackHud.h"
#include "GameHud.h"

#include "PlayerController.h"
#include "EnemyController.h"
#include "Timer.h"

#include "FontObject.h"

class FlashbackController
{
public:
	FlashbackController();
	~FlashbackController();

	void LoadStartStates( PlayerController& playerController,
		EnemyController& enemyController, GameHud& gameHud, int fps);

	bool LoadContent(ResourceManager& resources, int windowWidth);
	void UnloadContent();

	void Update( float dt, PlayerController& playerController,
		EnemyController& enemyController, GameHud& gameHud, Input& input);

	void Render(SDL_Renderer* renderer);

	bool GetFlashback();

private:

	int m_statePerSec,
		m_totalFlashbackSecs,
		m_fps,
		m_currentFrame,
		m_currentState,
		m_flashbackFrame,
		m_totalFlashBack,
		m_flashBackRecharge;

	vector<PlayerController> m_previousPlayerState;
	vector<EnemyController> m_previousEnemyState;
	vector<GameHud> m_previousHudState;

	bool m_flashBack,
		m_flashBackReady;

	FlashbackHud m_flashbackHud;
};

#endif