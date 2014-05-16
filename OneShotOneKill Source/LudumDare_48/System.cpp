#include "System.h"

System::System(int screenWidth, int screenHeight) : m_window(NULL), m_buffer(NULL), m_renderer(NULL),
	m_fullscreen(false), m_screenWidth(screenWidth), m_screenHeight(screenHeight),
	m_title("LudumDare 48"), m_maxFPS(30), m_currentAvgFPS(0.0f), m_frameCount(0),
	m_capTimer(), m_fpsTimer(), m_input()
{
}

System::~System()
{
}

bool System::Initialise()
{
	//Initialise SDL
	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	//initialise TTF
	if(TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	//Initialise the window
	if(!m_fullscreen)
	{
		m_window = SDL_CreateWindow(m_title.c_str(), 100, 100, m_screenWidth, m_screenHeight,
			SDL_WINDOW_SHOWN);
	}
	else
	{
		m_window = SDL_CreateWindow(m_title.c_str(), 0, 0, m_screenWidth, m_screenHeight,
			SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	//Check to see if the window has been created
	if(m_window == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	//Initialise the renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//check to see if the renderer has been created
	if(m_renderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	//Set the draw colour
	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

bool System::Done()
{
	// Check for a system message
	while(SDL_PollEvent(&m_input.GetEvent()) != 0)
	{
		//if the system message askes to quit then break out of game loop
		if(m_input.GetEvent().type == SDL_QUIT)
		{
			return true;
		}
	}
	//Reset the fps timer
	m_capTimer.Start();

	return false;
}

void System::StartRender()
{
	//Set the draw colour
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
}

void System::EndRender()
{
	SDL_RenderPresent(m_renderer);
}

void System::CalculateFrames()
{
	//calculate the average fps
	m_currentAvgFPS = (float)m_frameCount / (m_fpsTimer.GetTicks() / 1000);

	//restrict the frame rate to the max fps
	if(m_capTimer.GetTicks() < (unsigned)(1000 / m_maxFPS))
	{
		SDL_Delay( (1000/ m_maxFPS) - m_capTimer.GetTicks() );
	}

	//add on the current frames
	m_frameCount += 1;
}

void System::Shutdown()
{
	//Release the renderer and the window
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_renderer = NULL;
	m_window = NULL;

	//Close down SDL and other libs
	TTF_Quit();
	SDL_Quit();
}

SDL_Window* System::GetWindow()
{
	return m_window;
}

SDL_Renderer* System::GetRenderer()
{
	return m_renderer;
}

SDL_Texture* System::GetBuffer()
{
	return m_buffer;
}

SDL_Event System::GetEvent()
{
	return m_event;
}

float System::GetFps()
{
	return m_currentAvgFPS;
}

float System::GetDeltaTicks()
{
	return ((float)m_capTimer.GetTicks() / 1000);
}

Timer System::GetFpsTimer()
{
	return m_fpsTimer;
}

Input System::GetInput()
{
	return m_input;
}

int System::GetScreenWidth()
{
	return m_screenWidth;
}

int System::GetScreenHeight()
{
	return m_screenHeight;
}