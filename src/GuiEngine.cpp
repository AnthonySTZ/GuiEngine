#include "GuiEngine.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


std::string readFromFile(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open())
        return "";

    std::stringstream ss{};
    ss << file.rdbuf();
    file.close();
    return ss.str();
}


namespace engine
{

    const char* InitGLFW()
	{

        if (!glfwInit())
            return "";

        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return glsl_version;

	}
    void SetElementsColors(ImGuiStyle& style, ImVec4 color, std::vector<ImGuiCol_> elements)
    {
        for each (ImGuiCol_ element in elements)
        {
            style.Colors[element] = color;
        }

    }
    ImGuiIO& InitImGui(GLFWwindow* window, const char* glsl_version, int vsync)
    {
        
        glfwMakeContextCurrent(window);
        glfwSwapInterval(vsync); // Enable/Disable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;        // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows


        // Change Windows style
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.WindowMenuButtonPosition = ImGuiDir_None;
        style.WindowPadding = ImVec2(0.0f, 0.0f);
        ImVec4 dark_color = ImVec4(0.1f, 0.1f, 0.11f, 1.0f);
        std::vector<ImGuiCol_> dark_elements = {
            ImGuiCol_WindowBg,
            ImGuiCol_ChildBg,
            ImGuiCol_PopupBg,
            ImGuiCol_TitleBg,
            ImGuiCol_TitleBgActive,
            ImGuiCol_TitleBgCollapsed,
            ImGuiCol_Header,
            ImGuiCol_HeaderHovered,
            ImGuiCol_HeaderActive,
            ImGuiCol_ScrollbarBg,
            ImGuiCol_Tab,
            ImGuiCol_TabHovered,
            ImGuiCol_TabSelected,
            ImGuiCol_TabSelectedOverline,
            ImGuiCol_TabDimmed,
            ImGuiCol_TabDimmedSelected,
            ImGuiCol_TabDimmedSelectedOverline,

        };
        SetElementsColors(style, dark_color, dark_elements);

        ImVec4 blue_color = ImVec4(0.1f, 0.2f, 0.4f, 1.0f);
        std::vector<ImGuiCol_> blue_elements = {
            ImGuiCol_TitleBg,
            ImGuiCol_TitleBgActive,
            ImGuiCol_TitleBgCollapsed,
            ImGuiCol_Tab,
            ImGuiCol_TabHovered,
            ImGuiCol_TabSelected,
            ImGuiCol_TabSelectedOverline,
            ImGuiCol_TabDimmed,
            ImGuiCol_TabDimmedSelected,
            ImGuiCol_TabDimmedSelectedOverline,
            ImGuiCol_Border
        };
        SetElementsColors(style, blue_color, blue_elements);

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        return io;
    }
    void PollEvents()
    {
        glfwPollEvents();
    }
    void NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void ShowDockspace(ImGuiIO& io)
    {
        bool p_open = false;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each other.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking; // No MenuBar flag here
       
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        // Submit the DockSpace
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();

    }

    void Render(GLFWwindow* window, ImGuiIO& io)
    {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    void Shutdown(GLFWwindow* window)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Renderer::BindShaders()
    {
        if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

        // Load and compile shader from file
        std::string vertexShaderCode = readFromFile("../../../src/shaders/vertex_shader.glsl");
        std::string fragmentShaderCode = readFromFile("../../../src/shaders/fragment_shader.glsl");

        const char* vertexShaderSource = vertexShaderCode.c_str();
        const char* fragmentShaderSource = fragmentShaderCode.c_str();

        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Check for compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Check for fragment shader compilation errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    void Renderer::GenTexture2D()
    {
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &textureColorBuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "Framebuffer not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Renderer::InitBuffers(std::vector<Vertex> vertices, std::vector<int> indices)
    {
        // Generate and bind VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // Generate and bind EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

        // Define position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // Define color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // Unbind the VAO (optional)
        glBindVertexArray(0);

    }

    void Renderer::Render(int w_width, int w_height, Scene scene)
    {
        scene.camera.aspectRatio = (float)w_width / (float)w_height;
        gui_math::Matrix4 view = scene.camera.getViewMatrix();
        gui_math::Matrix4 projection = scene.camera.getProjectionMatrix();
        /*std::cout << "Projection Matrix:\n";
        for (int j = 0; j < 4; ++j) {
            for (int i = 0; i < 4; ++i) {
                std::cout << view.elements[i * 4 + j] << " ";
            }
            std::cout << std::endl;
        }*/

        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "proj");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.elements);

        GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.elements);

        // Refresh Viewport size
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_width, w_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glViewport(0, 0, w_width, w_height);
        glClearColor(0.4f, 0.6f, 0.6f, 1.0f);  // Blue background
        glClear(GL_COLOR_BUFFER_BIT);

        // Render triangle with shader program
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, scene.indices.size(), GL_UNSIGNED_INT, 0);

        // Unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
    }

}