#include "GuiEngine.h"
#include <iostream>
#include<array> 

#include "3DHandler.h"

int main() 
{

	Vector3 vector_01 = Vector3(-.5f, -0.5f, 0.0f);
	Vector3 vector_02 = Vector3(-0.5f, 0.5f, 0.0f);
	Vector3 vector_03 = Vector3(.5f, .5f, 0.0f);
	Vertex point_01 = Vertex(vector_01);
	Vertex point_02 = Vertex(vector_02);
	Vertex point_03 = Vertex(vector_03);
	Scene scene = Scene();
	std::vector<Vertex> scene_vertices = { point_01, point_02, point_03 };
	scene.AddVertices(scene_vertices);


	const char* glsl_version = engine::InitGLFW();
	if (!glsl_version)
		return 1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
	ImGuiIO& io = engine::InitImGui(window, glsl_version, 0);

	engine::Renderer renderer = engine::Renderer();
	renderer.BindShaders();
	renderer.GenTexture2D();


	renderer.InitBuffers(scene.vertices);

	while (!glfwWindowShouldClose(window))
	{
		engine::PollEvents();
		engine::NewFrame();
		engine::ShowDockspace(io);

		ImGui::Begin("Viewport");
		ImVec2 w_size = ImGui::GetContentRegionAvail();
		renderer.Render(w_size.x, w_size.y, scene.vertices.size());
		ImGui::Image((intptr_t)renderer.textureColorBuffer, ImVec2(w_size.x, w_size.y));
		ImGui::End();

		ImGui::Begin("Tools");
		ImGui::Text("Stats: %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		engine::Render(window, io);
	}
	engine::Shutdown(window);
	return 0;

}