#include "OpenGLRenderer.h"

#include <iostream>

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <algorithm>

OpenGLRenderer2D::OpenGLRenderer2D(GLFWwindow* targetWindow, int width, int height):
	m_TargetWindow(targetWindow),
	m_WindowWidth(width),
	m_WindowHeight(height),
	m_RectShader(std::make_unique<Shader>("./shader/objectRect.vs.glsl", "./shader/objectRect.fs.glsl")),
	m_MainCamera(),
	m_TextureFilepaths({ 
								{"RoadTile", "./Res/img/road.png"},
								{"PlayerCar", "./Res/img/redcar.png"},
								{"Grass_1", "./Res/img/grass.png"}
							})
{
}

OpenGLRenderer2D::~OpenGLRenderer2D()
{
	UnloadTextures();
}

void OpenGLRenderer2D::BeginFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer2D::SubmitRect(unsigned int objectID, float x, float y)
{
	// TODO: Implement the function
	assert(false);
}

int OpenGLRenderer2D::GetRenderTag(const std::string& tagName)
{

	auto cacheSearch = m_TextureCache.find(tagName);

	if(cacheSearch != m_TextureCache.end())
	{
		return cacheSearch->second->ID();
	}

	auto pathSearch = m_TextureFilepaths.find(tagName);

	if(pathSearch == m_TextureFilepaths.end())
	{
		std::cerr << "Warning: Unrecognized RenderTag request: " << tagName << std::endl;
		return 0;
	}

	else
	{
		OpenGLTexture* newTexture = new OpenGLTexture(pathSearch->second.string());
		m_TextureCache[tagName] = newTexture;
		return newTexture->ID();
	}
}

void OpenGLRenderer2D::SetMainCamera(const Camera& mainCamera)
{
	m_MainCamera = mainCamera;
}

void OpenGLRenderer2D::SubmitRect(unsigned int objectID, const glm::vec3& position, float angle)
{
	m_RenderQueue.emplace_back(objectID, position, angle);
}

void OpenGLRenderer2D::Paint()
{
	float overallTime = static_cast<float>(glfwGetTime());
	
	glClearColor(1.0f, 0.0f + glm::cos(overallTime), 0.0f + glm::sin(overallTime), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// TODO: Implement Radix sort
	// std::sort(m_RenderQueue.begin(), m_RenderQueue.end());

	// TODO: Implement proper state change system for renderer
	for(const Drawable& drawable : m_RenderQueue)
	{
		DrawObject(drawable);
	}

	m_RenderQueue.clear();

}

void OpenGLRenderer2D::DrawObject(const Drawable& drawable)
{
	glm::mat4 world = glm::translate(glm::mat4(1.0f), drawable.position);
	world = glm::rotate(world, glm::radians(drawable.rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 proj = m_MainCamera.getOrthoProj();
	glm::mat4 view(1.0f);

	m_RectShader->setMatrix4f("proj", proj);
	m_RectShader->setMatrix4f("world", world);
	m_RectShader->setMatrix4f("view", view);

	glBindTexture(GL_TEXTURE_2D, drawable.rendertag);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLRenderer2D::UnloadTextures()
{
	for(auto textureEntry : m_TextureCache)
	{
		delete(textureEntry.second);
	}
}
