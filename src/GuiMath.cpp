#include "GuiMath.h"
#include <string>

namespace gui_math {

	Vector3 Vector3::operator+(Vector3 vector)
	{
		return Vector3(x + vector.x, y + vector.y, z + vector.z);
	}

	void Vector3::operator+=(Vector3 vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
	}

	void Vector3::operator-=(Vector3 vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
	}

	Vector3 Vector3::operator-(Vector3 vector)
	{
		return Vector3(x - vector.x, y - vector.y, z - vector.z);
	}

	Vector3 Vector3::operator-()
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 Vector3::operator*(float mult)
	{
		return Vector3(x * mult, y * mult, z * mult);
	}

	Vector3 Vector3::operator/(float divider)
	{
		return Vector3(x / divider, y / divider, z / divider);
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		std::string text = "x: " + std::to_string(vector.x) + " y: " + std::to_string(vector.y) + " z: " + std::to_string(vector.z);
		return os << text;
	}

	Vector3 cross(Vector3 vec_01, Vector3 vec_02)
	{
		return Vector3(vec_01.y * vec_02.z - vec_01.z * vec_02.y,
			vec_01.z * vec_02.x - vec_01.x * vec_02.z,
			vec_01.x * vec_02.y - vec_01.y * vec_02.x);
	}

	float length(Vector3 vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	Vector3 normalize(Vector3 vec)
	{
		float vec_length = length(vec);
		if (vec_length == 0) return Vector3(0.0f, 0.0f, 0.0f);
		return vec / vec_length;
	}

	float dot(Vector3 vec_01, Vector3 vec_02)
	{
		return vec_01.x * vec_02.x + vec_01.y * vec_02.y + vec_01.z * vec_02.z;
	}

	float radians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	Matrix4 Matrix4::lookAt(Vector3 eye, Vector3 target, Vector3 up)
	{
		Matrix4 result;

		Vector3 d = gui_math::normalize(eye - target);       // Camera direction
		Vector3 r = gui_math::normalize(gui_math::cross(up, d)); // Right vector
		Vector3 u = gui_math::cross(d, r);                   // Recomputed up vector

		// Fill rotation part
		result.elements[0] = r.x; result.elements[4] = r.y; result.elements[8] = r.z;
		result.elements[1] = u.x; result.elements[5] = u.y; result.elements[9] = u.z;
		result.elements[2] = -d.x; result.elements[6] = -d.y; result.elements[10] = -d.z;

		// Fill translation part
		result.elements[12] = -gui_math::dot(r, eye);
		result.elements[13] = -gui_math::dot(u, eye);
		result.elements[14] = gui_math::dot(d, eye);

		// Last row
		result.elements[15] = 1.0f;

		return result;
	}

	Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far)
	{
		Matrix4 result;

		float tanHalfFov = tan(fov / 2.0f);

		result.elements[0] = 1.0f / (aspect * tanHalfFov); // [0][0]
		result.elements[5] = 1.0f / tanHalfFov;           // [1][1]
		result.elements[10] = -(far + near) / (far - near);  // [2][2]
		result.elements[11] = -1.0f;                      // [2][3]
		result.elements[14] = -(2.0f * far * near) / (far - near); // [3][2]

		return result;
	}

	Matrix4 Matrix4::view(Vector3 position, Vector3 direction, Vector3 up)
	{
		Matrix4 result;

		// Calculate camera axes
		Vector3 zAxis = -gui_math::normalize(direction);                // Forward direction (negative z-axis in view space)
		Vector3 xAxis = -gui_math::normalize(gui_math::cross(up, zAxis)); // Right vector
		Vector3 yAxis = gui_math::cross(zAxis, xAxis);                  // Up vector

		// Fill the rotation matrix
		result.elements[0] = xAxis.x;
		result.elements[1] = yAxis.x;
		result.elements[2] = zAxis.x;
		result.elements[3] = 0.0f;

		result.elements[4] = xAxis.y;
		result.elements[5] = yAxis.y;
		result.elements[6] = zAxis.y;
		result.elements[7] = 0.0f;

		result.elements[8] = xAxis.z;
		result.elements[9] = yAxis.z;
		result.elements[10] = zAxis.z;
		result.elements[11] = 0.0f;

		// Fill the translation part
		result.elements[12] = -gui_math::dot(xAxis, position);
		result.elements[13] = -gui_math::dot(yAxis, position);
		result.elements[14] = -gui_math::dot(zAxis, position);
		result.elements[15] = 1.0f;

		return result;
	}


}