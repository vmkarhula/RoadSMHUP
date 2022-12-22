#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float x, float y, float zoom):
   m_Position(glm::vec2(x, y)),
   m_ZoomLevel(zoom),
   m_AspectX(16),
   m_AspectY(9)
{
}

Camera::~Camera()
{
}

Camera::Camera(const Camera& rhs): 
   m_Position(rhs.m_Position),
   m_ZoomLevel(rhs.m_ZoomLevel),
   m_AspectX(rhs.m_AspectX),
   m_AspectY(rhs.m_AspectY)
{
}


glm::mat4 Camera::getOrthoProj()
{
   return glm::ortho(
         m_Position.x - m_ZoomLevel,
         m_Position.x + m_ZoomLevel,
         m_Position.y - m_ZoomLevel,
         m_Position.y + m_ZoomLevel
         );
}

void Camera::setZoom(float zoomValue)
{
   m_ZoomLevel = zoomValue;
}

void Camera::adjustZoom(float zoomValue)
{
   m_ZoomLevel += zoomValue;
}

void Camera::setPosition(glm::vec2 xy)
{
   m_Position = xy; 
}

void Camera::movePosition(glm::vec2 moveXY)
{
   
}

void Camera::movePosition(glm::vec3 moveXYZ)
{
}
