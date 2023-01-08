#pragma once

#include "SHMUPWorld.h"

#include <vector>
#include <unordered_map>
#include <string>

#include "Camera.h"
#include "RoadInput.h"

#include "glm/glm.hpp"


class EndlessRoadWorld: public SHMUPWorld
{

public:
	
	EndlessRoadWorld();
	~EndlessRoadWorld();

	EndlessRoadWorld(const EndlessRoadWorld& rhs) = delete;
	EndlessRoadWorld(EndlessRoadWorld&& rhs) = delete;

	// Update one timestep
	void Update(float dt) override;
	
	void AttachEventQueue(EventQueue& eq);

	// Send render requests to the renderer 
	void SendRenderables(OpenGLRenderer2D* renderer) override;
	
	// Preload the required assets (shaders, textures, material data ...)
	void PrepareRenderer(OpenGLRenderer2D* renderer) override;

private:

	void HandleEvent(const InputEvent& e);

	void SendLandscapeRenderables(OpenGLRenderer2D* renderer);
	void SendActorRenderables(OpenGLRenderer2D* renderer);

	void GenerateLandscapeGrid(int gridHeight, int gridWidth);

private:
	
	int m_Seed;
		
	float m_CurrentTick;
	
	float m_PlayerSpeed;

	glm::vec3 m_PlayerPosition;
	
	// Player angle in degrees
	float m_PlayerAngle;
	
	std::vector<glm::vec3> m_Grass;
	std::vector<glm::vec3> m_Roads;
	
	std::vector<std::vector<glm::vec3>> m_LandScape;


	Camera m_MainCamera;

	std::vector<std::string> m_PreloadList; 
	std::unordered_map<std::string, unsigned int> m_RenderTagCache;	

	EventQueue* m_EventQueue;
};