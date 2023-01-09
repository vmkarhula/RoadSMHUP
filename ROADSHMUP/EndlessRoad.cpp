#include "EndlessRoad.h"

#include "OpenGLRenderer.h"

#include <iostream>

EndlessRoadWorld::EndlessRoadWorld() :
	m_Seed(0),

	m_Roads{
		{0.0f, -6.0f, -0.3f},
		{0.0f, -5.0f, -0.3f},
		{0.0f, -4.0f, -0.3f},
		{0.0f, -3.0f, -0.3f},
		{0.0f, -2.0f, -0.3f},
		{0.0f, -1.0f, -0.3f},
		{0.0f, 0.0f, -0.3f},
		{0.0f, 1.0f, -0.3f},
		{0.0f, 2.0f, -0.3f},
		{0.0f, 3.0f, -0.3f},
		{0.0f, 4.0f, -0.3f},
		{0.0f, 5.0f, -0.3f},
		{0.0f, 6.0f, -0.3f} },

		m_MainCamera(0.0f, 0.0f, 3.0f, 3.0f),
		m_PlayerSpeed(1.0f),
		m_PlayerPosition(0.0f, 0.0f, 0.0f),
		m_PlayerAngle(0.0f),
		m_CurrentTick(0.0f),

		m_PreloadList(
			{
				"PlayerCar",
				"RoadTile",
				"Grass_1",
			}),

			m_EventQueue(nullptr)
{
	GenerateLandscapeGrid(10, 10);
}

EndlessRoadWorld::~EndlessRoadWorld()
{
}

void EndlessRoadWorld::Update(float dt)
{
	m_CurrentTick = dt;

	m_PlayerAngle = 0.0f;
	

	if (m_EventQueue)
	{
		
		// For now inputevents are nice, small enums, but we'll keep this expandable with const ref
		for (const InputEvent& e : *m_EventQueue)
		{
			HandleEvent(e);
		}
		
		m_EventQueue->clear();
	}
	

	for (glm::vec3& roadTile : m_Roads)
	{
		roadTile.y -= m_PlayerSpeed * dt;
		if (roadTile.y < -6.0f)
		{
			roadTile.y += 12.0f;
		}
	}

	for (glm::vec3& grassTile : m_Grass)
	{
		grassTile.y -= m_PlayerSpeed * dt;
		if (grassTile.y < -6.0f)
		{
			grassTile.y += 12.0f;
		}
	}

	for(std::vector<glm::vec3>& row : m_LandScape)
	{
		for(glm::vec3& square : row)
		{
			square.y -= m_PlayerSpeed * dt;
		
			if (square.y < -6.0f)
			{
				square.y += 12.0f;
			}
		}
	}

	m_MainCamera.update(m_CurrentTick);
}

void EndlessRoadWorld::AttachEventQueue(EventQueue& eq)
{
	m_EventQueue = &eq;
}

void EndlessRoadWorld::SendRenderables(OpenGLRenderer2D* renderer)
{
	renderer->SetMainCamera(m_MainCamera);
	
	for (const glm::vec3& roadTile : m_Roads)
	{
		renderer->SubmitRect(m_RenderTagCache["RoadTile"], roadTile, 0);
	}
	/*
	for (const glm::vec3& grassTile : m_Grass)
	{
		renderer->SubmitRect(m_RenderTagCache["Grass_1"], grassTile, 0);
	}
	*/

	for (const std::vector<glm::vec3>& tileRow: m_LandScape)
	{

		for (const glm::vec3& grassTile : tileRow)
		{
			renderer->SubmitRect(m_RenderTagCache["Grass_1"], grassTile, 0);
		}
	}

	renderer->SubmitRect(m_RenderTagCache["PlayerCar"], m_PlayerPosition, m_PlayerAngle);

}

void EndlessRoadWorld::PrepareRenderer(OpenGLRenderer2D* renderer)
{
	for (const std::string& toLoad : m_PreloadList)
	{
		int tag = renderer->GetRenderTag(toLoad);

		if (tag)
		{
			m_RenderTagCache[toLoad] = tag;
		}

		else
		{
			std::cerr << "Warning! Failed to receive rendertag for: " << toLoad << std::endl;
		}
	}
}

void EndlessRoadWorld::HandleEvent(const InputEvent& e)
{
	switch(e.code)
	{
	case InputEvent::InputCode::Up:
	{
		m_PlayerPosition.y += m_PlayerSpeed * m_CurrentTick;

	} break;

	case InputEvent::InputCode::Down:
	{
		m_PlayerPosition.y -= m_PlayerSpeed * m_CurrentTick;
	} break;

	case InputEvent::InputCode::Left:
	{
		m_PlayerAngle = 45.0f;
		m_PlayerPosition.x -= m_PlayerSpeed * m_CurrentTick;
	} break;

	case InputEvent::InputCode::Right:
	{
		m_PlayerAngle = -45.0f;
		m_PlayerPosition.x += m_PlayerSpeed * m_CurrentTick;
	} break;

	case InputEvent::InputCode::ZoomIn:
	{
		m_MainCamera.adjustZoomTarget(-1.0f);
	} break;

	case InputEvent::InputCode::ZoomOut:
	{
		m_MainCamera.adjustZoomTarget(1.0f);
	} break;

	default:
	{
		std::cerr << "Warning: Unhandled event code: " << static_cast<int>(e.code) << std::endl;
	}
	
	}

}

void EndlessRoadWorld::SendLandscapeRenderables(OpenGLRenderer2D* renderer)
{
	unsigned int roadTag = m_RenderTagCache.find("road")->second;

	for (const glm::vec3& roadTile : m_Roads)
	{
		renderer->SubmitRect(roadTag, roadTile, 0.0f);
	}
}

void EndlessRoadWorld::SendActorRenderables(OpenGLRenderer2D* renderer)
{
	unsigned int playerRenderTag = m_RenderTagCache.find("player")->second;

	renderer->SubmitRect(playerRenderTag, m_PlayerPosition, m_PlayerAngle);
}


/* Generates a grid of gridHeight * gridWidth with corresponding coordinates */
void EndlessRoadWorld::GenerateLandscapeGrid(int gridHeight, int gridWidth)
{
	m_LandScape = std::vector(gridHeight, std::vector<glm::vec3>(gridWidth, glm::vec3()));

	float xCoordStart = -6.0f;
	float yCoordStart = -6.0f;

	float zLevel = -0.3f;

	float xCoordEnd = 6.0f;
	float yCoordEnd = 6.0f;

	float xStep = (xCoordEnd - xCoordStart) / gridWidth;
	float yStep = (yCoordEnd - yCoordStart) / gridHeight;


	for(int row = 0; row < gridHeight; row++)
	{
		for(int column = 0; column < gridWidth; column++)
		{
			m_LandScape[row][column] = glm::vec3(xCoordStart + column * xStep, yCoordStart + row * yStep, zLevel);
		}
	}
}

