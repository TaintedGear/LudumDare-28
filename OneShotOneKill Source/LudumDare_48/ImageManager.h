#ifndef IMAGE_MANAGER_H
#define IMAGE_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include <SDL.H>

using std::string;
using std::vector;

struct Image
{
	Image()
	{
		m_texture = NULL;
		m_imageWidth = 0;
		m_imageHeight = 0;
		m_imageLabel = "NULL";
	}

	void Release()
	{
		if(m_texture != NULL)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = NULL;

		}
	}

	std::string m_imageLabel;
	SDL_Texture* m_texture;
	float m_imageWidth,
		m_imageHeight;
};

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	bool LoadImages(SDL_Renderer* renderer);
	void UnloadImages();

	Image& GetImage(string label);
private:

	bool LoadFromFile(SDL_Renderer* renderer, string filename);

	vector<Image> m_images;
};

#endif