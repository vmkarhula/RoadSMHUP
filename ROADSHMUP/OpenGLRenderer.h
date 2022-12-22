#pragma once

#include "GLFW/glfw3.h"
#include <memory>
#include <vector>



class OpenGLRenderer
{
public:

	OpenGLRenderer(GLFWwindow* targetWindow, int width, int height);
	
	OpenGLRenderer(const OpenGLRenderer& rhs) = delete;
	OpenGLRenderer operator=(const OpenGLRenderer& rhs) = delete;

	~OpenGLRenderer();

	void SubmitObject(unsigned int objectID, float x, float y);
	void SetCameraPos(float x, float y, float z);
	void Paint();

private:

	struct Drawable
	{
		unsigned int rendermask;
		unsigned int rendertag;
		float x, y;
	};

	void DrawObject(Drawable drawable);

private: 

	// The GLFWwindows have responsibilities outside the rendering, so they're owned by the main game and not by the renderer.  
	GLFWwindow* m_TargetWindow;
	
	int m_WindowWidth;
	int m_WindowHeight;
	
	std::vector<Drawable> m_RenderQueue;

};