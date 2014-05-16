#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

#include "Camera.h"
#include "Player.h"
#include "Input.h"

class PlayerCamera : public Camera
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Initialise( int minZoom, int maxZoom, int screenWidth, int screenHeight,
		Player& player);
	void Update( float dt, Player& player, Input& input, Level& level);

private:
};

#endif