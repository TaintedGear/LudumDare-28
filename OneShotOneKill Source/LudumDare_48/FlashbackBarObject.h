#ifndef FLASHBACK_BAR_OBJECT_H
#define FLASHBACK_BAR_OBJECT_H

#include "GameObject.h"
#include "FlashbackBarSegementObject.h"

class FlashbackBarObject : public GameObject
{
public:
	FlashbackBarObject();
	~FlashbackBarObject();

	bool LoadContent(ResourceManager& resources, int windowWidth);
	void UnloadContent();

	void Update(float dt, int flashBackRemaining);
	void Render(SDL_Renderer* renderer);

private:

	vector<FlashbackBarSegementObject> m_segements;
};

#endif