#include "GLFW_InputHandler.h"

#include <iostream>

GLFWInputHandler::GLFWInputHandler(GLFWwindow* targetWindow):
   m_TargetWindow(targetWindow)
{
}

GLFWInputHandler::GLFWInputHandler()
{
}

void GLFWInputHandler::PollEvents(EventQueue& eq)
{
   if (glfwGetKey(m_TargetWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
   {
      InputEvent e;
      e.code = InputEvent::InputCode::Left;
      
      eq.push_back(e);
   }

   if (glfwGetKey(m_TargetWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
   {
      InputEvent e;
      e.code = InputEvent::InputCode::Right;

      eq.push_back(e);
   }

   if (glfwGetKey(m_TargetWindow, GLFW_KEY_UP) == GLFW_PRESS)
   {
      InputEvent e;
      e.code = InputEvent::InputCode::Up;

      eq.push_back(e);
   }

   if (glfwGetKey(m_TargetWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
   {
      InputEvent e;
      e.code = InputEvent::InputCode::Down;

      eq.push_back(e);
   }

}
