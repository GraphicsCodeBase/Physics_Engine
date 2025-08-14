#include "headers/Shapes.hpp"
//basic constructor.
Shapes::Shapes(shapeType type, glm::vec3 pos, glm::vec3 scl, float rot, glm::vec4 col)
    : position(pos), scale(scl), rotation(rot), color(col)
{
    switch (type)
    {
    case shapeType::CUBE:
        main_mesh = std::make_unique<Mesh>(Mesh::createCube());
        break;

    case shapeType::PYRAMID:
        main_mesh = std::make_unique<Mesh>(Mesh::createPyramid());
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
}

void Shapes::set_color(vec4 color_in)
{
	color = color_in;
}
