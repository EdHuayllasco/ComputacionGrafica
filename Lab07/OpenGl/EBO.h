#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID de referencia de los Elements Buffer Object
	GLuint ID;
	// contructuro que genera los Elements Buffer Object y los referencia a los indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds EBO
	void Bind();
	// Unbinds EBO
	void Unbind();
	// Eliminar EBO
	void Delete();
};

#endif#pragma once
