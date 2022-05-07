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
	// Esta funcion es para incializar GLFW y asi poder usar sus funciones
	glfwInit();
	
	// le damos la version de GLFW que estamos usando
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	
	// Como la version es 3.3 nos falta el decimal
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// tenemos que decir que opengl estamos usando si el basico o el moderno, nosotros usamos el moderno
	//por lo cual usaremos el core_profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// glfloat es un tipo de dato en opengl
	GLfloat vertices[] =
		//coordenadas triangulo equilatero
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // abajo izquierda
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // abajo derecha
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // medio arriba
	};

	// para crear la ventana, necesitamos un tipo GLFWwindow puntero, su constructor tiene 5 entradas
	// ancho, alto de la ventana, nombre de la pantalla, si la queremos pantalla full o no, lo ultimo no me acuerdo
	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGLEDWARD", NULL, NULL);
	// Le dice a GLFW que la pantalla es parte del contexto actual 
	// contexto es una especie de objeto que contiene todo opengl
	glfwMakeContextCurrent(window);
	// abrir las configuraciones de opengl
	gladLoadGL();
	//dato entero sin signo o positivo
	// debemos especificar que tipo de shader queremos en este caso un vertice
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	// el 1 es porque usamos una cadena para todo el shader, luego apuntamos a source code
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	//compilar
	glCompileShader(vertexshader);
	// Fragment Shader, hacemos lo mismo
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);

	//shader Program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexshader);
	glAttachShader(shaderProgram, fragmentshader);
	glLinkProgram(shaderProgram);
	// Como ya tenemos creados nuestro programa con nuestro shaders, podemos eliminar
	// los vertices creados.

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	// creamos el buffer enviamos 1 porque solo tenemos un objeto 3d, y darle una referencia
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Nuestro objeto esta vacio, asi que le enviaremos los vertices programados.
	// enviamos primero el tipo de buffer, luego el tamano en bits, luego los vertices, y el tipo de flujo
	// en este caso estatico , signfica que se modicaran una vez y tambien DRAW indica que seran dibujados.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
	// esta funcion nos indica que unicamente se cerrara la pantalla windows cuando aprentemos el boton de cerrar
	// sino seguira en funccionamiento por el while
	// o si otra funcion le dice que se cierre
	while (!glfwWindowShouldClose(window)) {
		glad_glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// activamos el programa shader que creamos anteriormente 
		glUseProgram(shaderProgram);
		// no es necesario pero, obligamos a open GL enlazar al VAO no es necesario porque
		// tenemos un unico objeto sin embargo, para tener varios si servira
		glBindVertexArray(VAO);
		// funcion de dibujo en si, crada anteriormente, especificamos el tipo de primitiva a usar
		// indice inicial de los vertices, la canidad de vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Intercambiar BUFFERES BACK A FRONT
		glfwSwapBuffers(window);
		// tenemos que decirle a la ventana que absorva todos los comando que le hemos enviado y eso se realiza a traves de la
		// siguiente funcion
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Destruir la ventana despues de que se ejecute la funcion principal
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
} 