#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::LoadResources(SDL_Renderer* renderer)
{
	if(!m_imageManager.LoadImages( renderer ))
	{
		return false;
	}
	
	return true;
}

void ResourceManager::UnloadResources()
{
	m_imageManager.UnloadImages();
}

ImageManager& ResourceManager::GetImages()
{
	return m_imageManager;
}