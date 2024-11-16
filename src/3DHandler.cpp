#include "3DHandler.h"


void Scene::AddVertices(std::vector<Vertex> vertices_list)
{
	for each(Vertex vertex in vertices_list)
	{
		vertices.push_back(vertex);
	}	
}

void Scene::AddIndices(std::vector<int> indicies_list)
{
	for each (int index in indicies_list)
	{
		indices.push_back(index);
	}
}

Camera::Camera()
	: position(gui_math::Vector3(0.0f, 0.0f, 0.0f)),
	direction(gui_math::Vector3(0.0f, 0.0f, -1.0f)),
	up(gui_math::Vector3(0.0f, 1.0f, 0.0f)),
	right(gui_math::Vector3(1.0f, 0.0f, 0.0f)),
	aspectRatio(1.0f),
	fov(45.0f),
	yaw(0.0f),
	pitch(0.0f),
	movementSpeed(2.5f),
	mouseSensitivity(0.1f) {

}

gui_math::Matrix4 Camera::getProjectionMatrix()
{
	float fovRadians = fov * (gui_math::PI / 180.0f); // Convert FOV to radians
	return gui_math::Matrix4::perspective(fovRadians, aspectRatio, 0.1f, 100.0f); // near = 0.1, far = 100.0
}

gui_math::Matrix4 Camera::getLookAtMatrix(gui_math::Vector3 target)
{
	return gui_math::Matrix4::lookAt(position, target, up);
}

gui_math::Matrix4 Camera::getViewMatrix()
{
	return gui_math::Matrix4::view(position, direction, up);
}
