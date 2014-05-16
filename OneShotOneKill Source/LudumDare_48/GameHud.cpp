#include "GameHud.h"

GameHud::GameHud() : m_lives(3), m_scoreFont()
{
}

GameHud::~GameHud()
{
}

bool GameHud::LoadContent(ResourceManager& resources, int screenWidth)
{
	for(unsigned int l = 0; l < m_lives; l++)
	{
		GameLivesIcon newIcon;

		if(!newIcon.LoadContent(resources))
		{
			return false;
		}

		newIcon.SetPosX( screenWidth / 2 - 50 + (l*50));
		newIcon.SetPosY( 10 );

		m_liveIcons.push_back(newIcon);
	}

	return true;
}

void GameHud::UnloadContent()
{
	for(unsigned int i = 0; i < m_liveIcons.size(); i++)
	{
		m_liveIcons[i].UnloadContent();
	}
}

void GameHud::Update( float dt, int score, int lives )
{
	std::stringstream scr;
	scr << score;
	m_score = ("Score: " + scr.str());

	for(unsigned int i = 0; i < m_liveIcons.size(); i++)
	{
		if(i >= lives)
		{
			m_liveIcons[i].CycleAnimation(0, 4, 1.0f);
		}
		if(m_liveIcons[i].GetFrameX() == 3)
		{
			m_liveIcons[i].SetShown(false);
		}

		m_liveIcons[i].Update(dt);
	}
}

void GameHud::Render(SDL_Renderer* renderer)
{
	Vector2D clip;
	clip.x = 0;
	clip.y = 0;

	m_scoreFont.LoadFont(renderer, "Data/Fonts/gamefont.ttf", m_score, 10, 10, 1.0f, 0.0f);

	for(unsigned int i = 0; i < m_liveIcons.size(); i++)
	{
		if(m_liveIcons[i].GetShown())
		{
			m_liveIcons[i].Render(renderer);
		}
	}

	m_scoreFont.Render(renderer, clip);
}

