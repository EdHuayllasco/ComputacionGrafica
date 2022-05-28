#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// vertices
GLfloat vertices[] =
{ //               COORDINADAS                  /     COLORES           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // ESQUINA IZQUIERDA BAJA
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // ESQUINA DERECHA BAJA
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // ESQUINA SUPERIOR
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // DENTRO IZQUIERDA
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // DENTRO DERECHA
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // DENTRO ABAJO
};

// INDICES Y ORDEN DE LOS VERTICES A DIBUJAR
GLuint indices[] =
{
	0, 3, 5, // TRIANGULO,ABAJO IZQUIERDA
	3, 2, 4, // TRIANGULO, ABAJO DERECHA
	5, 4, 1 // ARRIBA TRIANGULO
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// DESENLAZAMOS PARA EVITAR ERRORES
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// OBTIENE LA IDENTIFICACION DEL UNIFORME SCALE
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// MAIN WHILE
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
		// HACEMOS BIND AL VAO 
		VAO1.Bind();
		// DIBUJAMOS LAS PRIMITIVA, NUMEROS DE INDICES, LOS TIPOS DE DATO DE LOS INDICES, LOS INDEX DE LOS INDICES
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// CAMBIAMOS EL BACK POR EL FRONT
		glfwSwapBuffers(window);
		// GLFW EVENTS
		glfwPollEvents();
	}



	// BORRAMOS TODOS LOS ELEEMTNOS CREADOS
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// BORRAMOS LA PANTALLA ANTES DE QUE CERREMOS EL PROGRAMA
	glfwDestroyWindow(window);
	// TERMINAMOS GLFW
	glfwTerminate();
	return 0;
}