#ifndef FONT_OBJECT_H
#define FONT_OBJECT_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Camera.h"
#include "MathHelper.h"

using std::string;
using namespace MathHelper;

class FontObject
{
public:
	FontObject();
	~FontObject();

	bool LoadFont(SDL_Renderer* renderer, string fontFile, string text, 
		int posX, int posY, float scale, float angle);
	void UnloadFont();

	void Update(float dt);
	void Render(SDL_Renderer* renderer, Vector2D clip);

	void SetColour(Uint8 red, Uint8 green, Uint8 blue);
	void SetAlpha(Uint8 alpha);
	void SetText( string text );
	void SetAngle( float angle );
	void SetPosX( int x );
	void SetPosY( int y );
	void SetScale( int scale );
	void SetFlip( bool flip );

private:
	bool LoadFontFromTexture(SDL_Renderer* renderer);

	string m_fontFile;
	string m_text;

	TTF_Font* m_font;

	SDL_Color m_textColor;
	SDL_Surface* m_fontSurface;
	SDL_Texture* m_fontTexture;

	int m_posX,
		m_posY,
		m_width,
		m_height;

	float m_scale,
		m_angle;

	bool m_flip;

};

#endif