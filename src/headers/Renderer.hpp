#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <headers/Mesh.hpp>
#include <headers/Shapes.hpp>
#include <unordered_map>
/*
*	
	BASIC BRIEF
	=============
	The Renderer will be responsible for:
	Allocating instance buffers (SSBOs) for each mesh type.
	Updating instance data each frame (model matrices, maybe colors).
	Binding meshes and issuing instanced draw calls.
*/
class Renderer
{
	public:
	// Initialize instance buffer for a mesh type
	void initInstanceBuffer(const std::shared_ptr<Mesh>& mesh, size_t maxInstances);

	// Collect object data and update the GPU buffer
	void updateInstanceData(const std::shared_ptr<Mesh>& mesh, const std::vector<std::shared_ptr<Shapes>>& objects);

	// Draw all instances of a given mesh
	void drawInstanced(const std::shared_ptr<Mesh>& mesh, size_t instanceCount);
	private:
		struct InstanceBuffer
		{
			GLuint ssbo = 0;
			size_t maxInstances = 0;
		};
	//store per-mesh instance buffer data.
		std::unordered_map<Mesh*, InstanceBuffer> m_InstanceBuffers;
};