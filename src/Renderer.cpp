#include "headers/Renderer.hpp"

void Renderer::initInstanceBuffer(const std::shared_ptr<Mesh>& mesh, size_t maxInstances)
{
	//create buffer.
	InstanceBuffer Buffer;
	//assign max instances
	Buffer.maxInstances = maxInstances;

	//generate SSBO 
	glGenBuffers(1, &Buffer.ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer.ssbo);
	// Allocate memory for maxInstances model matrices
	glBufferData(GL_SHADER_STORAGE_BUFFER, maxInstances * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	m_InstanceBuffers[mesh.get()] = Buffer;//assign back into the container.
}

void Renderer::updateInstanceData(const std::shared_ptr<Mesh>& mesh, const std::vector<std::shared_ptr<Shapes>>& objects)
{
	//we update instance data each frame.
	auto it = m_InstanceBuffers.find(mesh.get());
	if (it == m_InstanceBuffers.end()) return;

	InstanceBuffer& buffer = it->second;
	std::vector<glm::mat4> matrices;
	matrices.reserve(objects.size());

	for (auto& obj : objects)
	{
		if (obj->getMesh().get() == mesh.get()) // only take objects using this mesh
		{
			matrices.push_back(obj->getModelMatrix());
		}
	}
	//finally pass into the shader.
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer.ssbo);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Renderer::drawInstanced(const std::shared_ptr<Mesh>& mesh, size_t instanceCount)
{
	// Lookup instance buffer
	auto it = m_InstanceBuffers.find(mesh.get());
	if (it == m_InstanceBuffers.end())
	{
		return;
	}

	InstanceBuffer& buffer = it->second;

	// Bind mesh VAO
	glBindVertexArray(mesh->vao);

	// Bind SSBO to binding point 0 (make sure shader matches this binding)
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer.ssbo);

	// Draw instanced
	glDrawElementsInstanced(
		GL_TRIANGLES,
		static_cast<GLsizei>(mesh->indices.size()),
		GL_UNSIGNED_INT,
		0,
		static_cast<GLsizei>(instanceCount)
	);

	// Unbind VAO
	glBindVertexArray(0);
}
