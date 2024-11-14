#include "GuiEngine.h"
#include <iostream>
#include<array> 

int main() 
{
	const char* glsl_version = engine::InitGLFW();
	if (!glsl_version)
		return 1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
	ImGuiIO& io = engine::InitImGui(window, glsl_version, 0);

	engine::Renderer renderer = engine::Renderer();
	renderer.BindShaders();
	renderer.GenTexture2D();

	float vertices[] = {
	 -.5f,-0.5f, 0.0f,
	 -0.5f, 0.5f, 0.0f,
	 .5f,  .5f, 0.0f,

	 -.5f,-0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 .5f,  .5f, 0.0f,
	};
	int number_of_vertices = (int)(sizeof(vertices) / sizeof(*vertices) / 3);

	renderer.InitBuffers(vertices, sizeof(vertices));

	while (!glfwWindowShouldClose(window))
	{
		engine::PollEvents();
		engine::NewFrame();
		engine::ShowDockspace(io);

		ImGui::Begin("Viewport");
		ImVec2 w_size = ImGui::GetContentRegionAvail();
		renderer.Render(w_size.x, w_size.y, number_of_vertices);
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