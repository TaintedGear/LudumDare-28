#include "FontObject.h"

FontObject::FontObject() : m_fontFile(""), m_text(""), m_posX(0), m_posY(0),
	m_font(NULL), m_fontTexture(NULL), m_scale(1.0f), m_angle(0.0f), m_flip(false),
	m_width(0), m_height(0)
{
}

FontObject::~FontObject()
{
}

bool FontObject::LoadFont(SDL_Renderer* renderer, string fontFile, string text, int posX, int posY,
	float scale, float angle)
{
	m_fontFile = fontFile;
	m_text = text;
	m_posX = posX;
	m_posY = posY;
	m_scale = scale;
	m_angle = angle;

	m_textColor.r = 0;
	m_textColor.g = 255;
	m_textColor.b = 0;
	m_textColor.a = 255;

	if(!LoadFontFromTexture(renderer))
	{
		return false;
	}
	
	return true;
}

void FontObject::UnloadFont()
{
	SDL_DestroyTexture(m_fontTexture);
	m_fontTexture = NULL;

	//TTF_CloseFont(m_font);
	m_font = NULL;
}

void FontObject::Update(float dt)
{

}

void FontObject::Render(SDL_Renderer* renderer, Vector2D clip)
{
	//the destination rect for where it needs to be on screen
	SDL_Rect dstRect = { (m_posX - clip.x), (m_posY - clip.y),
		m_width * m_scale, m_height * m_scale };

	double dAngle = (double)DegreesToRadians(m_angle);

	SDL_Point origin;
	origin.x = m_width * m_scale;
	origin.y = m_height * m_scale;

	if(!m_flip)
	{
		SDL_RenderCopyEx(renderer, m_fontTexture, NULL, &dstRect, m_angle, &origin, SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_fontTexture, NULL, &dstRect, m_angle, &origin, SDL_FLIP_HORIZONTAL);
	}
}

bool FontObject::LoadFontFromTexture(SDL_Renderer* renderer)
{
	UnloadFont();

	m_font = TTF_OpenFont(m_fontFile.c_str(), 28);

	m_fontSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);

	if(m_fontSurface == NULL)
	{
		return false;
	}
	else
	{
		m_fontTexture = SDL_CreateTextureFromSurface(renderer, m_fontSurface);

		if(m_fontTexture == NULL)
		{
			return false;
		}
		else
		{
			m_width = m_fontSurface->w;
			m_height = m_fontSurface->h;
		}
	}

	return true;
}

void FontObject::SetColour(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_fontTexture, red, green, blue);
}
void FontObject::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_fontTexture, alpha);
}
void FontObject::SetText( string text )
{
	m_text = text;
}
void FontObject::SetAngle( float angle )
{
	m_angle = angle;
}
void FontObject::SetPosX( int x )
{
	m_posX = x;
}
void FontObject::SetPosY( int y )
{
	m_posY = y;
}
void FontObject::SetScale( int scale )
{
	m_scale = scale;
}
void FontObject::SetFlip( bool flip )
{
	m_flip = flip;
}