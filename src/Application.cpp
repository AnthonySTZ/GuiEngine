#include "GuiEngine.h"
#include <iostream>
#include<array> 

#include "3DHandler.h"

int main() 
{
	// Define Scene
	Vector3 vector_01 = Vector3(-0.5f, -0.5f, 0.0f);
	Vector3 vector_02 = Vector3(-0.5f, 0.5f, 0.0f);
	Vector3 vector_03 = Vector3(.5f, .5f, 0.0f);
	Vector3 vector_04 = Vector3(.5f, -.5f, 0.0f);

	Vector3 red = Vector3(0.8f, 0.0f, 0.0f);
	Vector3 green = Vector3(0.0f, 0.8f, 0.0f);
	Vector3 blue = Vector3(0.0f, 0.0f, 0.8f);
	Vector3 yellow = Vector3(0.8f, 0.8f, 0.0f);

	Vertex point_01 = Vertex(vector_01, red);
	Vertex point_02 = Vertex(vector_02, green);
	Vertex point_03 = Vertex(vector_03, blue);
	Vertex point_04 = Vertex(vector_04, yellow);

	Scene scene = Scene();
	std::vector<Vertex> scene_vertices = { point_01, point_02, point_03, point_04 };
	std::vector<int> scene_indices = { 
		0, 1, 2,
		0, 2, 3
	};
	scene.AddVertices(scene_vertices);
	scene.AddIndices(scene_indices);

	//Init camera
	Vector3 cam_position = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 cam_direction = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cam_upVector = Vector3(0.0f, 1.0f, 0.0f); 
	float cam_fov = 45.0f;
	float cam_aspect = 16.0f/9.0f;
	Camera camera = Camera(cam_position, cam_direction, cam_upVector, cam_fov, cam_aspect);
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

	while (!glfwWindowShouldClose(window))
	{
		// Refresh UI
		engine::PollEvents();
		engine::NewFrame();
		engine::ShowDockspace(io);

		// Render Viewport
		ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoMove);
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