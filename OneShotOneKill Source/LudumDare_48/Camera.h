#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	~Camera();

	virtual void Initialise( int minZoom, int maxZoom, int screenWidth, int screenHeight);
	virtual void Update(float dt);

	int GetPosX();
	int GetPosY();
	int GetZoomLevel();

protected:
	int m_posX,
		m_posY,
		m_zoomLevel,
		m_minZoom,
		m_maxZoom,
		m_screenWidth,
		m_screenHeight;

};

#endif