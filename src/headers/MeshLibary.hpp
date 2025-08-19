#pragma once
#include "headers/Mesh.hpp"
#include "glm/glm.hpp"
#include <map>
#include <iostream>
class MeshLib
{
	public:
		void initalise();
		static std::shared_ptr<Mesh> get(std::string name);//search the map and return mesh.
	private:
		//this will hold all the instances of the objects.
		//for safety we will keep it private :)
		//i hope making this static doesnt affect the safety :(
		static std::map<std::string, std::shared_ptr<Mesh>> mesh_Libary;
};