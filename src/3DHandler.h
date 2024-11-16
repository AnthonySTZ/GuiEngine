#pragma once

#include "GuiMath.h"
#include <iostream>
#include <vector>

struct Vertex
{
	gui_math::Vector3 position;
	gui_math::Vector3 color;
	Vertex(gui_math::Vector3 position, gui_math::Vector3 color) : position(position), color(color) {};
};

class Camera
{
public:
	gui_math::Vector3 position = gui_math::Vector3();
	gui_math::Vector3 direction = gui_math::Vector3();
	gui_math::Vector3 up = gui_math::Vector3();
	gui_math::Vector3 right = gui_math::Vector3();
	float aspectRatio = 0.0f;
	float fov = 0.0f;
	float yaw = 0.0f;                 // Rotation around the Y-axis
	float pitch = 0.0f;               // Rotation around the X-axis
	float movementSpeed = 0.0f;       // Speed of camera movement (translation)
	float mouseSensitivity = 0.0f;    // Sensitivity for mouse movement (rotation)
	Camera();
	Camera(gui_math::Vector3 pos, gui_math::Vector3 dir, gui_math::Vector3 upVector, float fov_, float aspect)
		: position(pos), direction(dir), up(upVector), fov(fov_), aspectRatio(aspect),
		yaw(0.0f), pitch(0.0f),
		movementSpeed(2.5f), mouseSensitivity(0.1f)	
	{
		// Initialize right vector
		right = gui_math::normalize(gui_math::cross(direction, up));
	};
	gui_math::Matrix4 getProjectionMatrix();
	gui_math::Matrix4 getLookAtMatrix(gui_math::Vector3 target);
	gui_math::Matrix4 getViewMatrix();
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