#version 330 core

// COORDENADAS
layout (location = 0) in vec3 aPos;
// COLORES
layout (location = 1) in vec3 aColor;
// COORDINADAS DE LAS TEXTURAS
layout (location = 2) in vec2 aTex;
// NORMALES
layout (location = 3) in vec3 aNormal;


// OUTPUT DE LOS COLORES HACIA FRAGMENT 
out vec3 color;
// OUTPUT TEXTURAS HACIA FRAGMENT
out vec2 texCoord;
// OUTPUTS DE LA NORMAL HACIA EL FRAGMENT
out vec3 Normal;
// OUTPUT POSICION ACTUAL
out vec3 crntPos;


uniform mat4 camMatrix;

uniform mat4 model;


void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	color = aColor;
	texCoord = aTex;
	Normal = aNormal;
}