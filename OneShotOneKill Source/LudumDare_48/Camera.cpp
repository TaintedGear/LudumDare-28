#include "Camera.h"

Camera::Camera() : m_posX(0), m_posY(0), m_zoomLevel(1), m_minZoom(1), m_maxZoom(1),
	m_screenWidth(0), m_screenHeight(0)
{
}

Camera::~Camera()
{

}

void Camera::Initialise( int minZoom, int maxZoom, int screenWidth, int screenHeight)
{
	m_minZoom = minZoom;
	m_maxZoom = maxZoom;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void Camera::Update(float dt)
{
	if(m_zoomLevel < m_minZoom)
	{
		m_zoomLevel = m_minZoom;
	}
	else if(m_zoomLevel > m_maxZoom)
	{
		m_zoomLevel = m_maxZoom;
	}
}

int Camera::GetPosX()
{
	return m_posX;
}

int Camera::GetPosY()
{
	return m_posY;
}

int Camera::GetZoomLevel()
{
	return m_zoomLevel;
}