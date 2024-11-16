#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "3DHandler.h"

#include <vector>

namespace engine
{

	const char* InitGLFW();
	void SetElementsColors(ImGuiStyle& style, ImVec4 color, std::vector<ImGuiCol_> elements);
	ImGuiIO& InitImGui(GLFWwindow* window, const char* glsl_version, int vsync);
	void PollEvents(GLFWwindow* window);
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
		GLuint depthBuffer;
		GLuint VAO, VBO, EBO;
		void BindShaders();
		void GenTexture2D();		
		void InitBuffers(std::vector<Vertex> vertices, std::vector<int> indices);
		void Render(int w_width, int w_height, Scene scene);
	};
}