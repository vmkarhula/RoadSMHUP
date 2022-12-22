#include "OpenGLRenderer.h"
#include "glm/glm.hpp"

#include <algorithm>

OpenGLRenderer::OpenGLRenderer(GLFWwindow* targetWindow, int width, int height):
	m_TargetWindow(targetWindow),
	m_WindowWidth(width),
	m_WindowHeight(height)
{
	
}

void OpenGLRenderer::SubmitObject(unsigned int objectID, float x, float y)
{
}

void OpenGLRenderer::SetCameraPos(float x, float y, float z)
{
}

void OpenGLRenderer::Paint()
{
	float overallTime = static_cast<float>(glfwGetTime());
	
	glClearColor(1.0f, 0.0f + glm::cos(overallTime), 0.0f + glm::sin(overallTime), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// TODO: Implement Radix sort
	// std::sort(m_RenderQueue.begin(), m_RenderQueue.end());

	// TODO: Implement proper state change system for renderer
	for(Drawable drawable : m_RenderQueue)
	{
		DrawObject(drawable);
	}

	glfwSwapBuffers(m_TargetWindow);
}

void OpenGLRenderer::DrawObject(Drawable drawable)
{
}
