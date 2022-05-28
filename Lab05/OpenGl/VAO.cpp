#include"VAO.h"

// Constructor general el ID del VAO
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Vincula un atributo de VBO, como una posición o un color, al VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Bind VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Borrar el VAo
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}