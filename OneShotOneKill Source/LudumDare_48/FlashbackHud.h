#ifndef FLASHBACK_HUD_H
#define FLASHBACK_HUD_H

#include <iostream>
#include <sstream>

#include "ResourceManager.h"
#include "FlashbackBarObject.h"
#include "FlashbackIconObject.h"

#include "FontObject.h"

class FlashbackHud
{
public:
	FlashbackHud();
	~FlashbackHud();

	bool LoadContent(ResourceManager& resources, int windowWidth);
	void UnloadContent();

	void Update(float dt);
	void Render(SDL_Renderer* renderer);

	void SetFlashbackRemaining( int flashbackRemaining);
	void SubtractTimer( int time );
	void SetFlashback( bool flashback );

private:
	float m_flashBackRemaining;
	int m_timerCount,
		m_secounds,
		m_minutes,
		m_windowWidth;
	string m_timerText;
	bool m_isFlashback;

	FlashbackBarObject m_flashbackBar;
	FontObject m_timerFont;
	FlashbackIconObject m_flashbackIcon;
};

#endif