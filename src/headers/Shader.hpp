#pragma once
#include <glad/glad.h>  // OpenGL
#include <GLFW/glfw3.h> // Window creation
#include <glm/glm.hpp>
#include <iostream>
class Shader
{
public:
	//basic constructor.
	Shader() : programID(0) {} //initalised the gluint to zero.

	void setUpShader(const std::string& vertexPath, const std::string& fragmentPath);
	//bind shader
	void use() const;
	void unUse() const;
	// Uniform setters
	void setMat4(const std::string& name, const glm::mat4& value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setFloat(const std::string& name, float value) const;
	GLuint getShaderID();
private:
	GLuint programID;

	//helper functions.
	std::string readFile(const std::string& filePath);
	//checking for shader compile errors.
	void checkCompileErrors(GLuint shader, std::string type);
};