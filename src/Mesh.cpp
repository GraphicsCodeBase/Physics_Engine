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

    // Positions of the 8 cube corners
    glm::vec3 positions[8] = {
        {-0.5f, -0.5f,  0.5f}, // 0
        { 0.5f, -0.5f,  0.5f}, // 1
        { 0.5f,  0.5f,  0.5f}, // 2
        {-0.5f,  0.5f,  0.5f}, // 3
        {-0.5f, -0.5f, -0.5f}, // 4
        { 0.5f, -0.5f, -0.5f}, // 5
        { 0.5f,  0.5f, -0.5f}, // 6
        {-0.5f,  0.5f, -0.5f}  // 7
    };

    // Compute smooth normals for each corner by averaging connected face normals
    glm::vec3 normals[8] = {};
    normals[0] = normalize(glm::vec3(-1, -1, 1) + glm::vec3(-1, 0, 0) + glm::vec3(0, -1, 0));
    normals[1] = normalize(glm::vec3(1, -1, 1) + glm::vec3(1, 0, 0) + glm::vec3(0, -1, 0));
    normals[2] = normalize(glm::vec3(1, 1, 1) + glm::vec3(1, 0, 0) + glm::vec3(0, 1, 0));
    normals[3] = normalize(glm::vec3(-1, 1, 1) + glm::vec3(-1, 0, 0) + glm::vec3(0, 1, 0));
    normals[4] = normalize(glm::vec3(-1, -1, -1) + glm::vec3(-1, 0, 0) + glm::vec3(0, -1, 0));
    normals[5] = normalize(glm::vec3(1, -1, -1) + glm::vec3(1, 0, 0) + glm::vec3(0, -1, 0));
    normals[6] = normalize(glm::vec3(1, 1, -1) + glm::vec3(1, 0, 0) + glm::vec3(0, 1, 0));
    normals[7] = normalize(glm::vec3(-1, 1, -1) + glm::vec3(-1, 0, 0) + glm::vec3(0, 1, 0));

    // Create vertices
    for (int i = 0; i < 8; ++i)
        tempMesh->vertices.push_back({ positions[i], normals[i] });

    // Indices for the 12 triangles of the cube
    tempMesh->indices = {
        0,1,2, 2,3,0, // Front
        1,5,6, 6,2,1, // Right
        5,4,7, 7,6,5, // Back
        4,0,3, 3,7,4, // Left
        3,2,6, 6,7,3, // Top
        4,5,1, 1,0,4  // Bottom
    };

    tempMesh->uploadToGPU();

    return tempMesh;
}



std::unique_ptr<Mesh> Mesh::createPyramid()
{
    auto m = std::make_unique<Mesh>();

    // Positions of the 5 pyramid corners
    glm::vec3 positions[5] = {
        { 0.0f,  0.5f,  0.0f}, // top (0)
        {-0.5f, -0.5f,  0.5f}, // front-left (1)
        { 0.5f, -0.5f,  0.5f}, // front-right (2)
        { 0.5f, -0.5f, -0.5f}, // back-right (3)
        {-0.5f, -0.5f, -0.5f}  // back-left (4)
    };

    // Compute smooth normals for each vertex
    glm::vec3 normals[5];

    // Top vertex normal: average of all four side faces
    normals[0] = normalize(
        glm::vec3(0.0f, 0.707f, 0.707f) + // front
        glm::vec3(0.707f, 0.707f, 0.0f) + // right
        glm::vec3(0.0f, 0.707f, -0.707f) + // back
        glm::vec3(-0.707f, 0.707f, 0.0f)    // left
    );

    // Base vertices: average of side faces touching each vertex + bottom face
    normals[1] = normalize(glm::vec3(0.0f, 0.707f, 0.707f) + glm::vec3(-0.707f, 0.707f, 0.0f) + glm::vec3(0.0f, -1.0f, 0.0f));
    normals[2] = normalize(glm::vec3(0.0f, 0.707f, 0.707f) + glm::vec3(0.707f, 0.707f, 0.0f) + glm::vec3(0.0f, -1.0f, 0.0f));
    normals[3] = normalize(glm::vec3(0.0f, 0.707f, -0.707f) + glm::vec3(0.707f, 0.707f, 0.0f) + glm::vec3(0.0f, -1.0f, 0.0f));
    normals[4] = normalize(glm::vec3(0.0f, 0.707f, -0.707f) + glm::vec3(-0.707f, 0.707f, 0.0f) + glm::vec3(0.0f, -1.0f, 0.0f));

    // Create vertices
    for (int i = 0; i < 5; ++i)
        m->vertices.push_back({ positions[i], normals[i] });

    // Indices for the 4 side triangles + 2 base triangles
    m->indices = {
        0,1,2, // front
        0,2,3, // right
        0,3,4, // back
        0,4,1, // left
        1,2,3, // base triangle 1
        1,3,4  // base triangle 2
    };

    m->uploadToGPU();
    return m;
}



