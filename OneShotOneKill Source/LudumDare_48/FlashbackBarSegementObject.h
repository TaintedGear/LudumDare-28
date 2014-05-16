#ifndef FLASHBACK_BAR_SEGEMENT_OBJECT_H
#define FLASHBACK_BAR_SEGEMENT_OBJECT_H

#include "GameObject.h"

class FlashbackBarSegementObject : public GameObject
{
public:
	FlashbackBarSegementObject();
	~FlashbackBarSegementObject();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt);
	void Render(SDL_Renderer* renderer);

private:

};

#endif