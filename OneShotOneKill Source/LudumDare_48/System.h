#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "Input.h"
#include "Timer.h"

class System
{
public:
	System(int screenWidth, int screenHeight);
	~System();

	bool Initialise();
	void Shutdown();

	bool Done();

	void StartRender();
	void EndRender();

	void CalculateFrames();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Texture* GetBuffer();
	SDL_Event GetEvent();
	
	Timer GetFpsTimer();
	float GetFps();
	float GetDeltaTicks();
	
	int GetScreenWidth();
	int GetScreenHeight();

	Input GetInput();

private:
	std::string m_title;

	int m_screenWidth,
		m_screenHeight,
		m_maxFPS,
		m_frameCount;

	float m_currentAvgFPS;

	bool m_fullscreen;

	Timer m_fpsTimer;
	Timer m_capTimer;

	SDL_Event m_event;
	SDL_Window* m_window;
	SDL_Texture* m_buffer;
	SDL_Renderer* m_renderer;

	Input m_input;
};

#endif