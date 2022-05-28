#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// Referencia ID del Vertex Buffer Object
	GLuint ID;
	// Constructor que genera un Vertex Buffer Object y los referencia a los vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Binds VBO
	void Bind();
	// Unbinds VBO
	void Unbind();
	// Deletes VBO
	void Delete();
};

#endif
