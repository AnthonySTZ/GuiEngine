#include "GuiEngine.h"
#include <iostream>
#include<array> 

#include "3DHandler.h"

int main() 
{
	// Define Scene
	// TOP
	gui_math::Vector3 vector_01 = gui_math::Vector3(-0.5f, 0.5f, -0.5f);
	gui_math::Vector3 vector_02 = gui_math::Vector3(0.5f, 0.5f, -0.5f);
	gui_math::Vector3 vector_03 = gui_math::Vector3(0.5f, 0.5f, 0.5f);
	gui_math::Vector3 vector_04 = gui_math::Vector3(-0.5f, 0.5f, 0.5f);

	// BOTTOM
	gui_math::Vector3 vector_05 = gui_math::Vector3(-0.5f, -0.5f, -0.5f);
	gui_math::Vector3 vector_06 = gui_math::Vector3(0.5f, -0.5f, -0.5f);
	gui_math::Vector3 vector_07 = gui_math::Vector3(0.5f, -0.5f, 0.5f);
	gui_math::Vector3 vector_08 = gui_math::Vector3(-0.5f, -0.5f, 0.5f);

	gui_math::Vector3 red = gui_math::Vector3(0.8f, 0.0f, 0.0f);
	gui_math::Vector3 green = gui_math::Vector3(0.0f, 0.8f, 0.0f);
	gui_math::Vector3 blue = gui_math::Vector3(0.0f, 0.0f, 0.8f);
	gui_math::Vector3 yellow = gui_math::Vector3(0.8f, 0.8f, 0.0f);

	Vertex point_01 = Vertex(vector_01, red);
	Vertex point_02 = Vertex(vector_02, red);
	Vertex point_03 = Vertex(vector_03, red);
	Vertex point_04 = Vertex(vector_04, red);

	Vertex point_05 = Vertex(vector_05, blue);
	Vertex point_06 = Vertex(vector_06, blue);
	Vertex point_07 = Vertex(vector_07, blue);
	Vertex point_08 = Vertex(vector_08, blue);

	Scene scene = Scene();
	std::vector<Vertex> scene_vertices = { 
		point_01, point_02, point_03, point_04,
		point_05, point_06, point_07, point_08 
	};
	std::vector<int> scene_indices = { 
		// Top face
		0, 1, 2,  2, 3, 0,

		// Bottom face
		4, 7, 6,  6, 5, 4,

		// Back face
		0, 4, 1,  1, 4, 5,

		// Front face
		3, 2, 7,  7, 2, 6,

		// Right face
		2, 1, 5,  5, 6, 2,

		// Left face
		0, 3, 4,  4, 3, 7		
	
	};
	scene.AddVertices(scene_vertices);
	scene.AddIndices(scene_indices);

	//Init camera
	gui_math::Vector3 cam_position = gui_math::Vector3(1.0f, 0.0f, 10.0f);
	gui_math::Vector3 cam_direction = gui_math::Vector3(0.0f, 0.0f, -1.0f);
	gui_math::Vector3 cam_upVector = gui_math::Vector3(0.0f, 1.0f, 0.0f);
	float cam_fov = 45.0f;
	float cam_aspect = 16.0f/9.0f;
	Camera camera = Camera(cam_position, cam_direction, cam_upVector, cam_fov, cam_aspect);
	camera.movementSpeed = 6.0f;
	scene.SetCamera(camera);

	// Init Window
	const char* glsl_version = engine::InitGLFW();
	if (!glsl_version)
		return 1;

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "GuiEngine", nullptr, nullptr);
	ImGuiIO& io = engine::InitImGui(window, glsl_version, 0);

	// Init Renderer
	engine::Renderer renderer = engine::Renderer();
	renderer.BindShaders();
	renderer.GenTexture2D();
	renderer.InitBuffers(scene.vertices, scene.indices);

	float currentFrame, deltaTime, lastFrame = 0.0f;
	double xpos, ypos;

	while (!glfwWindowShouldClose(window))
	{

		// Refresh UI
		engine::PollEvents(window);
		engine::NewFrame();
		engine::ShowDockspace(io);

		// Render Viewport
		ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoMove);
		if (ImGui::IsWindowFocused())
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			scene.processInput(window, deltaTime);
			glfwGetCursorPos(window, &xpos, &ypos);
			scene.mouse_callback(xpos, ypos);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			scene.firstMouse = true;
		}
		ImVec2 w_size = ImGui::GetContentRegionAvail();
		renderer.Render(w_size.x, w_size.y, scene);
		ImGui::Image((intptr_t)renderer.textureColorBuffer, ImVec2(w_size.x, w_size.y));
		ImGui::End();

		// Add Tools Bar
		ImGui::Begin("Tools", NULL, ImGuiWindowFlags_NoMove);
		ImGui::Text("Stats: %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		// Render all the window UI (show everything to screen)
		engine::Render(window, io);
	}

	engine::Shutdown(window);
	return 0;

}