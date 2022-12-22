#pragma once

#include "GLFW/glfw3.h"



class GLFWInputHandler
{
public:

	GLFWInputHandler(GLFWwindow* targetWindow);
	GLFWInputHandler();

	GLFWInputHandler(const GLFWInputHandler& rhs) = delete;
	GLFWInputHandler(GLFWInputHandler&& rhs) = delete; 
	GLFWInputHandler operator=(const GLFWInputHandler& rhs) = delete;
	GLFWInputHandler operator=(GLFWInputHandler&& rhs) = delete;

	void PollEvents();


private:

	GLFWwindow* m_TargetWindow;

};