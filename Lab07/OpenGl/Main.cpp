#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// vertices
GLfloat vertices[] =
{ //     COORDINADAS     /        COLORES      /   TexCoordinadas  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // IZQUIERDA ABAJO
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // IZQUIERDA ARRIBA
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // DERECHA ARRIBA
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // DERECHA ABAJO
};

// INDICES Y ORDEN DE LOS VERTICES A DIBUJAR
GLuint indices[] =
{
	0, 2, 1, // Triangulo de arriba
	0 , 3, 2 // Triagunlo de abajo
};



int main()
{
	// INICIAMOS GLWF
	glfwInit();

	// VERSION DE OPEN GL  EN NUESTRO CASO 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// CORE PROFILE
	// USAMOS FUNCIONES MODERNAS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFWINDOW DE 800X800 PIXELES LLAMADA EDWARD HUAYLLASCO
	GLFWwindow* window = glfwCreateWindow(800, 800, "EDWARDHUAYLLASCO", NULL, NULL);
	// SI FALLA AL CREARSE
	if (window == NULL)
	{
		std::cout << "HA FALLADO LA CREACION DE LA PANTALLA" << std::endl;
		glfwTerminate();
		return -1;
	}
	// INTRODUCE LA PANTALLA EN EL CURRENT CONTEXT 
	glfwMakeContextCurrent(window);

	//CARGA EL GLAD PARA GL
	gladLoadGL();
	// ESPECIFICA EL VIEWPORT PARA LA PANTALLA
	// EL VIEWPORT ES x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// GENERAMOS LOS SHADERS YA SEPARADOS EN DOS ARCHIVOS
	Shader shaderProgram("default.vert", "default.frag");



	// GENERAMOS LOS ARRAYS Y LOS ENLAZAMOS
	VAO VAO1;
	VAO1.Bind();

	// GENERAMOS LOS BUFFER PARA LOS VERTICES
	VBO VBO1(vertices, sizeof(vertices));
	// GENERAMOS LOS ELEMENTOS DEL BUFFER Y LOS ENLAZAMOS A LOS INDICES
	EBO EBO1(indices, sizeof(indices));

	// ENLANZAMOS LOS ATRIBUTOS VBO COMO LAS COORDENADA Y COLORSE AL VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// DESENLAZAMOS PARA EVITAR ERRORES
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// OBTIENE LA IDENTIFICACION DEL UNIFORME SCALE
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// TEXTURAS
	// Creamos tres variables enteras para ordenar el ancho y el alto de la imagen en pixeles y la cantidad de canales de color que tiene
	int widthImg, heightImg, numCo1Ch;
	stbi_set_flip_vertically_on_load(true);
	// almacenamos la imagen en un unsigned char usando la funcion sdbi_load y dando la ubicacion y el nombre de la imagen.
	unsigned char* bytes = stbi_load("descarga.png", &widthImg, &heightImg, &numCo1Ch, 0);

	GLuint texture;
	glGenTextures(1, &texture); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	//GL NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);

	// textura2 
	GLuint texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//GL NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	unsigned char* bytes1 = stbi_load("descarga1.png", &widthImg, &heightImg, &numCo1Ch, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes1);

	glGenerateMipmap(GL_TEXTURE_2D);
	//DESVINCULAR TEXTURAS
	stbi_image_free(bytes);
	stbi_image_free(bytes1);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "texture");
	GLuint tex0Uni1 = glGetUniformLocation(shaderProgram.ID, "texture1");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);
	glUniform1i(tex0Uni1, 1);
	while (!glfwWindowShouldClose(window))
	{
		// ESPECIFICAMOS EL COLOR DEL BACKGROUND
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// LOMPIAMOS EL BACK BUFFER Y ASIGNAMOS EL NUEVO COLOR
		glClear(GL_COLOR_BUFFER_BIT);
		// LE DECIMOS AL OPENGL QUE SHADER VAMOS A USAR
		shaderProgram.Activate();
		// ASIGNAMOS UN VALOR AL UNIFORM 
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindTexture(GL_TEXTURE_2D, texture1);
		// HACEMOS BIND AL VAO 
		VAO1.Bind();
		// DIBUJAMOS LAS PRIMITIVA, NUMEROS DE INDICES, LOS TIPOS DE DATO DE LOS INDICES, LOS INDEX DE LOS INDICES
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// CAMBIAMOS EL BACK POR EL FRONT
		glfwSwapBuffers(window);
		// GLFW EVENTS
		glfwPollEvents();
	}



	// BORRAMOS TODOS LOS ELEEMTNOS CREADOS
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	// BORRAMOS LA PANTALLA ANTES DE QUE CERREMOS EL PROGRAMA
	glfwDestroyWindow(window);
	// TERMINAMOS GLFW
	glfwTerminate();
	return 0;
}