#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <sstream>

#include "ResourceManager.h"
#include "Input.h"
#include "Timer.h"

#include "FontObject.h"

class Menu
{
public:
	Menu();
	~Menu();

	bool LoadContent(ResourceManager& resources);

	void Update(Input& input, int score);
	void Render(SDL_Renderer* renderer);

	int GetState();
	void SetState( int state );
	bool GetReset();

private:
	int m_state;
	bool m_reset;

	enum m_states {START_SCREEN = 0, END_SCREEN = 1, NO_SCREEN = 2};

	string m_title,
		m_instruct,
		m_score,
		m_time;

	FontObject m_titleFont,
		m_instructFont,
		m_scoreFont,
		m_timeFont;

	Timer m_timer;
};

#endif