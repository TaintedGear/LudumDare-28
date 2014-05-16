#include "ImageManager.h"


ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
}

bool ImageManager::LoadImages(SDL_Renderer* renderer)
{
	if(!LoadFromFile(renderer, "Player"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "Enemy"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "TileSheet"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "Weapons"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "Pickups"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "Projectiles"))
	{
		return false;
	}
	if(!LoadFromFile(renderer, "Hud"))
	{
		return false;
	}

	return true;
}

void ImageManager::UnloadImages()
{

	for(unsigned int i = 0; i < m_images.size(); i++)
	{
		m_images[i].Release();
	}
}

bool ImageManager::LoadFromFile(SDL_Renderer* renderer, string filename)
{
	// Get the proper file path
	string filePath = "Data/Images/" + filename + ".bmp";

	//Create a new image object
	Image newImage;

	// Create a surface from the file
	SDL_Surface* loadedSurface = SDL_LoadBMP(filePath.c_str());

	if(loadedSurface != NULL)
	{
		
		//Set the color key of the surface to be ignored
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255) );

		//Create the texture from the surface
		newImage.m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if(newImage.m_texture != NULL)
		{
			//Set up the new image object
			newImage.m_imageHeight = loadedSurface->h;
			newImage.m_imageWidth = loadedSurface->w;
			newImage.m_imageLabel = filename;

			m_images.push_back( newImage );
		}
		else
		{
			std::cout << "Unable to create texture from surface: " << filePath << "ERROR: " << SDL_GetError();
			return false;
		}

		SDL_FreeSurface( loadedSurface );
	}
	else
	{
		std::cout << "Unable to create surface from image: " << filePath << "ERROR: " << SDL_GetError();
		return false;
	}

	return true;
}

Image& ImageManager::GetImage(string label)
{
	// Return an error image which label is ERROR
	Image errorImg;
	errorImg.m_imageLabel = "ERROR";

	if(label.size() != 0)
	{
		for(unsigned int i = 0; i < m_images.size(); i++)
		{
			if(m_images[i].m_imageLabel == label)
			{
				return m_images[i];
			}
		}
	}

	return errorImg; // change this
}