#include <glm/glm.hpp>
#include <headers/Shapes.hpp>
#include <iostream>
class PhysicsSystem
{
	public:

		void initaliseObjects();

		void update(float dt);

		//getters
		std::vector<std::shared_ptr<Shapes>> getObjects();
	private:
		//container to hold all the objects.
		std::vector<std::shared_ptr<Shapes>> objects;
};