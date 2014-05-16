#include "Game.h"

Game::Game() : m_system(800, 600), m_resourceManager(), m_playerCam()
	, m_deltaTicks(0.0f), m_playerController(), m_state(0), m_menu()
{
}

Game::~Game()
{
}

bool Game::Initialise()
{
	//Initialise SDL and other libs
	if(!m_system.Initialise())
	{
		return false;
	}

	//Load Game content
	if(!m_resourceManager.LoadResources(m_system.GetRenderer()))
	{
		return false;
	}

	if(!m_level.LoadLevel("test", m_resourceManager, 30, 10))
	{
		return false;
	}

	if(!m_playerController.LoadContent( m_resourceManager, m_level))
	{
		return false;
	}
	if(!m_enemyController.LoadContent( m_resourceManager, m_playerController.GetPlayer(), m_level))
	{
		return false;
	}
	if(!m_flashback.LoadContent(m_resourceManager, m_system.GetScreenWidth()))
	{
		return false;
	}
	if(!m_gameHud.LoadContent(m_resourceManager, m_system.GetScreenWidth()))
	{
		return false;
	}
	if(!m_menu.LoadContent(m_resourceManager))
	{
		return false;
	}

	m_playerCam.Initialise(1, 3, m_system.GetScreenWidth(), m_system.GetScreenHeight(),
		m_playerController.GetPlayer());

	m_flashback.LoadStartStates(m_playerController, m_enemyController, m_gameHud, 30);

	m_resetCam = m_playerCam;
	m_resetPlayerController = m_playerController;
	m_resetEnemyController = m_enemyController;
	m_resetFlash = m_flashback;
	m_resetHud = m_gameHud;

	return true;
}

void Game::Run()
{
	//Start the fps timer
	m_system.GetFpsTimer().Start();

	// Game while loop
	while(!m_system.Done())
	{
		//Check for events
		m_system.GetInput().CheckInput();

		//Update game objects
		Update();

		//Render game objects
		Render();

		//Calculate and restrict the frame rate
		m_system.CalculateFrames();
		//Get the delta tick per frame
		m_deltaTicks = m_system.GetDeltaTicks();
	}

}

void Game::Update()
{
	m_state = m_menu.GetState();

	switch(m_state)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		m_playerCam.Update(m_deltaTicks, m_playerController.GetPlayer(), m_system.GetInput(),
			m_level);

		if(!m_flashback.GetFlashback())
		{
			m_enemyController.Update(m_deltaTicks, m_playerController.GetPlayer(), m_level,
				m_playerCam);

			m_playerController.Update(m_deltaTicks, m_system.GetInput(), m_playerCam,
				m_level, m_enemyController);

			m_gameHud.Update(m_deltaTicks, m_enemyController.GetScore(), m_playerController.GetPlayer().GetLives());
		}

		m_level.Update(m_deltaTicks, m_playerCam);

		m_flashback.Update(m_deltaTicks, m_playerController, m_enemyController, m_gameHud, m_system.GetInput());

		break;
	};

	if(!m_playerController.GetPlayer().GetAlive())
	{
		m_menu.SetState(1);
	}
	if(m_menu.GetReset())
	{
		m_playerController = m_resetPlayerController;
		m_enemyController = m_resetEnemyController;
		m_playerCam = m_resetCam;
		m_flashback = m_resetFlash;
		m_gameHud = m_resetHud;

	}

	m_menu.Update(m_system.GetInput(), m_enemyController.GetScore());

}

void Game::Render()
{
	//Clear the render screen
	m_system.StartRender();

	//------------ RENDER HERE -----------------//

	if(m_state == 2)
	{
		m_level.Render(m_system.GetRenderer(), m_playerCam);

		m_enemyController.Render(m_system.GetRenderer(), m_playerCam);
		m_playerController.Render(m_system.GetRenderer(), m_playerCam);
		m_flashback.Render(m_system.GetRenderer());
		m_gameHud.Render(m_system.GetRenderer());
	}

	m_menu.Render(m_system.GetRenderer());

	//^^^^^^^^^^^^ RENDER HERE ^^^^^^^^^^^^^^//

	//Presents the objects to the renderer
	m_system.EndRender();
}

void Game::Shutdown()
{
	//Unload game content
	m_resourceManager.UnloadResources();

	//m_playerController.UnloadContent();
	//m_enemyController.UnloadContent();
	//m_flashback.UnloadContent();
	//m_gameHud.UnloadContent();
	//m_resetFlash.UnloadContent();
	//m_resetHud.UnloadContent();

	//Shut down sdl and other libs
	m_system.Shutdown();
}

