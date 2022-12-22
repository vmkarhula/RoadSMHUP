#pragma once

#include <memory>


// Glad needs to be loaded before glfw3
#include "glad/glad.h"
#include "GLFW/glfw3.h"


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

private:


private:
		
	GLFWwindow* m_MainWindow; 
	//SmartGLFWWindow m_MainWindow; 

};