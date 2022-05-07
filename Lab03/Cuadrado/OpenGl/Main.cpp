#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLfloat vertices[] =
	{
		0.5f, 0.5f, 0.0f,  //abajo derechaS
		0.5f,-0.5f,0.0f,  // abajo izquierda
		-0.5f, -0.5f, 0.0f,  //arriba izquierda
		- 0.5f, 0.5f,0.0f
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGLEDWARD", NULL, NULL);
	glfwMakeContextCurrent(window);
	// abrir las configuraciones de opengl
	gladLoadGL();
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// cero pos inicial, 3 vertices, tipo de valores, la distancia de los puntos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// activamos pos inicial
	glEnableVertexAttribArray(0);
	//PAra asegurarnos obligaremos a los buffers estar en la posicion cero
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	

	//revisamos si se creo correctamente o no.
	if (window == NULL) {
		std::cout << "Error al crear" << std::endl;
		// esta funcion es para terminar GLFW 
		glfwTerminate();
		return -1;
	}

	// pinta desde la posicion x,,y 0 hasta la 800 
	glViewport(0, 0, 800, 800);
	// ESTAMOS CREANDO EL COLOR EN EL BACK BUFFER 
	glad_glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//PARA PASARLO AL FRONT BUFFER
	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window)) {
		glad_glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// activamos el programa shader que creamos anteriormente 
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, 0);

		// Intercambiar BUFFERES BACK A FRONT
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// Destruir la ventana despues de que se ejecute la funcion principal
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}