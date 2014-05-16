#ifndef GAME_HUD_H
#define GAME_HUD_H

#include <iostream>
#include <sstream>
#include <vector>

#include "ResourceManager.h"
#include "GameLivesIcon.h"
#include "FontObject.h"

using std::vector;

class GameHud
{
public:
	GameHud();
	~GameHud();

	bool LoadContent(ResourceManager& resources, int screenWidth);
	void UnloadContent();

	void Update(float dt, int score, int lives);
	void Render(SDL_Renderer* renderer);

private:
	int m_lives;
	string m_score;

	vector<GameLivesIcon> m_liveIcons;

	FontObject m_scoreFont;
};

#endif