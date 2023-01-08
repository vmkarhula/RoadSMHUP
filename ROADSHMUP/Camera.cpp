#include "Camera.h"

#include <iostream>

#include "RoadMathUtils.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera():
   m_Position(glm::vec2(0.0f, 0.0f)),
   m_ZoomLevel(1.0f),
   m_AspectX(16),
   m_AspectY(9),
   m_MinZoom(1.0f),
   m_MaxZoom(5.0f),
   m_ArriveThreshold(0.1f),
   m_MaxZoomVeloctity(2.0f)
{
}

Camera::Camera(float x, float y, float zoom):
   m_Position(glm::vec2(x, y)),
   m_ZoomLevel(zoom),
   m_AspectX(16),
   m_AspectY(9),
   m_MinZoom(1.0f),
   m_MaxZoom(5.0f),
   m_ArriveThreshold(0.1f),
   m_MaxZoomVeloctity(2.0f)
{
}

Camera::Camera(float x, float y, float zoom, float zoomTarget):
m_Position(glm::vec2(x, y)),
m_ZoomLevel(zoom),
m_AspectX(16),
m_AspectY(9),
m_MinZoom(1.0f),
m_MaxZoom(5.0f),
m_ArriveThreshold(0.1f),
m_MaxZoomVeloctity(2.0f), 
m_ZoomTarget(zoomTarget)
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

void Camera::update(float dt)
{
   float targetDist = m_ZoomTarget - m_ZoomLevel;

   m_ZoomLevel += RoadMath::clamp(targetDist, -m_MaxZoomVeloctity * dt, m_MaxZoomVeloctity * dt);

}

void Camera::setZoom(float zoomValue)
{
   m_ZoomLevel = zoomValue;
}

void Camera::adjustZoom(float zoomValue)
{
   m_ZoomLevel += zoomValue;
   m_ZoomLevel = RoadMath::clamp(m_ZoomLevel, m_MinZoom, m_MaxZoom);
}

void Camera::adjustZoomTarget(float zoomTargetValue)
{
   m_ZoomTarget += zoomTargetValue;
   m_ZoomTarget = RoadMath::clamp(m_ZoomTarget, m_MinZoom, m_MaxZoom);
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
