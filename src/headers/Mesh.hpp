#include <glm/glm.hpp>
#include <iostream>
#include <vector>

//defining a struct for the mesh
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class Mesh
{
	public:
		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ibo = 0;

		// Raw geometry data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		
		Mesh() = default;
		~Mesh();

		// Upload to GPU
		void uploadToGPU();

		// Delete from GPU
		void destroy();

		//draw mesh
		void draw() const;

		// Shape generators
		static std::unique_ptr<Mesh> createCube();
		static std::unique_ptr<Mesh> createPyramid();
	private:
};
