#pragma once

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <memory>
#include <vector>
#include <filesystem>

#include "Shader.h"
#include "Camera.h"
#include "OpenGLTexture.h"

using std::filesystem::path;


class OpenGLRenderer2D
{
public:

	OpenGLRenderer2D(GLFWwindow* targetWindow, int width, int height);

	OpenGLRenderer2D(const OpenGLRenderer2D& rhs) = delete;
	OpenGLRenderer2D operator=(const OpenGLRenderer2D& rhs) = delete;

	~OpenGLRenderer2D();

	void BeginFrame();

	void SubmitRect(unsigned int objectID, float x, float y);
	//void SubmitRect(unsigned int objectID, float x, float y, float z);
	void SubmitRect(unsigned int renderTag, const glm::vec3& position, float rotationDegrees);
	//void SubmitRect(unsigned int objectID, const glm::mat4& transform);

	//void SubmitRectBatch(const std::vector<glm::vec3>& positions, const glm::vec4& color);
	//void SubmitRectBatch(const std::vector<glm::vec3>& positions, const std::vector<glm::vec4>& colors);

	int GetRenderTag(const std::string& tagName);

	void SetMainCamera(const Camera& mainCamera);
	void Paint();

private:

	struct Drawable
	{
		Drawable(unsigned int _renderTag, const glm::vec3& _position, float _rotation) :
			rendertag(_renderTag),
			position(_position),
			rotation(_rotation)
		{};

		unsigned int rendertag;
		glm::vec3 position;
		float rotation;
	};

	void DrawObject(const Drawable& drawable);

	void UnloadTextures();

private:

	// The GLFWwindows have responsibilities outside the rendering, so they're owned by the main game and not by the renderer.  
	GLFWwindow* m_TargetWindow;

	int m_WindowWidth;
	int m_WindowHeight;

	Camera m_MainCamera;

	std::unique_ptr<Shader> m_RectShader;

	std::vector<Drawable> m_RenderQueue;
	std::unordered_map<std::string, path> m_TextureFilepaths;
	std::unordered_map<std::string, OpenGLTexture*> m_TextureCache;
};