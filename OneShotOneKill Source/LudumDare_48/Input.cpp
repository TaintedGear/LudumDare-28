#include "Input.h"

Input::Input() : m_mouseX(0), m_mouseY(0)
{
}

Input::~Input()
{
}

void Input::CheckInput()
{
	SDL_PumpEvents();

	////assign the previous state
	//m_previousState = m_currentState;

	//m_currentState = SDL_GetKeyboardState(NULL);

}

bool Input::GetKeyState(int key)
{
	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if(keyState[key])
	{
		return true;
	}
	
	return false;
}

bool Input::GetMouseButtonState(int key)
{
	if(SDL_GetMouseState(&m_mouseX, &m_mouseY)&SDL_BUTTON(key))
	{
		return true;
	}

	return false;	
}

int Input::GetMouseX()
{
	Uint32 mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);

	return m_mouseX;
}

int Input::GetMouseY()
{
	Uint32 mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);

	return m_mouseY;
}

SDL_Event& Input::GetEvent()
{
	return m_event;
}