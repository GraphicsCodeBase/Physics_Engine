#include <headers/physics.hpp>
#include <glm/gtc/matrix_transform.hpp> // For glm::rotate, glm::perspective, glm::lookAt, etc.

void PhysicsSystem::initaliseObjects()
{
	objects.clear();
	//make 16 cubes and put into the container.
	// all the same color first.
	int gridSize = 4;        // 4x4 grid
	float spacing = 1.5f;    // distance between cubes

	for (int x = 0; x < gridSize; x++)
	{
		for (int z = 0; z < gridSize; z++)
		{
			glm::vec3 pos = glm::vec3(x * spacing, 0.0f, z * spacing);
			glm::vec3 scale = glm::vec3(1.0f);
			float rot = 0.0f;
			glm::vec4 color = glm::vec4(1.0f, 0.5f, 0.2f, 1.0f);

			auto cube = std::make_shared<Shapes>(Shapes::shapeType::CUBE, pos, scale, rot, color);
			objects.push_back(cube);
		}
	}
}

void PhysicsSystem::update(float dt)
{
	//for now we just spin the objects 
	float rotationSpeed = glm::radians(45.0f); // 45 degrees/sec

	//loop through every object in the container
	for (auto obj : objects)
	{
		// for now we assume Shapes has a getter for rotation
		float currentRot = obj->getRot();

		// increment rotation based on delta time
		float newRot = currentRot + rotationSpeed * dt;

		// update object
		obj->setRot(newRot);

		obj->update(dt);//set the model matrix.
	}
}

std::vector<std::shared_ptr<Shapes>> PhysicsSystem::getObjects()
{
	return objects;
}
