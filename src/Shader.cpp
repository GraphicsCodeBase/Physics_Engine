#include "header/Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
//========================================
// 
//          CORE FUNCTIONS 
// 
//========================================
void Shader::setUpShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    //read source from files.
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);
    //convert into to char*
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //compile vertex shader.
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");// compile and check for shader errors

    //compile fragment shader.
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Link shaders to program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");

    // Clean up shaders (they're already linked into the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
//function to bind shader.
void Shader::use() const
{
    glUseProgram(programID);
}
void Shader::unUse() const
{
    glUseProgram(0);  // <-- unbind here
}
//========================================
//      UNIFORM SETTING FUNCTIONS 
/*
        BASIC SHADER USE CASE.

        shader.use(); // Always before setting uniforms

        shader.setMat4("u_Model", modelMatrix);
        shader.setVec3("u_LightPos", glm::vec3(0.0f, 10.0f, 5.0f));
        shader.setFloat("u_Time", glfwGetTime());
*/
//========================================
void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }
    else
    {
        std::cerr << "Warning: uniform '" << name << "' not found in shader program." << std::endl;
    }
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1)
    {
        glUniform3fv(location, 1, glm::value_ptr(value));
    }
    else
    {
        std::cerr << "Warning: uniform '" << name << "' not found in shader program." << std::endl;
    }
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1)
    {
        glUniform4fv(location, 1, glm::value_ptr(value));
    }
    else
    {
        std::cerr << "Warning: uniform '" << name << "' not found in shader program." << std::endl;
    }
}

void Shader::setFloat(const std::string& name, float value) const
{
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1)
    {
        glUniform1f(location, value);
    }
    else
    {
        std::cerr << "Warning: uniform '" << name << "' not found in shader program." << std::endl;
    }
}
//get shaderID.
GLuint Shader::getShaderID()
{
    return programID;
}

//========================================
// 
//          HELPER FUNCTIONS 
// 
//========================================
//helper function to read from file.
std::string Shader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("Failed to open shader file: " + filePath);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
//helper functions to check for compile errors.
void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << type << " SHADER COMPILATION ERROR\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "PROGRAM LINKING ERROR\n" << infoLog << std::endl;
        }
    }
}
