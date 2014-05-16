#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "MathHelper.h"
#include "GameObject.h"

class PhysicsObject : public GameObject
{
public:
	PhysicsObject();
	virtual ~PhysicsObject();

	virtual void Update(float dt);

	Vector2D GetVelocity();
	void SetVelocityX( int x );
	void SetVelocityY( int y );
	void SetAccelerationX( int x );
	void SetAccelerationY( int y );
	void SetSpeed( int speed );

protected:
	Vector2D m_velocity;
	Vector2D m_acceleration;

	float m_speed,
		m_maxSpeed,
		m_drag;

	bool m_applyDrag;
	
};

#endif