#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Id del Shader Program
	GLuint ID;
	// Realiza el Shader Program desde los 2 diferentes shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activa el shader program
	void Activate();
	// Elimina el shader program
	void Delete();
	void setInt(const std::string& name, int value) const;
	void use() const;
private:
	// verifica los diferentes shaders
	void compileErrors(unsigned int shader, const char* type);
	
};


#endif