#include <headers/Mesh.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::~Mesh()
{
    //call the destroy function.
    destroy();
}

void Mesh::uploadToGPU()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex layout (position only for now)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0);
}
//function to clear all member variables.
void Mesh::destroy()
{
    if (vbo) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    if (ibo) {
        glDeleteBuffers(1, &ibo);
        ibo = 0;
    }
    if (vao) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

std::unique_ptr<Mesh> Mesh::createCube()
{
    auto tempMesh = std::make_unique<Mesh>();

    // Create vertices
    tempMesh->vertices = {
        // Front
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f},
        // Back
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f}
    };

    // Create indices
    tempMesh->indices = {
        // Front
        0, 1, 2, 2, 3, 0,
        // Right
        1, 5, 6, 6, 2, 1,
        // Back
        5, 4, 7, 7, 6, 5,
        // Left
        4, 0, 3, 3, 7, 4,
        // Top
        3, 2, 6, 6, 7, 3,
        // Bottom
        4, 5, 1, 1, 0, 4
    };

    tempMesh->uploadToGPU();

    return tempMesh; // returns unique_ptr<Mesh>
}


std::shared_ptr<Mesh> Mesh::createPyramid()
{
    auto m = std::make_shared<Mesh>();

    // Create vertices
    m->vertices = {
        { 0.0f,  0.5f,  0.0f},  // top
        {-0.5f, -0.5f,  0.5f},  // front-left
        { 0.5f, -0.5f,  0.5f},  // front-right
        { 0.5f, -0.5f, -0.5f},  // back-right
        {-0.5f, -0.5f, -0.5f}   // back-left
    };

    // Create indices
    m->indices = {
        0, 1, 2,  // front face
        0, 2, 3,  // right face
        0, 3, 4,  // back face
        0, 4, 1,  // left face
        1, 4, 3,  // base
        1, 3, 2
    };

    m->uploadToGPU();
    return m;
}

