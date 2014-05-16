#include "FlashbackHud.h"

FlashbackHud::FlashbackHud() : m_flashBackRemaining(0.0f), m_timerCount(0), m_secounds(0),
	m_minutes(0), m_timerFont(), m_timerText(""), m_windowWidth(0), m_isFlashback(false),
	m_flashbackIcon(), m_flashbackBar()
{

}

FlashbackHud::~FlashbackHud()
{
}

bool FlashbackHud::LoadContent(ResourceManager& resources, int windowWidth)
{
	m_windowWidth = windowWidth;

	if(!m_flashbackBar.LoadContent(resources, windowWidth))
	{
		return false;
	}

	if(!m_flashbackIcon.LoadContent(resources))
	{
		return false;
	}

	m_flashbackIcon.SetPosX(windowWidth - 150);
	m_flashbackIcon.SetPosY(10);
	m_flashbackIcon.SetScale(2);
	m_flashbackIcon.SetFlip(true);

	return true;
}

void FlashbackHud::UnloadContent()
{
	m_flashbackBar.UnloadContent();
	m_flashbackIcon.UnloadContent();
	m_timerFont.UnloadFont();
}

void FlashbackHud::Update(float dt)
{
	m_flashbackBar.Update(dt, m_flashBackRemaining);

	m_secounds = (int)m_timerCount / 30;
	m_minutes = (int)m_secounds / 60;

	std::stringstream sec;
	sec << m_secounds;
	std::stringstream mins;
	mins << m_minutes;
	m_timerText = (mins.str() + " : " + sec.str());

	if(!m_isFlashback)
	{
		m_timerCount += 1;
		m_flashbackIcon.SetFrameX(0);
	}
	else
	{
		m_flashbackIcon.SetFrameX(1);
	}
}

void FlashbackHud::Render(SDL_Renderer* renderer)
{
	Vector2D clip;
	clip.x = 0;
	clip.y = 0;

	m_timerFont.LoadFont(renderer, "Data/Fonts/gamefont.ttf", m_timerText, m_windowWidth - 100, 10, 1.0f, 0.0f);
	m_timerFont.Render(renderer, clip);
	m_flashbackBar.Render(renderer);
	m_flashbackIcon.Render(renderer);
}

void FlashbackHud::SetFlashbackRemaining( int flashbackRemaining)
{
	m_flashBackRemaining = flashbackRemaining;
}

void FlashbackHud::SubtractTimer( int time )
{
	m_timerCount -= time;
}

void FlashbackHud::SetFlashback( bool flashback )
{
	m_isFlashback = flashback;
}