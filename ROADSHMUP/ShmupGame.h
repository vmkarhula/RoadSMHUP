#pragma once

#include <memory>

#define GLFW_INCLUDE_NONE

// Glad needs to be loaded before glfw3
#include "glad/glad.h"
#include <GLFW/glfw3.h>



struct DestroyglfwWin 
{
	void operator()(GLFWwindow* ptr) 
	{
		glfwDestroyWindow(ptr);
	}
};

//using WindowUPtr = std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>;
using SmartGLFWWindow = std::unique_ptr<GLFWwindow, DestroyglfwWin>;


class SHMUPGame
{
public:
	
	SHMUPGame();
	SHMUPGame(const SHMUPGame& rhs) = delete;
	SHMUPGame operator=(const SHMUPGame& rhs) = delete;

	~SHMUPGame();

	bool Init();
	int Run();

	void I_MouseWheel(float xOffset, float yOffset);

private:

	void RenderInit();

private:
		
	GLFWwindow* m_MainWindow; 
	//SmartGLFWWindow m_MainWindow; 

	float m_MWheelOffsetX;
	float m_MWheelOffsetY;

};