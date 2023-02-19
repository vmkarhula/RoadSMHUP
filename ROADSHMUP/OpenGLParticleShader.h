#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glad/glad.h"



class OpenGLParticleShader
{
	enum class ShaderType { VERTEX, FRAGMENT, COMPUTE, GEOMETRY, TESSELLATION, PROGRAM };
	enum class TransformFeedbackType { NONE, INTERLEAVED, SEPARATE };
	enum class LinkingState { NOT_LINKED, LINKED };

	OpenGLParticleShader(const std::string& programName);
	~OpenGLParticleShader();

	bool CompileShader(ShaderType type, const std::filesystem::path& filepath);
	bool AddTransformFeedback(const std::vector<std::string>& variableNames, TransformFeedbackType feedbacktype);

	bool LinkProgram();

	GLuint ProgramId() { return m_ProgramId; }
	GLuint ShaderId(ShaderType type);

	void Use();

	// Uniform Setters
	void SetInt(const std::string& paramName, int value);
	void SetUint(const std::string& paramName, unsigned int value);
	void SetFloat(const std::string& paramName, float value);
	void SetVector3f(const std::string& paramName, const glm::vec3& value);
	void SetMatrix3fv(const std::string& paramName, const glm::mat3& value);
	void SetMatrix4f(const std::string& paramName, const glm::mat4& value);

private:

	GLint FindUniformLocation(const std::string& uniformName);
	bool CheckShaderCompileErrors(unsigned int shader, ShaderType type);
	void DeleteShaders();

private:

	std::string m_ProgramName;
	GLuint m_ProgramId;
	LinkingState m_LinkingState;

	GLuint m_VertexShaderId;
	GLuint m_FragmentShaderId;
	GLuint m_GeometryShaderId;
	GLuint m_TessellationCSId;
	GLuint m_ComputeShaderId;

	std::unordered_map<std::string, GLuint> m_UniformCache;


};