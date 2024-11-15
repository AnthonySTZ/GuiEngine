#version 330 core

uniform mat4 proj;  // Projection matrix
uniform mat4 view;  // View matrix

layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 vertexColor; // Output color to the fragment shader

void main()
{
    gl_Position = proj * view * vec4(aPos, 1.0);
    vertexColor = aColor; // Pass the input color to the fragment shader
}