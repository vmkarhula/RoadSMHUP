#pragma once

#include "glm/glm.hpp"

class Camera
{
public:

	Camera();
	Camera(float x, float y, float zoom);
	Camera(float x, float y, float zoom, float zoomTarget);
	~Camera();

	Camera(const Camera& rhs);
	Camera& operator=(const Camera& rhs) = default;
	
	Camera(Camera&& rhs) = delete; 
	Camera&& operator=(Camera&& rhs) = delete;

	glm::mat4 getOrthoProj();
	
	void update(float dt);

	void setZoom(float zoomValue);
	
	void adjustZoomTarget(float zoomTargetValue);
	void adjustZoom(float zoomValue);
	
	void setPosition(glm::vec2 xy);
	//void setPosition(glm::vec3 xyz);
	
	void movePosition(glm::vec2 moveXY);
	void movePosition(glm::vec3 moveXYZ);

private:
	
	glm::vec2 m_Position;
	
	float m_ZoomLevel;
	float m_ZoomTarget;

	float m_MinZoom;
	float m_MaxZoom;

	int m_AspectX;
	int m_AspectY;

	float m_ArriveThreshold;
	
	float m_MaxZoomVeloctity;

};