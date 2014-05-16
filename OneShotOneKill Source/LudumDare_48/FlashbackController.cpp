#include "FlashbackController.h"

FlashbackController::FlashbackController() : m_statePerSec(30), m_totalFlashbackSecs(2),
	m_fps(30), m_currentFrame(0), m_currentState(0), m_flashBack(false),
	m_flashbackFrame(0), m_flashBackReady(false), m_totalFlashBack(0), m_flashBackRecharge(2)
{
}

FlashbackController::~FlashbackController()
{
}

void FlashbackController::LoadStartStates( PlayerController& playerController,
		EnemyController& enemyController, GameHud& gameHud, int fps)
{
	m_fps = fps;

	for(unsigned int s = 0; s < m_statePerSec * m_totalFlashbackSecs; s++)
	{
		m_previousPlayerState.push_back(playerController);
		m_previousEnemyState.push_back(enemyController);
		m_previousHudState.push_back(gameHud);
	}
}

void FlashbackController::Update( float dt, PlayerController& playerController,
	EnemyController& enemyController, GameHud& gameHud, Input& input)
{
	int frameToRecord = (int)m_fps / m_statePerSec;

	//Deal with the flash back
	if(m_flashBack)
	{
		if(m_flashbackFrame != m_currentState + 1)
		{
			playerController = m_previousPlayerState[m_flashbackFrame];
			enemyController = m_previousEnemyState[m_flashbackFrame];
			gameHud = m_previousHudState[m_flashbackFrame];

			//now decrement through the current states; ( not sure to use a nother variable here)
			m_flashbackFrame -= 1;
			m_totalFlashBack -= (1 + m_flashBackRecharge);
			m_flashbackHud.SubtractTimer(1);
		}
		else
		{
			m_flashbackFrame = 0;
			m_totalFlashBack = 0;
			m_flashBackReady = false;
			m_flashBack = false;
			m_flashbackHud.SetFlashback(false);
		}
	}
	else
	{
		//Increment the frame counter
		m_currentFrame += 1;
		//Increment the total flash back record
		m_totalFlashBack += 1;
	}

	//Check to see if the user wants to flash back
	if(input.GetKeyState(SDL_SCANCODE_SPACE) && (!m_flashBack) && (m_flashBackReady))
	{
   		m_flashbackFrame = m_currentState - 1;
		m_flashBack = true;
		m_flashbackHud.SetFlashback(true);
	}

	//COMMENTED OUT UNTILL I CAN WORK OUT HOW TO STOP THE WEIRD LOOP OF THE TIMELINE
	//else if ((!input.GetKeyState(SDL_SCANCODE_SPACE)) && (m_flashBack))
	//{
	//	m_currentState = m_flashbackFrame;
	//	m_flashBack = false;
	//}

	// RecordStates
	//If the current frames is the frame to record then take the states and store in a vector
	if((m_currentFrame == frameToRecord) && (!m_flashBack))
	{
		m_previousPlayerState[m_currentState] = playerController;
		m_previousEnemyState[m_currentState] = enemyController;
		m_previousHudState[m_currentState] = gameHud;

		m_currentState += 1;
		m_currentFrame = 0;
	}

	//Restrict the state to the amount per the total flash back (Stops from going out of bounds)
	if(m_currentState > m_statePerSec * m_totalFlashbackSecs - 1)
	{
		m_currentState = 0;
	}
	else if(m_currentState < 0)
	{
  		m_currentState = m_statePerSec * m_totalFlashbackSecs - 1;
	}
	if(m_flashbackFrame < 0)
	{
		m_flashbackFrame = m_statePerSec * m_totalFlashbackSecs - 1;
	}
	if(m_totalFlashBack >  (m_statePerSec * m_totalFlashbackSecs - 1) + (m_statePerSec * m_flashBackRecharge))
	{
		m_totalFlashBack = (m_statePerSec * m_totalFlashbackSecs - 1) + (m_statePerSec * m_flashBackRecharge);
		m_flashBackReady = true;
	}

	//Get the percentage of the flashback remanining
	float percentageFlashback = (float)m_totalFlashBack / 
		((m_statePerSec * m_totalFlashbackSecs - 1) + (m_statePerSec * m_flashBackRecharge)) * 100;

	m_flashbackHud.SetFlashbackRemaining(  percentageFlashback  );

	// Update the Hud
	m_flashbackHud.Update(dt);
}

bool FlashbackController::LoadContent(ResourceManager& resources, int windowWidth)
{
	if(!m_flashbackHud.LoadContent(resources, windowWidth))
	{
		return false;
	}

	return true;
}

void FlashbackController::Render(SDL_Renderer* renderer)
{
	//Render the hud
	m_flashbackHud.Render(renderer);
}

void FlashbackController::UnloadContent()
{
	m_flashbackHud.UnloadContent();
}

bool FlashbackController::GetFlashback()
{
	return m_flashBack;
}