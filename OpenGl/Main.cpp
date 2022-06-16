#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
const unsigned int width = 800;
const unsigned int height = 800;

// vertices
GLfloat vertices[] =
{ //     COORDINADAS     /        COLORES      /   TexCoordinadas  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
// INDICES Y ORDEN DE LOS VERTICES A DIBUJAR
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
	Texture Fondo("descarga.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Fondo.texUnit(shaderProgram, "text0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		// ESPECIFICAMOS EL COLOR DEL BACKGROUND
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// LOMPIAMOS EL BACK BUFFER Y ASIGNAMOS EL NUEVO COLOR
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// LE DECIMOS AL OPENGL QUE SHADER VAMOS A USAR
		shaderProgram.Activate();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0));
		proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);

		
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// ASIGNAMOS UN VALOR AL UNIFORM 
		glUniform1f(uniID, 0.5f);
		// HACEMOS BIND AL VAO 
		Fondo.Bind();
		VAO1.Bind();
		// DIBUJAMOS LAS PRIMITIVA, NUMEROS DE INDICES, LOS TIPOS DE DATO DE LOS INDICES, LOS INDEX DE LOS INDICES
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// CAMBIAMOS EL BACK POR EL FRONT
		glfwSwapBuffers(window);
		// GLFW EVENTS
		glfwPollEvents();
	}



	// BORRAMOS TODOS LOS ELEEMTNOS CREADOS
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	Fondo.Delete();
	shaderProgram.Delete();
	// BORRAMOS LA PANTALLA ANTES DE QUE CERREMOS EL PROGRAMA
	glfwDestroyWindow(window);
	// TERMINAMOS GLFW
	glfwTerminate();
	return 0;
}