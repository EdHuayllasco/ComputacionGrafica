#version 330 core

// RGBA OUTPUT DE COLORES
out vec4 FragColor;


// IMPORTAR COLOR DESDE EL VERTEX SHADER
in vec3 color;
// IMPORTAR TEXTURA Y COORDINADAS DESDE EL VERTEX SHADER
in vec2 texCoord;
// IMPORTAR LA NORMAL DEL VERTEX SHADER 
in vec3 Normal;
// IMPORTAR LA POSICION ACTUAL DEL VEXTEX SHADER
in vec3 crntPos;


uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	// LIGHTING 
	float ambient = 0.20f;

	// HACERLO DIFUSO
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// SPECULAR
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	// OUTPUT DE LOS COLORES
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}