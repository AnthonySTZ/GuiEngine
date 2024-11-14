#include "GuiEngine.h"
#include <iostream>
int main() 
{
	const char* glsl_version = engine::InitGLFW();
	if (!glsl_version)
		return 1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", nullptr, nullptr);
	ImGuiIO& io = engine::InitImGui(window, glsl_version);

	engine::Renderer renderer = engine::Renderer();
	renderer.BindShaders();
	renderer.GenTexture2D();
	renderer.InitBuffers();

	while (!glfwWindowShouldClose(window))
	{
		engine::PollEvents();
		engine::NewFrame();
		engine::ShowDockspace(io);

		ImGui::Begin("Viewport");
		ImVec2 w_size = ImGui::GetContentRegionAvail();
		renderer.Render(w_size.x, w_size.y);
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