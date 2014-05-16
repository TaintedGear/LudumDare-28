#ifndef GAME_LIVES_ICON_H
#define GAME_LIVES_ICON_H

#include "GameObject.h"

class GameLivesIcon : public GameObject
{
public:
	GameLivesIcon();
	~GameLivesIcon();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt);
	void Render(SDL_Renderer* renderer);

private:
};

#endif