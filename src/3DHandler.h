#pragma once

#include "GuiMath.h"
#include "glfw/glfw3.h"
#include "imgui.h"
#include <iostream>
#include <vector>

enum Action {
	MOVING_FORWARD,
	MOVING_BACKWARD,
	MOVING_RIGHT,
	MOVING_LEFT,
	MOVING_UP,
	MOVING_DOWN
};

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
		yaw(-90.0f), pitch(0.0f),
		movementSpeed(2.5f), mouseSensitivity(0.05f)	
	{
		// Initialize right vector
		right = gui_math::normalize(gui_math::cross(direction, up));
	};
	gui_math::Matrix4 getProjectionMatrix();
	gui_math::Matrix4 getLookAtMatrix(gui_math::Vector3 target);
	gui_math::Matrix4 getViewMatrix();
	void move(Action action, float deltaTime);
	void updateCameraVectors();
};


class Scene
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	Camera camera;
	bool firstMouse = true;
	float lastX = 0;
	float lastY = 0;
	Scene() {};
	void AddVertices(std::vector<Vertex> vertices_list);
	void AddIndices(std::vector<int> indicies_list);
	void SetCamera(Camera camera_) {camera = camera_;};
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(double xpos, double ypos);
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
};