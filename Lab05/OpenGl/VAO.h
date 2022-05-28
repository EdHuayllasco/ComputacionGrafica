#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID de referencia del Vertex Array Object
	GLuint ID;
	// genera el VAO ID
	VAO();

	// Vincula un atributo VBO al VAO, puede ser el color u otros.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds VAO
	void Bind();
	// Unbinds VAO
	void Unbind();
	// Deletes VAO
	void Delete();
};

#endif