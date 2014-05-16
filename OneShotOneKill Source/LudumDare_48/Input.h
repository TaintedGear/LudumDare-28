#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
public:
	Input();
	~Input();

	bool GetKeyState(int key);
	bool GetMouseButtonState(int key);
	int GetMouseX();
	int GetMouseY();

	void CheckInput();

	SDL_Event& GetEvent();

private:

	//const Uint8* m_currentState;
	//const Uint8* m_previousState;

	SDL_Event m_event;

	int m_mouseX,
		m_mouseY;
};

#endif