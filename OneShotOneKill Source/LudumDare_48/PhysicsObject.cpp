#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() : GameObject(), m_speed(0.0f), m_maxSpeed(0.0f), m_drag(0.99f),
	m_applyDrag(true), m_velocity(), m_acceleration()
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update(float dt)
{
	Vector2D newVelocity;
	Vector2D newPosition;

	//Calc the new velocity using acceleration
	newVelocity.x = m_velocity.x + m_acceleration.x * dt;
	newVelocity.y = m_velocity.y + m_acceleration.y * dt;

	//Create Drag
	if(m_applyDrag)
	{
		newVelocity.x *= m_drag;
		newVelocity.y *= m_drag;
	}

	//Restrict speed
	if(newVelocity.x >= m_maxSpeed)
	{
		newVelocity.x = m_maxSpeed;
	}
	else if(newVelocity.y >= m_maxSpeed)
	{
		newVelocity.y = m_maxSpeed;
	}

	if(newVelocity.x <= -m_maxSpeed)
	{
		newVelocity.x = -m_maxSpeed;
	}
	else if(newVelocity.y <= -m_maxSpeed)
	{
		newVelocity.y = -m_maxSpeed;
	}
	
	//Calculate the new position using the new velocity
	newPosition.x = m_position.x + newVelocity.x * dt;
	newPosition.y = m_position.y + newVelocity.y * dt;

	////Store the new position and new velocity
	m_position.x = newPosition.x;
	m_position.y = newPosition.y;
	m_velocity.x = newVelocity.x;
	m_velocity.y = newVelocity.y;

	////Reset the acceleration
	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;

	GameObject::Update(dt);
}

Vector2D PhysicsObject::GetVelocity()
{
	return m_velocity;
}
void PhysicsObject::SetVelocityX( int x )
{
	m_velocity.x = x;
}
void PhysicsObject::SetVelocityY( int y )
{
	m_velocity.y = y;
}
void PhysicsObject::SetAccelerationX( int x )
{
	m_acceleration.x = x;
}
void PhysicsObject::SetAccelerationY( int y )
{
	m_acceleration.y = y;
}
void PhysicsObject::SetSpeed( int speed )
{
	m_speed = speed;
}