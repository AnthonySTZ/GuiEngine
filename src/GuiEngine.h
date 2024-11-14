#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace engine
{

	const char* InitGLFW();
	ImGuiIO& InitImGui(GLFWwindow* window, const char* glsl_version);
	void PollEvents();
	void NewFrame();
	void ShowDockspace(ImGuiIO& io);
	void Render(GLFWwindow* window, ImGuiIO& io);
	void Shutdown(GLFWwindow* window);

	class Renderer
	{
	public:
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLuint framebuffer;
		GLuint textureColorBuffer;
		GLuint VAO, VBO;
		void BindShaders();
		void GenTexture2D();
		void InitBuffers();
		void Render(int w_width, int w_height);
	};
}