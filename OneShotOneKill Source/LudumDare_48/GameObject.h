#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>

#include "MathHelper.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "Camera.h"

using namespace MathHelper;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual bool LoadContent(ResourceManager& resources);
	virtual void UnloadContent();

	virtual void Update(float dt);
	virtual void Render(SDL_Renderer* renderer, Camera cam);

	void CycleAnimation(int startFrame, int endFrame, float interval);
	bool CheckCollision( SDL_Rect a, SDL_Rect b);

	Vector2D GetPosition();
	int GetFrameX();
	bool GetFlip();
	float GetAngle();
	bool GetShown();
	SDL_Rect GetCollisionBox();
	int GetWidth();
	int GetHeight();
	int GetScale();
	Vector2D GetForwardVec();

	void SetScale( int scale);
	void SetPosX( float posX );
	void SetPosY( float posY );
	void SetFrameX( int frameX );
	void SetFlip( bool flip );
	void SetAngle( float angle );
	void SetShown( bool show );
	void SetColour( Uint8 red, Uint8 green, Uint8 blue);
	void SetAlpha( Uint8 alpha);
	void SetBlendMode( SDL_BlendMode blending );

protected:

	Image m_image;
	Timer m_animTimer;

	int m_startX,
		m_startY,
		m_width,
		m_height,
		m_frameX,
		m_frameY,
		m_originX,
		m_originY,
		m_scale;

	Vector2D m_position,
		m_forwardVec,
		m_backwardVec,
		m_rightVec,
		m_leftVec;

	float m_angle;

	bool m_flip,
		m_show;

	SDL_Rect m_collisionBox;
};

#endif