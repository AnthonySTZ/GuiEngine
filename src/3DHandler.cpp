#include "3DHandler.h"
#include <string>

Vector3 Vector3::operator+(Vector3 vector3)
{
	return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);
}

std::ostream& operator<<(std::ostream&  os, const Vector3& vector3)
{
	std::string text = "x: " + std::to_string(vector3.x) + " y: " + std::to_string(vector3.y) + " z: " + std::to_string(vector3.z);
	return os << text;
}

void Scene::AddVertices(std::vector<Vertex> vertices_list)
{
	for each(Vertex vertex in vertices_list)
	{
		vertices.push_back(vertex);
	}	
}
