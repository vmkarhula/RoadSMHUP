#include "ShmupGame.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "OpenGLTexture.h"
#include "RoadMathUtils.h"

#include "Camera.h"
#include "SHMUPWorld.h"

#include "DearImGUI/imgui.h"
#include "DearImGUI/backends/imgui_impl_glfw.h"
#include "DearImGUI/backends/imgui_impl_opengl3.h"
#include "DearImGUI/backends/imgui_impl_opengl3_loader.h"

#include <iostream>
#include <string>
#include <vector>

struct Renderable2D
{
   glm::vec3 pos;
   glm::vec3 rotation;

   unsigned int textureID;
};


SHMUPGame::SHMUPGame(): 
   m_MainWindow(nullptr),
   m_MWheelOffsetX(0.0f),
   m_MWheelOffsetY(0.0f)
{
}

SHMUPGame::~SHMUPGame()
{
   if(m_MainWindow)
      glfwDestroyWindow(m_MainWindow);
   
   glfwTerminate();
}

bool SHMUPGame::Init()
{
   std::cout << "SHMUP Initializing!" << std::endl;
  
   if (!glfwInit())
   {
      std::cerr << "GLFW Initialization failed!" << std::endl;
   }
  
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

   m_MainWindow = glfwCreateWindow(800U, 600U, "Wroom!", NULL, NULL);
      
   glfwMakeContextCurrent(m_MainWindow);
   
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize OpenGL context" << std::endl;
      return false;
   }
   
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   
   ImGui::StyleColorsDark();
   const char* glsl_version = "#version 460";
   //ImGui::StyleColorsLight();

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(m_MainWindow, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   glfwSetWindowUserPointer(m_MainWindow, (void*)this);

   // Hook up input callbacks

   auto ScrollWheelCallback = [](GLFWwindow* window, double xOffset, double yOffset)
   {
      ((SHMUPGame*)(glfwGetWindowUserPointer(window)))->I_MouseWheel(xOffset, yOffset);
   };

   glfwSetScrollCallback(m_MainWindow, ScrollWheelCallback);

   RenderInit();

   return true;
}

void SHMUPGame::RenderInit()
{
   
   
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);

   std::cout << "Depth check enabled" << std::endl;
}

