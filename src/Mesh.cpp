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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex layout (position only for now)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

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

void Mesh::draw() const
{
    //bind vao
    glBindVertexArray(vao);
    // Draw the mesh using indices
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    // Unbind the VAO (optional, but good practice)
    glBindVertexArray(0);
}

std::unique_ptr<Mesh> Mesh::createCube()
{
    auto tempMesh = std::make_unique<Mesh>();

    // Create vertices
    tempMesh->vertices = {
        // Front face (+Z)
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},

        // Back face (-Z)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}}        
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


std::unique_ptr<Mesh> Mesh::createPyramid()
{
    auto m = std::make_unique<Mesh>();

    // Create vertices
   // Vertices with normals (per-face)
    m->vertices = {
        // Front face
        {{ 0.0f,  0.5f,  0.0f}, { 0.0f,  0.707f,  0.707f}}, // top
        {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.707f,  0.707f}}, // front-left
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.707f,  0.707f}}, // front-right

        // Right face
        {{ 0.0f,  0.5f,  0.0f}, { 0.707f,  0.707f,  0.0f}}, // top
        {{ 0.5f, -0.5f,  0.5f}, { 0.707f,  0.707f,  0.0f}}, // front-right
        {{ 0.5f, -0.5f, -0.5f}, { 0.707f,  0.707f,  0.0f}}, // back-right

        // Back face
        {{ 0.0f,  0.5f,  0.0f}, { 0.0f,  0.707f, -0.707f}}, // top
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.707f, -0.707f}}, // back-right
        {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.707f, -0.707f}}, // back-left

        // Left face
        {{ 0.0f,  0.5f,  0.0f}, {-0.707f,  0.707f,  0.0f}}, // top
        {{-0.5f, -0.5f, -0.5f}, {-0.707f,  0.707f,  0.0f}}, // back-left
        {{-0.5f, -0.5f,  0.5f}, {-0.707f,  0.707f,  0.0f}}, // front-left

        // Base face (optional: flat horizontal normal)
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}}, // front-left
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}}, // front-right
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}}, // back-right
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}}, // back-left
    };

    // Create indices
    m->indices = {
       0, 1, 2,      // front face
       3, 4, 5,      // right face
       6, 7, 8,      // back face
       9, 10, 11,    // left face
       12, 13, 14,   // base triangle 1
       12, 14, 15    // base triangle 2
    };

    m->uploadToGPU();
    return m;
}

