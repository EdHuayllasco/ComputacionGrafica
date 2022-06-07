#include"shaderClass.h"

// Lee un archivo de texto y genera una cadena con todo lo que hay en el archivo de texto
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor que crea el programa Shader a partir de 2 shaders diferentes
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// lee vertexFile y fragmentFile y almacena los strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// convierte los string shaders en la matriz de caraceteres
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Crea Vertex Shader Object y obtiene la referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Adjuntamos Vertex Shader source hacia el Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// compilamos el Vertex Shader dentor del codigo maquina
	glCompileShader(vertexShader);
	// revisamos si se realizo satisfactoriamente
	compileErrors(vertexShader, "VERTEX");

	// Creamos Fragment Shader Object y obtenemos su referencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Adjuntar Fragment Shader source en el Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compilar el Vertex Shader dentro del codigo maquina
	glCompileShader(fragmentShader);
	// verificar
	compileErrors(fragmentShader, "FRAGMENT");

	// Creamos Shader Program Object obtenemos su referencia
	ID = glCreateProgram();
	// Adjuntar Fragment Shader source en el Fragment Shader Object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Wrap-up y enlazamos todos los shaders juntos dentro del shader program
	glLinkProgram(ID);
	// revisamos
	compileErrors(ID, "PROGRAM");

	// eliminamos todos los vertex y fragments
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// activamos el shader program
void Shader::Activate()
{
	glUseProgram(ID);
}

// elminamos el Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

// verificamos si los diferntes shaders se aplicaron correctamente
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// almacenamos el status de la compilacion
	GLint hasCompiled;
	// Matriz de caracteres para almacenar el mensaje de error en...
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}