int SHMUPGame::Run()
{
   std::cout << "SHMUP Running!" << std::endl;
   
   float rectVertices[] = 
   {
                            -0.5f, -0.5f, 1.0f,
                            0.5f, -0.5f, 1.0f,
                            -0.5f, 0.5f, 1.0f,

                            -0.5f, 0.5f, 1.0f,
                            0.5f, -0.5f, 1.0f,
                            0.5f, 0.5f, 1.0f
   
   };

   float rectUVVertices[] = 
   {
                            -0.5f, -0.5f, 1.0f,    0.0f, 0.0f,
                            0.5f, -0.5f, 1.0f,     1.0f, 0.0f,
                            -0.5f, 0.5f, 1.0f,     0.0f, 1.0f,

                            -0.5f, 0.5f, 1.0f,     0.0f, 1.0f,
                            0.5f, -0.5f, 1.0f,     1.0f, 0.0f,
                            0.5f, 0.5f, 1.0f,      1.0f, 1.0f
   };


   GLuint VBO;
   GLuint VAO;
   
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);

   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

   GLuint texVBO;
   GLuint texVAO;
   glGenBuffers(1, &texVBO);
   glGenVertexArrays(1, &texVAO);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   
   glBindBuffer(GL_ARRAY_BUFFER, texVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(rectUVVertices), rectUVVertices, GL_STATIC_DRAW);


   glBindVertexArray(texVAO);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);


   Shader firstShader = Shader("./shader/simplerect.vs.glsl", "./shader/simplerect.fs.glsl");
   Shader rectShader = Shader("./shader/objectRect.vs.glsl", "./shader/objectRect.fs.glsl");
   

   glm::vec3 pos = {};
   pos.x = 0.0;
   pos.y = 0.0;
   pos.z = -0.1f;

   glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
   
   OpenGLTexture carTex = OpenGLTexture("./Res/img/redcar.png");

   float prevTime = static_cast<float>(glfwGetTime());
   float xPos = 0.0f;
   float sideSpeed = 1.0f;
   float rotation = 0.0f;

   bool identityProj = false;

   std::vector<std::vector<int>> landGrid
   { {0, 1, 0},
      {0, 1, 0 },
      {0, 1, 0 },
      {0, 1, 0 },
      {0, 1, 0 } };

   glm::vec3 roadPos[] 
    {
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
      {0.0f, 6.0f, -0.3f}
     };

   

   Camera mainCam(0.0f, 0.0f, 1.0f);

   OpenGLTexture roadTex("./Res/img/road.png");

   float playerSpeed = 1.0f;

   while(!glfwWindowShouldClose(m_MainWindow))
   {
      
      /* 
         ===============
         INPUT AND SETUP
         ===============
      */
      
      //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      
      {
         ImGui::Begin("RoadSHMUP Control Panel");                        
       
         ImGui::SliderFloat("float", &xPos, -1.0f, 1.0f);         
         ImGui::SliderFloat("rotation", &rotation, 0.0f, 2 * glm::pi<float>());

         ImGui::SliderFloat("Speed", &playerSpeed, 0.0f, 5.0f);

         ImGui::Checkbox("Identity Projection Matrix", &identityProj);


         ImGui::Text("ImGUI Reported Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
         ImGui::End();
      }

      float overallTime = static_cast<float>(glfwGetTime());
      float tick = overallTime - prevTime;
      prevTime = overallTime;
      
      mainCam.update(tick);
         
      if (glfwGetKey(m_MainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         glfwSetWindowShouldClose(m_MainWindow, true);

      bool goingLeft = false;
      bool goingRight = false;
      bool goingUp = false;
      bool goingDown = false;

      if(glfwGetKey(m_MainWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
      {
         goingLeft = true;
         xPos -= tick * sideSpeed;
      }
      
      if (glfwGetKey(m_MainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
      {
         goingRight = true;
         xPos += tick * sideSpeed;
      }

      if (glfwGetKey(m_MainWindow, GLFW_KEY_UP) == GLFW_PRESS)
      {
         goingUp = true;
         pos.y += tick * sideSpeed;
      }

      if (glfwGetKey(m_MainWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
      {
         goingDown = true;
         pos.y -= tick * sideSpeed;
      }

      /* 
         =============
         Update system
         =============
      */

      xPos = RoadMath::clamp(xPos, -1.0f, 1.0f);

      pos = glm::vec3(xPos, pos.y, pos.z);
      
      
      
      // Render
      
      
      ImGui::Render();

      glClearColor(1.0f, 0.0f + glm::cos(overallTime), 0.0f + glm::sin(overallTime), 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glm::mat4 myMat = glm::mat4(1.0f);

      mainCam.adjustZoomTarget(-m_MWheelOffsetY);
      m_MWheelOffsetY = 0;

      glm::mat4 proj = mainCam.getOrthoProj();
      //glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

      if(identityProj)
      {
         proj = glm::mat4(1.0f);
      }

      rectShader.Use();
      
      if(goingLeft)
      {
         rotation = 0.25 * glm::pi<float>();
      }

      else if(goingRight)
      {
         rotation = -0.25 * glm::pi<float>();
      }

      else
      {
         rotation = 0.0f;
      }

      rotation = RoadMath::normalizeAngle(rotation, 0.0f, 2 * glm::pi<float>());

      for(glm::vec3& roadTile : roadPos)
      {
         roadTile.y -= playerSpeed * tick;
         if(roadTile.y < -6.0f)
         {
            roadTile.y += 12.0f;
         } 
      }

      /* 
         ======
         RENDER
         ======
      */


      glm::mat4 world = glm::translate(glm::mat4(1.0f), pos);
      world = glm::rotate(world, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
      
      glm::mat4 view(1.0f);

      rectShader.setMatrix4f("proj", proj);
      rectShader.setMatrix4f("world", world);
      rectShader.setMatrix4f("view", view);
      //rectShader.setUniformSampler2D()

      glBindTexture(GL_TEXTURE_2D, carTex.ID());
 

      //firstShader.Use();
      //firstShader.setVector3f("ourColor", pos);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      for(const glm::vec3& road : roadPos)
      {
         glm::mat4 roadWorld = glm::translate(glm::mat4(1.0f), road);
         
         glBindTexture(GL_TEXTURE_2D, roadTex.ID());

         rectShader.setMatrix4f("proj", proj);
         rectShader.setMatrix4f("world", roadWorld);
         rectShader.setMatrix4f("view", view);
      
         glDrawArrays(GL_TRIANGLES, 0, 6);

      }

      
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(m_MainWindow);

      glfwPollEvents();
   }

   return 0;
}

void SHMUPGame::I_MouseWheel(float xOffset, float yOffset)
{
   m_MWheelOffsetX += xOffset;
   m_MWheelOffsetY += yOffset; 
}
