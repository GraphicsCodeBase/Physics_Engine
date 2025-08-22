#pragma once
#include <glm/glm.hpp>
#include "headers/Mesh.hpp"
#include "headers/Shader.hpp"
#include "headers/MeshLibary.hpp"
using namespace glm;

class Shapes
{
public:
	enum shapeType
	{
		CUBE,
		BALL,
		PYRAMID
	};
	//constructor
	Shapes(shapeType type, glm::vec3 pos = { 0.0f,0.0f,0.0f }, glm::vec3 scl = { 1.0f,1.0f,1.0f }
		  , float rot = 0.0f, glm::vec4 col = { 1,1,1,1 });
	~Shapes();//destructor
	void update(float dt); //dt = delta time.
	void render(const Shader& shader, glm::mat4 camMatrix);
	//void initialize_shape();
	void set_color(vec4 color);
	//setters
	void setRot(float rotation_in);
	void setPos(glm::vec3 position_in);
	//Getters
	std::shared_ptr<Mesh> getMesh();
	glm::mat4 getModelMatrix();
	float getRot();
private:
	//basic attributes to send to the GPU.
	glm::vec3 position;
	glm::vec3 scale;
	float rotation;
	glm::vec4 color;
	glm::mat4 modelMatrix;
	shapeType objectType;
	std::shared_ptr<Mesh> main_mesh;
};