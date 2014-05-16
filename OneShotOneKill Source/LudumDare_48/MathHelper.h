#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <math.h>

namespace MathHelper
{
	const float PI = 3.14f;

	struct Vector2D
	{
		Vector2D()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float x, y;

		void Normalize()
		{
			float mag = sqrt((float)x*(float)x + (float)y*(float)y);
			x /= mag;
			y /= mag;
		}
	};

	inline float DegreesToRadians( float degrees )
	{
		return (degrees*PI)/ 180.0f;
	}
	inline float RadiansToDegrees( float radians )
	{
		return (radians*180.0f) / PI;
	}
	inline float Lerp(float x, float x1, float target)
	{
		return x * (1 - target) + x1 * target;
	}
	inline float DistanceFromTarget(Vector2D start, Vector2D target)
	{
		float distX = target.x - start.x;
		float distY = target.y - start.y;

		return (float)sqrt((double)distX*distX + distY*distY);
	}
};

#endif