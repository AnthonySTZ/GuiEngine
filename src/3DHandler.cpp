#include "3DHandler.h"
#include <string>

Vector3 Vector3::operator+(Vector3 vector3)
{
	float new_x = x + vector3.x;
	float new_y = y + vector3.y;
	float new_z = z + vector3.z;
	return Vector3(new_x, new_y, new_z);
}

std::ostream& operator<<(std::ostream&  os, const Vector3& vector3)
{
	std::string text = "x: " + std::to_string(vector3.x) + " y: " + std::to_string(vector3.y) + " z: " + std::to_string(vector3.z);
	return os << text;
}
