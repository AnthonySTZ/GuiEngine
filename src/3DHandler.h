#pragma once

#include <iostream>

class Vector3
{
public:
	float x, y, z;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3 operator+(Vector3 vector3);
	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector3);
};