#include <glm/glm.hpp>
#include <iostream>
#include <vector>
class Mesh
{
	public:
		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int ibo = 0;

		// Raw geometry data
		std::vector<glm::vec3> vertices;
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
