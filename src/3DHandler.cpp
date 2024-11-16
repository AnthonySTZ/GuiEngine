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

void Scene::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(MOVING_FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(MOVING_BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(MOVING_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(MOVING_RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.move(MOVING_UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.move(MOVING_DOWN, deltaTime);
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

void Camera::move(Action action, float deltaTime)
{
	switch (action) {

		case MOVING_FORWARD: {

			position += direction * deltaTime * movementSpeed;
			break;
		}
		case MOVING_BACKWARD: {

			position -= direction * deltaTime * movementSpeed;
			break;
		}
		case MOVING_RIGHT: {
			right = gui_math::normalize(gui_math::cross(up, direction));
			position += right * deltaTime * movementSpeed;
			break;
		}
		case MOVING_LEFT: {
			right = gui_math::normalize(gui_math::cross(up, direction));
			position -= right * deltaTime * movementSpeed;
			break;
		}
		case MOVING_UP: {
			position += up * deltaTime * movementSpeed;
			break;
		}
		case MOVING_DOWN: {
			right = gui_math::normalize(gui_math::cross(up, direction));
			position -= up * deltaTime * movementSpeed;
			break;
		}
	}
}
