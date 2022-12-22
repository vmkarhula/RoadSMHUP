#pragma once

#include "glm/glm.hpp"

class AABB;

class RigidBody
{
public:
	
	RigidBody();
	~RigidBody();

	void Update(float dt);

	void Move();
	void Push();
	bool Collide();

private:

	glm::vec3 m_Position;	
	glm::vec3 m_Velocity;

	float m_Mass;
};