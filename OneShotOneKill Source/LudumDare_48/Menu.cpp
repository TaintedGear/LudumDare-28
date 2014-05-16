#include "Menu.h"

Menu::Menu() : m_state(0), m_titleFont(), m_instructFont(), m_scoreFont(), m_timeFont(),
	m_title(""), m_instruct(""), m_score(""), m_time(""), m_timer(), m_reset(false)
{
}

Menu::~Menu()
{
}

bool Menu::LoadContent(ResourceManager& resources)
{
	m_title = "Ludum Dare 48";
	m_instruct = "You only get one shot!\n WASD to move\n Space to reverse time\n, Click anywhere to play!";

	return true;
}

void Menu::Update(Input& input, int score)
{
	std::stringstream scr;
	scr << score;
	m_score = ("You'r final score: " + scr.str());

	switch(m_state)
	{
	case START_SCREEN:

		m_reset = false;

		if(input.GetMouseButtonState(1))
		{
			if(!m_timer.IsStarted())
			{
				m_timer.Start();
			}
		}

		if(m_timer.IsStarted())
		{
			if((m_timer.GetTicks() / 1000) >= 1)
			{
				m_state = 2;
				m_timer.Stop();
			}
		}

		break;

	case END_SCREEN:

		if(input.GetMouseButtonState(1))
		{
			m_state = 0;
			m_reset = true;
		}

		break;

	case NO_SCREEN:

		break;
	}

}

void Menu::Render(SDL_Renderer* renderer)
{
	Vector2D clip;
	clip.x = 0;
	clip.y = 0;

	switch(m_state)
	{
	case START_SCREEN:
		m_titleFont.LoadFont(renderer, "Data/Fonts/gamefont.ttf", m_title, 10, 200, 1.0f, 0.0f);
		m_instructFont.LoadFont(renderer, "Data/Fonts/gamefont.ttf", m_instruct, 10, 300, 0.5f, 0.0f);
		m_titleFont.Render(renderer, clip);
		m_instructFont.Render(renderer, clip);
		break;

	case END_SCREEN:
		m_scoreFont.LoadFont(renderer, "Data/Fonts/gamefont.ttf", m_score, 200, 200, 1.0f, 0.0f);
		m_scoreFont.Render(renderer, clip);
		break;

	case NO_SCREEN:

		break;
	}
}

int Menu::GetState()
{
	return m_state;
}
void Menu::SetState( int state )
{
	m_state = state;
}

bool Menu::GetReset()
{
	return m_reset;
}