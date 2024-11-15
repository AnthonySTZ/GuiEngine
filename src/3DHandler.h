#pragma once

#include <iostream>
#include <vector>

struct Vector3
{
	float x, y, z;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3 operator+(Vector3 vector3);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector3);
};

struct Vertex
{
	Vector3 position;
	Vertex(Vector3 position) : position(position) {};
};


class Scene
{
public:
	std::vector<Vertex> vertices;
	void AddVertices(std::vector<Vertex> vertices_list);
};

