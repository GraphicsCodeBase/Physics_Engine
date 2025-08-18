#pragma once
#include "headers/Shapes.hpp"
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate, glm::perspective, glm::lookAt, etc.

//basic constructor.
Shapes::Shapes(shapeType type, glm::vec3 pos, glm::vec3 scl, float rot, glm::vec4 col)
    : position(pos), scale(scl), rotation(rot), color(col)
{
    switch (type)
    {
    case shapeType::CUBE:
        main_mesh = Mesh::createCube();
        break;

    case shapeType::PYRAMID:
        main_mesh = Mesh::createPyramid();
        break;

    /*case shapeType::Plane:
        mesh = std::make_unique<Mesh>(Mesh::CreatePlane());
        break;*/

    default:
        throw std::invalid_argument("Unknown shape type");
    }
}

Shapes::~Shapes()
{
    //check if the mesh exists 
    if (main_mesh)
    {
        main_mesh->destroy();
    }
}

void Shapes::update(float dt)
{
    //for now im going to make this cube spin.
    float spinSpeed = 15.0f; // 15 degrees per second.
    rotation += spinSpeed * dt;

    // Keep rotation within 0–360° (optional)
    if (rotation >= 360.0f)
        rotation -= 360.0f;
}

void Shapes::render(const Shader& shader, glm::mat4 camMatrix)
{
    //create the m2w matrix.
    glm::mat4 model = glm::mat4(1.0f);//start with a identity matrix
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 1, 0));
    model = glm::scale(model, scale);
    //for testing purposes
    shader.use();
    //set uniforms.
    shader.setMat4("uniform_m2w",model);
    shader.setVec4("objectColor", color);
    shader.setMat4("uniform_vp", camMatrix);
    //call draw function.
    main_mesh->draw();
    shader.unUse();
}

void Shapes::set_color(vec4 color_in)
{
	color = color_in;
}
