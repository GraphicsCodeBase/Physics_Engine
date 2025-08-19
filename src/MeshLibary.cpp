#include "headers/MeshLibary.hpp"
//defining static variables.
// This line allocates the storage for the static variable
std::map<std::string, std::shared_ptr<Mesh>> MeshLib::mesh_Libary;

void MeshLib::initalise()
{
	//create cube mesh
	auto cube = Mesh::createCube();
	//pass into the map.
	mesh_Libary["cube"] = std::move(cube);

	//create pyramid mesh
	auto pyramid = Mesh::createPyramid();
	//pass into map.
	mesh_Libary["pyramid"] = std::move(pyramid);
}

std::shared_ptr<Mesh> MeshLib::get(std::string name)
{
	//find the object using the map name 
	auto it = mesh_Libary.find(name);

	//if found return mesh.
	if (it != mesh_Libary.end())
	{
		return it->second;
	}
	else
	{
		//if not found return nullptr.
		std::cout << "Mesh not found." << std::endl; //error message.
		return nullptr;
	}
}
