#version 330 core

//posicion y coordinadas
layout (location = 0) in vec3 aPos;
// Colores
layout (location = 1) in vec3 aColor;


// Da salida al color para el Fragment Shader
out vec3 color;
// controla la escala de los vertices
uniform float scale;


void main()
{
	// Da output la posicion coordinada de todos los vectores
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// asignamos cada color del vertx Data
	color = aColor;
}