#include "GameObject.h"

GameObject::GameObject() : m_startX(0), m_startY(0), m_width(0), m_height(0), m_frameX(0),
	m_originX(0), m_originY(0), m_angle(0.0f), m_flip(false), m_show(false),
	m_scale(1), m_animTimer(), m_image(), m_frameY(0), m_position(), m_forwardVec(),
	m_backwardVec(), m_rightVec(), m_leftVec()
{
}

GameObject::~GameObject()
{
}

bool GameObject::LoadContent(ResourceManager& resources)
{
	return true;
}

void GameObject::UnloadContent()
{
}

void GameObject::Update(float dt)
{
	//Calculate the back vec
	m_backwardVec.x = sin(-m_angle);
	m_backwardVec.y = cos(-m_angle);

	//Calculate the forward vec
	m_forwardVec.x = -m_backwardVec.x;
	m_forwardVec.y = -m_backwardVec.y;

	//Calculate the left vec
	m_leftVec.x = sin(-m_angle + DegreesToRadians(90.0f));
	m_leftVec.y = cos(-m_angle + DegreesToRadians(90.0f));

	//Calculate the right vec
	m_rightVec.x = -m_leftVec.x;
	m_rightVec.y = -m_leftVec.y;

	m_backwardVec.Normalize();
	m_forwardVec.Normalize();
	m_leftVec.Normalize();
	m_rightVec.Normalize();

}

void GameObject::Render( SDL_Renderer* renderer, Camera cam)
{

	//the source rect from the image
	SDL_Rect srcRect = {m_startX + (m_width * m_frameX), m_startY + (m_height * m_frameY),
		m_width, m_height};

	//the destination rect for where it needs to be on screen
	SDL_Rect dstRect = { (m_position.x - cam.GetPosX()), (m_position.y - cam.GetPosY()),
		m_width*(m_scale * cam.GetZoomLevel()), m_height * (m_scale * cam.GetZoomLevel()) };

	//the center point of origin of the sprite
	SDL_Point origin;
	origin.x = m_originX * (m_scale * cam.GetZoomLevel());
	origin.y = m_originY * (m_scale * cam.GetZoomLevel());

	double dAngle = (double)RadiansToDegrees(m_angle);

	//if the sprite is flipped or not
	if(m_flip)
	{
	
		SDL_RenderCopyEx(renderer, m_image.m_texture, &srcRect, &dstRect, (double)dAngle, &origin, SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderCopyEx(renderer, m_image.m_texture, &srcRect, &dstRect, (double)dAngle, &origin, SDL_FLIP_HORIZONTAL);
	}
}

void GameObject::CycleAnimation(int startFrame, int endFrame, float interval)
{
	if(m_animTimer.IsStarted())
	{
		float animTick = (m_animTimer.GetTicks());
		if(animTick > interval)
		{
			m_frameX += 1;
			m_animTimer.Stop();
		}
	}
	else
	{
		m_animTimer.Start();
	}

	if(m_frameX >= endFrame)
	{
		m_frameX = startFrame;
	}
}

bool GameObject::CheckCollision(SDL_Rect a, SDL_Rect b)
{
	float leftA = a.x,
		rightA = a.x + a.w,
		topA = a.y,
		bottomA = a.y + a.h;

	float leftB = b.x,
		rightB = b.x + b.w,
		topB = b.y,
		bottomB = b.y + b.h;

	if(bottomA <= topB)
	{
		return false;
	}
	if(topA >= bottomB)
	{
		return false;
	}
	if(rightA <= leftB)
	{
		return false;
	}
	if(leftA >= rightB)
	{
		return false;
	}

	return true;
}

Vector2D GameObject::GetPosition()
{
	return m_position;
}
int GameObject::GetFrameX()
{
	return m_frameX;
}
bool GameObject::GetFlip()
{
	return m_flip;
}
float GameObject::GetAngle()
{
	return m_angle;
}
bool GameObject::GetShown()
{
	return m_show;
}
SDL_Rect GameObject::GetCollisionBox()
{
	return m_collisionBox;
}
int GameObject::GetWidth()
{
	return m_width;
}
int GameObject::GetHeight()
{
	return m_height;
}
int GameObject::GetScale()
{
	return m_scale;
}
Vector2D GameObject::GetForwardVec()
{
	return m_forwardVec;
}

void GameObject::SetPosX( float posX )
{
	m_position.x = posX;
}
void GameObject::SetPosY( float posY )
{
	m_position.y = posY;
}
void GameObject::SetFrameX( int frameX )
{
	m_frameX = frameX;
}
void GameObject::SetFlip( bool flip )
{
	m_flip = flip;
}
void GameObject::SetAngle( float angle )
{
	m_angle = angle;
}
void GameObject::SetShown( bool show )
{
	m_show = show;
}

void GameObject::SetColour( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod(m_image.m_texture, red, green, blue);
}
void GameObject::SetAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( m_image.m_texture, alpha);
}
void GameObject::SetBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( m_image.m_texture, blending );
}
void GameObject::SetScale( int scale )
{
	m_scale = scale;
}