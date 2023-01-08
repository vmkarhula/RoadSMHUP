#pragma once

#include "GLFW/glfw3.h"

#include "RoadInput.h"

#include <vector>

class GLFWInputHandler
{
public:

	GLFWInputHandler(GLFWwindow* targetWindow);
	GLFWInputHandler();

	GLFWInputHandler(const GLFWInputHandler& rhs) = delete;
	GLFWInputHandler(GLFWInputHandler&& rhs) = delete; 
	GLFWInputHandler operator=(const GLFWInputHandler& rhs) = delete;
	GLFWInputHandler operator=(GLFWInputHandler&& rhs) = delete;

	void PollEvents(EventQueue& eq);


private:

	GLFWwindow* m_TargetWindow;

};