#pragma once

#include <iostream>

namespace gui_math
{
	
	struct Vector3
	{
		float x, y, z;
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
		Vector3 operator+(Vector3 vector3);
		Vector3 operator-(Vector3 vector3);
		Vector3 operator-();
		Vector3 operator/(float divider);
		friend std::ostream& operator<<(std::ostream& os, const Vector3& vector3);
	};

	const float PI = 3.14159265358979323846;
	Vector3 cross(Vector3 vec_01, Vector3 vec_02);
	float length(Vector3 vec);
	Vector3 normalize(Vector3 vec);
	float dot(Vector3 vec_01, Vector3 vec_02);

	class Matrix4 {
	public:
		float elements[16] = { 0 };

		Matrix4() = default;

		static Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
		static Matrix4 perspective(float fov, float aspect, float near, float far);
		static Matrix4 view(Vector3 position, Vector3 direction, Vector3 up);
	};

}