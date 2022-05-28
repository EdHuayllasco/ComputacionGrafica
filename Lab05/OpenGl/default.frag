#version 330 core

// Outputs colores en RGBA
out vec4 FragColor;


// Introducimos el color desde el Vertex Shader
in vec3 color;


void main()
{
	FragColor = vec4(color, 1.0f);
}