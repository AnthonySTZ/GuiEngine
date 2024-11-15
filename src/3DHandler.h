#pragma once

#include <iostream>
#include <vector>

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

struct Vertex
{
	Vector3 position;
	Vector3 color;
	Vertex(Vector3 position, Vector3 color) : position(position), color(color) {};
};


namespace gui_math
{
	const float PI = 3.14159265358979323846;
	Vector3 cross(Vector3 vec_01, Vector3 vec_02);
	float length(Vector3 vec);
	Vector3 normalize(Vector3 vec);
	float dot(Vector3 vec_01, Vector3 vec_02);

}

class Matrix4 {
public:
	float elements[16] = { 0 };

	Matrix4() = default;

	static Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
	static Matrix4 perspective(float fov, float aspect, float near, float far);
	static Matrix4 view(Vector3 position, Vector3 direction, Vector3 up);
};

class Camera
{
public:
	Vector3 position = Vector3();
	Vector3 direction = Vector3();
	Vector3 up = Vector3();
	Vector3 right = Vector3();
	float aspectRatio = 0.0f;
	float fov = 0.0f;
	float yaw = 0.0f;                 // Rotation around the Y-axis
	float pitch = 0.0f;               // Rotation around the X-axis
	float movementSpeed = 0.0f;       // Speed of camera movement (translation)
	float mouseSensitivity = 0.0f;    // Sensitivity for mouse movement (rotation)
	Camera()
		: position(Vector3(0.0f, 0.0f, 0.0f)),
		direction(Vector3(0.0f, 0.0f, -1.0f)),
		up(Vector3(0.0f, 1.0f, 0.0f)),
		right(Vector3(1.0f, 0.0f, 0.0f)),
		aspectRatio(1.0f),
		fov(45.0f),
		yaw(0.0f),
		pitch(0.0f),
		movementSpeed(2.5f),
		mouseSensitivity(0.1f) {}
	Camera(Vector3 pos, Vector3 dir, Vector3 upVector, float fov_, float aspect)
		: position(pos), direction(dir), up(upVector), fov(fov_), aspectRatio(aspect),
		yaw(0.0f), pitch(0.0f),
		movementSpeed(2.5f), mouseSensitivity(0.1f)	
	{
		// Initialize right vector
		right = gui_math::normalize(gui_math::cross(direction, up));
	};
	Matrix4 getProjectionMatrix();
	Matrix4 getLookAtMatrix(Vector3 target);
	Matrix4 getViewMatrix();
};


class Scene
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	Camera camera;
	Scene() {};
	void AddVertices(std::vector<Vertex> vertices_list);
	void AddIndices(std::vector<int> indicies_list);
	void SetCamera(Camera camera_) {camera = camera_;};
};