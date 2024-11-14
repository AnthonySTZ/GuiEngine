#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace engine
{

	const char* InitGLFW();
	ImGuiIO& InitImGui(GLFWwindow* window, const char* glsl_version);
	void PollEvents();
	void NewFrame();
	void ShowDockspace(ImGuiIO& io);
	void Render(GLFWwindow* window, ImGuiIO& io);
	void Shutdown(GLFWwindow* window);

}