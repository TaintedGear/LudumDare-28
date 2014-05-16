#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "ImageManager.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool LoadResources(SDL_Renderer* renderer);
	void UnloadResources();

	ImageManager& GetImages();
private:

	ImageManager m_imageManager;
};

#endif