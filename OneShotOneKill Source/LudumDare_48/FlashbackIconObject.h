#ifndef FLASHBACK_ICON_OBJECT_H
#define FLASHBACK_ICON_OBJECT_H

#include "GameObject.h"

class FlashbackIconObject : public GameObject
{
public:
	FlashbackIconObject();
	~FlashbackIconObject();

	bool LoadContent(ResourceManager& resources);
	void UnloadContent();

	void Update(float dt);
	void Render(SDL_Renderer* renderer);

private:
};

#endif