#pragma once

#include "glm/glm.hpp"

class Camera
{
public:

	Camera(float x, float y, float zoom);
	~Camera();

	Camera(const Camera& rhs);
	Camera& operator=(const Camera& rhs) = delete;
	
	Camera(Camera&& rhs) = delete; 
	Camera&& operator=(Camera&& rhs) = delete;

	glm::mat4 getOrthoProj();
	
	void setZoom(float zoomValue);
	void adjustZoom(float zoomValue);
	
	void setPosition(glm::vec2 xy);
	//void setPosition(glm::vec3 xyz);
	
	void movePosition(glm::vec2 moveXY);
	void movePosition(glm::vec3 moveXYZ);

private:

	glm::vec2 m_Position;
	float m_ZoomLevel;

	int m_AspectX;
	int m_AspectY;

};